# Mini Gateway

## 개요
* 메시지를 보낼 수 있는 게이트웨이

## 전송 방법
* TCP/IP 를 이용하여 접속 유지 
  - 다량의 메시지를 발송하기 위해 접속 유지가 필요할 경우 TCP/IP를 통해 접속 유지
  - JSON 포맷으로 메시지 전송 의뢰
* API 호출 방식
  - 접속 유지가 필요 없거나 보안 등에 민감하지 않은 정보 발송 시 API 호출을 통해 메시지 발송 가능

## 빌드 방법
* (추후 작성)

## System
Docker
CPP
googletest
gRPC

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
