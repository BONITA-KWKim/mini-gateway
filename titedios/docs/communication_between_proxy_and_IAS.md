# Communication between proxy and internal API server

## gRPC vs cpp rest SDK
I want to use gRPC for communication method between docker containers. CPP rest SDK could be more effiecent to reqeust and response between those.  
gRPC is powerful, but it is pretty big for our project. A message in protocol buffer will be changed, however, proxy server has to hold socket connection for client. If it is changed, socket connection will be closed and that is problem for us. So, I have to search another option.  
CPP rest SDK is that. However, it is just test level. I may get others after test and thinking.  