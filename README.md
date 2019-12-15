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
1. Download
$ git clone https://github.com/google/googletest.git
2. Build googletest
$ cd googletest
$ cmake -Bmybuild -H.
3. Create library
$ cd mybuild
$ make
4. Copy header and library
$ cp -r googletest/googletest/include ${your own project} 
$ cp -r googletest/googlemock/include ${your own project} 
$ cp -r googletest/mybuild/lib ${your own project}
5. Include in source
#include "gtest/gtest.h"
#include "gmock/gmock.h"

### install json for Modern C++
1. Download  
$ git clone https://github.com/nlohmann/json.git  
2. Copy json.hpp file into our project  
$ cp -r json/single_include/json.hpp ${library_directory}  
3. Include in source  
#include "nlohmann/json.hpp"  
using json = nlohmann::json;  
