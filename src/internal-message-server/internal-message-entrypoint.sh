#!/bin/bash

echo "Hello IMS entry point"

echo "===== Build mini gateway IMS server ====="
cmake -Bbuild -H.
cmake --build build

echo "===== start test proxy server ====="
cmake --build build --target test

echo "===== start proxy server ====="
cmake --build build --target start_IMS
