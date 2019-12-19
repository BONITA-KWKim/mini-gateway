#!/bin/bash

echo "Hello base image"

echo "===== install google test ====="
GTEST_DIR=./third-party/googletest
mkdir ${GTEST_DIR}/build
cmake -B${GTEST_DIR}/build -H${GTEST_DIR}/
cmake --build ${GTEST_DIR}/build --target install

echo "===== install gRPC ====="
GRPC_DIR=./third-party/grpc
cd $GRPC_DIR/..
git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc.git
cd grpc
git submodule update --init

mkdir -p cmake/build
cd cmake/build
cmake ../..
make install

echo "===== remove third party ====="
rm -rf ./third-party/
