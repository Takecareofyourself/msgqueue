#include "socketApi.h"

int main(void)
{
    struct sockdes cli = {0};
    InitClient(&cli,NULL,8887);
    SubscribeMsg(NULL,&cli);
    return 0;
}