#include "socketApi.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define SERVER_PORT 6425
#define BUFF_LEN 1024

#ifdef SERVER

/*
    server:
            socket-->bind-->recvfrom-->sendto-->close
*/

int main(int argc, char* argv[])
{
    int server_fd, ret;
    struct sockaddr_in ser_addr; 

    server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if(server_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
    ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换

    ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if(ret < 0)
    {
        printf("socket bind fail!\n");
        return -1;
    }

    handle_udp_msg(server_fd);   //处理接收到的数据

    close(server_fd);
    return 0;
}

#else

/*
    client:
            socket-->sendto-->revcfrom-->close
*/
#define SERVER_IP "127.0.0.1"

struct localNet{
    int Port;
    char ipAddr[24];
};

int CreateOneConnet(const char *ipAddr,int portNum,struct sockaddr_in *ser)
{
    int fd = 0;
    
    fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd < -1){
        perror("socket");
        return -1;
    }
    ser->sin_family = AF_INET;
    ser->sin_addr.s_addr = inet_addr(ipAddr);
    ser->sin_port = htons(portNum);

    return fd;
}

void SubsMessage(const char *serverIp)
{
    int fd = 0;
    sockelen_t len;
    struct localNet one;
    strcpy(one.ipAddr,"127.0.0.1");
    one.Port = 7245;
    struct sockaddr_in ser_addr = {0};
    len = sizeof(ser_addr);
    fd = CreateOneConnet(SERVER_IP,SERVER_PORT,&ser_addr);
    if(fd>0){
        sendto(fd,&one,sizeof(one),&ser_addr,len);
    }
    close(fd);
}

int main(int argc, char* argv[])
{
    int client_fd;
    struct sockaddr_in ser_addr = {0};
    client_fd = CreateOneConnet(SERVER_IP,SERVER_PORT,&ser_addr);

    close(client_fd);

    return 0;
}
#endif