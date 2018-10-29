
#include "msgqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


struct list head;

void *Consumer(void *);

int main(void)
{
	Init_Listhead(&head);
#if 0

	struct list head;
	char buff[32] = {0};
	
	Init_Listhead(&head);

	char *msg = "test1";
	Insert_Front(msg, &head);
	msg = "test2";
	Insert_Front(msg,&head);

	msg = "test3";
	Insert_Front(msg,&head);
	
	Foreach_Ele(&head);
	printf("=============\n");

	int ret = GetTail_Drop(&head,buff,32);
	if(ret)
		printf("is empty\n");
	else
		printf("get is %s\n",buff);
	printf("+++++++++++++\n");
	Foreach_Ele(&head);
	printf("+++++++++++++\n");
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

	msgq_t *p;
	foreach_element(&head, p){
		if(strcmp(p->msg,"test2") == 0){
			printf("find %s\n",p->msg);
			break;
		}
	}

	Drop_Front(&head);
	Foreach_Ele(&head);
	Drop_Front(&head);
	Drop_Front(&head);
#endif
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
	return 0;
}

void *Consumer(void *arg)
{
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
	return NULL;
}
