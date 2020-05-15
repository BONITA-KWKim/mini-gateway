# ========== mini gateway base ==========
FROM debian:stretch AS mini-gw-base

LABEL maintaner "kyungwon.KIM <kyungwon9010@gmail.com>"

# install dependancies
RUN apt-get update && apt-get install -y \
  build-essential autoconf git pkg-config \
  automake libtool curl make g++ unzip cmake \
  vim \
  && apt-get clean

# create directory
RUN mkdir -p /opt/services/mini-gateway/shared

# copy our project code
WORKDIR /opt/services/mini-gateway
RUN mkdir include
RUN mkdir library
RUN mkdir config
COPY ./include ./include
COPY ./library ./library
COPY ./config  ./config
# install gRPC
# install protobuf first, then grpc
# RUN mkdir -p /opt/services/mini-gateway/third-party/grpc
# ENV GRPC_RELEASE_TAG v1.10.x
# RUN git clone -b ${GRPC_RELEASE_TAG} https://github.com/grpc/grpc /opt/services/mini-gateway/third-party/grac && \
# 		cd /opt/services/mini-gateway/third-party/grac && \
#     git submodule update --init && \
#     echo "--- installing protobuf ---" && \
#     cd third_party/protobuf && \
#     ./autogen.sh && ./configure --enable-shared && \
#     make -j$(nproc) && make -j$(nproc) check && make install && make clean && ldconfig && \
#     echo "--- installing grpc ---" && \
#     cd /opt/services/mini-gateway/third-party/grac && \
#     make -j$(nproc) && make install && make clean && ldconfig 
#     && \ 
#     rm -rf /opt/services/mini-gateway/third-party/grpc

# install googletest
RUN mkdir -p /opt/services/mini-gateway/third-party/googletest
RUN git clone https://github.com/google/googletest.git /opt/services/mini-gateway/third-party/googletest && \
        cd /opt/services/mini-gateway/third-party/googletest && \ 
    echo "--- installing googletest ---" && \
    mkdir build && \
    cmake -Bbuild -H. && \
    cmake --build build --target install && \
    rm -rf /opt/services/mini-gateway/third-party/googletest

# install cpprestsdk
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y libcpprest-dev

# install third party
COPY ./base-entrypoint.sh .
RUN ["chmod", "+x", "./base-entrypoint.sh"]
RUN ["sh", "./base-entrypoint.sh"]

# ========== mini gateway proxy server ==========
FROM mini-gw-base AS mini-gw-proxy

# install dependancies
#RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway/proxy
WORKDIR /opt/services/mini-gateway/proxy

# copy our project code
COPY ./proxy .

RUN ["chmod", "+x", "./proxy-entrypoint.sh"]
#ENTRYPOINT ["sh", "./proxy-entrypoint.sh"] 

# ========== mini gateway internal message server ==========
FROM mini-gw-base AS mini-gw-internal-IMS

# install dependancies
#RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway/internal-message-server
WORKDIR /opt/services/mini-gateway/internal-message-server

# copy our project code
COPY ./internal-message-server .

RUN ["chmod", "+x", "./internal-message-entrypoint.sh"]
#ENTRYPOINT ["sh", "./internal-message-entrypoint.sh"] 

# ========== mini gateway internal  server ==========
FROM mini-gw-base AS mini-gw-vendor-kakao

# install dependancies
#RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway/vendor-kakao
WORKDIR /opt/services/mini-gateway/vendor-kakao

# copy our project code
COPY ./vendor-kakao .

RUN ["chmod", "+x", "./kakao-entrypoint.sh"]
#ENTRYPOINT ["sh", "./kakao-entrypoint.sh"] 

# ========== mini gateway database manager ==========
FROM postgres:12.1-alpine AS mini-gw-db-manager

# create directory
RUN mkdir -p /opt/services/mini-gateway/db-manager
WORKDIR /opt/services/mini-gateway/db-manager

# copy our project code
COPY ./db-manager .

RUN ["chmod", "+x", "./db-manager-entrypoint.sh"]
