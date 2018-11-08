
#include "msgqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


//struct list head;

void *Consumer(void *);

int main(void)
{
	//Init_Listhead(&head);

	struct list head;
	char buff[32] = {0};
	
	Init_Listhead(&head);

	char *msg = "test1";
	Insert_Front(&head,msg );
	msg = "test2";
	Insert_Front(&head,msg);

	msg = "test3";
	Insert_Front(&head,msg);
	
	Foreach_Ele(&head);
	printf("=============\n");

	int ret = GetTail(&head,buff,32);
	if(ret)
		printf("is empty\n");
	else
		printf("get is %s\n",buff);
	printf("+++++++++++++\n");
	Foreach_Ele(&head);
	printf("+++++++++++++\n");
	msg = FindMsgByIndex(&head,4);
	if(msg != NULL){
		printf("msg is not null\n");
		printf("find is :%s\n",msg);
	}
		
#if 0
	Delete_All(&head);
	ret = Check_List(&head);
	if(ret)
		printf("is empty\n");

	Drop_Front(&head);
	Drop_Front(&head);
	Drop_Front(&head);
	Drop_Front(&head);
	Foreach_Ele(&head);
	printf("+++++++++++++\n");
	ret = Check_List(&head);
	if(ret)
		printf("is empty\n");
	else
		Foreach_Ele(&head);
#endif

/*
	Drop_Front(&head);
	Foreach_Ele(&head);
	Drop_Front(&head);
	Drop_Front(&head);
*/

#if 0
	pthread_t pth1;
	pthread_create(&pth1,NULL,Consumer,NULL);
	char *msg = "test1";
	int n = 0;
	while(1)
	{
		Insert_Front(msg,&head);
		sleep(2);
		n++;
		if(n>=3)
			break;
	}
	pthread_join(pth1,NULL);
	printf("main is end\n");
#endif
	return 0;
}

void *Consumer(void *arg)
{
	#if 0
	srand(time(NULL));
	int mtm = 0;
	while(1)
	{
		//mtm = rand()%5+1;
		if(Check_List(&head))
			printf("is empty|wait %d\n",mtm);
		else
			Drop_Front(&head);
		sleep(1);
		mtm++;
		if(mtm >= 10)
			break;
	}
	#endif
	return NULL;
}
