#!/bin/bash

echo "Hello base image"
THIRD_PARTY=./third-party

echo "===== install google test ====="
cd $THIRD_PARTY
git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc.git
cd googletest
mkdir build
cmake -Bbuild -H.
cmake --build build --target install

echo "===== install gRPC ====="
cd $THIRD_PARTY
git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc.git
cd grpc
git submodule update --init

#mkdir -p cmake/build
#cd cmake/build
#cmake ../..
#make install

make && make install

# install gRPC on alpine
# apk add build-base cmake
# apk update && apk add --no-cache --repository=http://dl-cdn.alpinelinux.org/alpine/edge/main protoc
# apk update && apk add --no-cache --repository=http://dl-cdn.alpinelinux.org/alpine/edge/community grpc


echo "===== remove third party ====="
rm -rf ./third-party/
