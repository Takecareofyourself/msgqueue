#ifndef __SOCKETAPI_H_
#define __SOCKETAPI_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct server{
    int flags;
    int fd;
    int svrport;
    struct sockaddr_in svr;
    socklen_t len;
};

struct local{
    int mflag;
    int Port;
    char ipAddr[24];
};

#endif