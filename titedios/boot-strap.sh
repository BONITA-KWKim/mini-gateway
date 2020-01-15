#!/usr/bin/env bash

sudo apt-get update
sudo apt-get install -y build-essential autoconf git pkg-config \
                        automake libtool curl make g++ unzip \
                        cmake vim
sudo apt-get clean

# install googletest
mkdir -p /opt/services/mini-gateway/third-party/googletest
git clone https://github.com/google/googletest.git /opt/services/mini-gateway/third-party/googletest
cd /opt/services/mini-gateway/third-party/googletest 
echo "--- installing googletest ---" 
mkdir build 
cmake -Bbuild -H. 
cmake --build build --target install 
rm -rf /opt/services/mini-gateway/third-party/googletest

# install cpprestsdk
sudo apt-get install -y libboost-all-dev
sudo apt-get install -y libcpprest-dev
