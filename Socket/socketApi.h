#ifndef __SOCKETAPI_H_
#define __SOCKETAPI_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct sockdes{
    int flag;
    int fd;
    int port;
    struct sockaddr_in skaddr;
    socklen_t len;
};

struct local{
    int flag;
    int port;
    char ipAddr[24];
};


void InitServer(struct sockdes *sock,int port);
void InitClient(struct sockdes *sock,const char *svrip,int port);

#endif