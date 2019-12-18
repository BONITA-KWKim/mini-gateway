#!/bin/bash

echo "Hello proxy entry point"

echo "===== install google test ====="
GTEST_DIR=../third-party/googletest
mkdir ${GTEST_DIR}/build
cmake -B${GTEST_DIR}/build -H${GTEST_DIR}/
cmake --build ${GTEST_DIR}/build --target install

echo "===== Build mini gateway proxy server ====="
cmake -Bbuild -H.
cmake --build build

echo "===== start test proxy server ====="
cmake --build build --target test

echo "===== start proxy server ====="
cmake --build build --target start_proxy
