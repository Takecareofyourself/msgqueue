
#include "msgqueue.h"
#include <stdio.h>

int main(void)
{
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
#if 0
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
	return 0;
}

