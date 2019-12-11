# 1 day 1 commit challenge!!!!
# Mini gateway

## what is the mini gateway?
Mini gateway is a bridge for connecting a system to others. Specifically, this gateway carry on transmitting text message or kakao message.

## System
Docker
CPP
googletest

## Reference
### install GoogleTest

### install json for Modern C++
1. download  
$ git clone https://github.com/nlohmann/json.git  
2. copy json.hpp file into our project  
$ cp -r json/single_include/json.hpp ${library_directory}  
3. include in source  
#include "nlohmann/json.hpp"  
using json = nlohmann::json;  
