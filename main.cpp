#include <aws/lambda-runtime/runtime.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace aws::lambda_runtime;

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

static invocation_response handle_request(invocation_request const& req)
{
    std::cout << exec("whereis g++");
    std::cout << exec("echo \"blahkhgfd\"");

    if (req.payload.length() > 42) {
        return invocation_response::failure("error message here"/*error_message*/,
                                            "error type here" /*error_type*/);
    }

    return invocation_response::success("json payload here" /*payload*/,
                                        "application/json" /*MIME type*/);
}

int main()
{
    run_handler(handle_request);
    return 0;
}