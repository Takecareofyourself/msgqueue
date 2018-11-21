#include "socketApi.h"


#define SERVER_PORT 8887
#define LOCAL_PORT 7245
#define SERVER_IP "127.0.0.1"

static void InitSockaddr_in(struct sockaddr_in *addr_in,const char *ip,int port);

int AcceptMessage(struct sockdes *sock,void *msgbuff,int size)
{
    int ret = 0;
    printf("start accept:%d\n",sock->flag);
    if(sock->flag)
        ret = recvfrom(sock->fd,msgbuff,size,0,NULL,NULL);
    return ret;
}

void SubscribeMsg(const char *serverIp,struct sockdes *sock)
{
    int ret = 0;
    struct local one;
    strcpy(one.ipAddr,"192.168.0.250");
    one.port = 7245;
    one.flag = 233;
    sendto(sock->fd,&one,sizeof(one),0,(struct sockaddr *)&sock->skaddr,sock->len);
    printf("start recv\n");
    recvfrom(sock->fd,&sock->flag,sizeof(sock->flag),0,NULL,NULL);
    
    printf("%d\n",sock->flag);
    if(sock->flag){
        printf("Subscribe is ok\n");
    }
}

void InitClient(struct sockdes *sock,const char *svrip,int port)
{
    sock->port = port;
    sock->flag = 0;
    sock->fd = socket(AF_INET,SOCK_DGRAM,0);
    if(sock->fd < -1){
        perror("socket");
        return ;
    }
    InitSockaddr_in(&sock->skaddr,SERVER_IP,port);
    sock->len = sizeof(sock->skaddr);
}

/*--------------------------------------------------------------------*/

int CatchSubscribe(struct sockdes *sock)
{
    struct local one;
    one.flag = -1;
    int flags = 1;
    int ret =0;
    struct sockaddr_in cli = {0};
    socklen_t len = sizeof(cli) ;

    ret = recvfrom(sock->fd,&one,sizeof(one),0,(struct sockaddr *)&cli,&len);
    printf("recv : %d\n",ret);
    printf("%s and %d\n",one.ipAddr,one.flag);
    
    ret = sendto(sock->fd,&flags,sizeof(flags),0,(struct sockaddr *)&cli,len);
    if(ret == -1)
        perror("sendto:");

    /*将用户上报信息生成*/
    printf("ret %d\n",ret);
    return 0;
}

void InitServer(struct sockdes *sock,int port)
{
    int ret = 0;
    sock->port = SERVER_PORT;
    sock->flag = 0;
    sock->fd = socket(AF_INET,SOCK_DGRAM,0);
    if(sock->fd < -1){
        perror("socket");
        return ;
    }
    InitSockaddr_in(&sock->skaddr,NULL,port);
    sock->len = sizeof(sock->skaddr);

    ret = bind(sock->fd,(struct sockaddr *)&sock->skaddr,sock->len);
    if(ret == -1){
        perror("bind");
    }
}

static void InitSockaddr_in(struct sockaddr_in *addr_in,const char *ip,int port)
{
    addr_in->sin_family = AF_INET;
    if(NULL == ip)
        addr_in->sin_addr.s_addr = htonl(INADDR_ANY);
    else
        addr_in->sin_addr.s_addr = inet_addr(ip);
    addr_in->sin_port = htons(port);
}