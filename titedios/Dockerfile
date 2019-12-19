# ========== mini gateway base ==========
FROM alpine:3.10 AS mini_gw_base

# install dependancies
RUN apk add cmake build-base git curl
# gRPC
RUN apk add autoconf libtool pkgconfig go
#RUN apk add libgflags-dev libgtest-dev
#RUN apk add clang-5.0 libc++-dev

# create directory
RUN mkdir -p /opt/services/mini-gateway/shared

# copy our project code
WORKDIR /opt/services/mini-gateway
RUN mkdir include
RUN mkdir library
COPY ./include ./include
COPY ./library ./library

# copy third party
RUN mkdir -p third-party/
COPY ./third-party/ ./third-party/

# install third party
COPY ./base-entrypoint.sh .
RUN ["chmod", "+x", "./base-entrypoint.sh"]
RUN ["sh", "./base-entrypoint.sh"]

# ========== mini gateway proxy server ==========
FROM mini_gw_base AS mini_gw_proxy

# install dependancies
#RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway/proxy
WORKDIR /opt/services/mini-gateway/proxy

# copy our project code
COPY ./proxy .

RUN ["chmod", "+x", "./proxy-entrypoint.sh"]
#ENTRYPOINT ["sh", "./proxy-entrypoint.sh"] 

# ========== mini gateway internal API server ==========
FROM mini_gw_base AS mini_gw_internal_API

# install dependancies
#RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway/internal_API_server
WORKDIR /opt/services/mini-gateway/internal_API_server

# copy our project code
COPY ./internal-API-server .

RUN ["chmod", "+x", "./internal-API-entrypoint.sh"]
#ENTRYPOINT ["sh", "./internal-API-entrypoint.sh"] 

# ========== mini gateway internal API server ==========
FROM mini_gw_base AS mini_gw_vendor_kakao

# install dependancies
#RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway/vendor-kakao
WORKDIR /opt/services/mini-gateway/vendor-kakao

# copy our project code
COPY ./vendor-kakao .

RUN ["chmod", "+x", "./kakao-entrypoint.sh"]
#ENTRYPOINT ["sh", "./kakao-entrypoint.sh"] 
