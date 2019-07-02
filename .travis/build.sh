#!/usr/bin/env bash

mkdir build &&
cd build &&
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=~/lambda-install &&
make &&
make aws-lambda-package-extractor-cpp
