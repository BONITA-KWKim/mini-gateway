FROM alpine:3.10

# install dependancies
RUN apk add cmake build-base

# create directory
RUN mkdir -p /opt/services/mini-gw-proxy
WORKDIR /opt/services/mini-gw-proxy

# copy our project code
COPY . /opt/services/mini-gw-proxy

RUN ["chmod", "+x", "./proxy-entrypoint.sh"]
ENTRYPOINT ["sh","./proxy-entrypoint.sh"] 
#CMD ["/opt/services/mini-gw-proxy/bin/mini_gw_proxy"]
