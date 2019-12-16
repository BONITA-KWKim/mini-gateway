#ifndef __INTERNAL_API_SERVER_H__
#define __INTERNAL_API_SERVER_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <sys/types.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <string>

// gRPC
#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

// JSON
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__INTERNAL_API_SERVER_H__