#include "socketApi.h"


#define SERVER_PORT 8887
#define LOCAL_PORT 7245
#define SERVER_IP "127.0.0.1"


int CatchSubs(struct server *ser)
{
    struct local one;
    one.mflag = -1;
    int flags = 1;
    int ret =0;
    struct sockaddr_in cli = {0};
    socklen_t len = sizeof(cli) ;
    memset(&cli,0,sizeof(cli));

    ret = bind(ser->fd,(struct sockaddr *)&ser->svr,ser->len);
    if(ret == -1){
        perror("bind");
    }
  
    ret = recvfrom(ser->fd,&one,sizeof(one),0,(struct sockaddr *)&cli,&len);
    printf("recv : %d\n",ret);
    printf("%s and %d\n",one.ipAddr,one.mflag);
    
    ret = sendto(ser->fd,&flags,sizeof(flags),0,(struct sockaddr *)&cli,len);
    perror("sendto:");
    printf("ret %d\n",ret);
    
    
}

int AcceptMessage(struct server *ser,void *msgbuff,int size)
{
    int ret = 0;
    printf("start accept:%d\n",ser->flags);
    if(1)
        ret = recvfrom(ser->fd,msgbuff,size,0,NULL,NULL);
    return ret;
}

void SubsMessage(const char *serverIp,struct server *ser)
{
    int ret = 0;
    struct local one;
    strcpy(one.ipAddr,"192.168.0.250");
    one.Port = 7245;
    one.mflag = 233;
    sendto(ser->fd,&one,sizeof(one),0,(struct sockaddr *)&ser->svr,ser->len);
    printf("start recv\n");
    //recvfrom(ser->fd,&ser->flags,sizeof(ser->flags),0,NULL,NULL);
    ser->flags=1;
    printf("%d\n",ser->flags);
    close(ser->fd);
    if(ser->flags){
        InitRec(ser,0);
        ret = bind(ser->fd,(struct sockaddr *)&ser->svr,ser->len);
        if(ret == -1){
            perror("bind");
        }
    }
}

void InitRec(struct server *ser,int flag)
{
    ser->svrport = SERVER_PORT;
    ser->flags = 0;
    ser->fd = socket(AF_INET,SOCK_DGRAM,0);
    if(ser->fd < -1){
        perror("socket");
        return ;
    }
    ser->svr.sin_family = AF_INET;
    if(flag)
        ser->svr.sin_addr.s_addr = inet_addr(SERVER_IP);
    else
        ser->svr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser->svr.sin_port = htons(ser->svrport);
    ser->len = sizeof(ser->svr);
}
