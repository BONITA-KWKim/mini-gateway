#!/bin/bash

echo "Hello proxy entry point"
echo "===== Build mini gateway proxy server ====="
cmake -Bbuild -H.
cmake --build build
cmake --build build --target install

echo "===== start proxy server ====="
./bin/mini_gw_proxy
