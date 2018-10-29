
#include "msgqueue.h"
#include <stdio.h>

int main(void)
{
	struct list head;
	
	Init_Listhead(&head);

	char *msg = "test1";
	Insert_Front(msg, &head);
	msg = "test2";
	Insert_Front(msg,&head);

	msg = "test3";
	Insert_Front(msg,&head);
	
	Foreach_Ele(&head);
	printf("=============\n");
	msgq_t *p;
	foreach_element(&head, p){
		if(strcmp(p->msg,"test2") == 0){
			printf("find %s\n",p->msg);
			break;
		}
	}
#if 0
	Drop_Front(&head);
	Foreach_Ele(&head);
	Drop_Front(&head);
	Drop_Front(&head);
#endif
	return 0;
}

