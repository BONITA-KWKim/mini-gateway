# Proxy server in mini gateway

## What to do
Proxy server in this project is built to maintaining socket connection. Then, socket communication is able to any time. Internal API server is used for transmitted data.  
  
In proxy server, authorization and health check is only carring on. Transmitted data is parsed to send to internal API server or to used in the proxy. Data to transmit a message is passed to internal API server directly. Authorization or health check data are processed in the proxy.  