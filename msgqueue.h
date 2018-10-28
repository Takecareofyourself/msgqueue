
#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include "listApi.h"

typedef struct msgque{
	struct list list;
	char *msg;
}msgq_t;

void Init_Listhead(struct list *);
void Insert_Front(char *msg,struct list *head,struct list *next);
void Foreach_Ele(struct list *head);


#endif
