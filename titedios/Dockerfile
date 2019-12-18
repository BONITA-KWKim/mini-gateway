# ========== mini gateway base ==========
FROM alpine:3.10 AS mini_gw_base

# install dependancies
RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gateway

# copy our project code
WORKDIR /opt/services/mini-gateway
RUN mkdir -p third-party/googletest
COPY ./third-party/googletest ./third-party/googletest

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
ENTRYPOINT ["sh", "./proxy-entrypoint.sh"] 

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
ENTRYPOINT ["sh", "./internal-API-entrypoint.sh"] 
