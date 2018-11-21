#include "socketApi.h"

int main(void)
{
    struct sockdes svr = {0};
    InitServer(&svr,8887);
    CatchSubscribe(&svr);
    return 0;
}