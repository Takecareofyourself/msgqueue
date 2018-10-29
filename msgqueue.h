
#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include "Public.h"

typedef struct msgque{
	struct list list;
	char *msg;
}msgq_t;

void Init_Listhead(struct list *);
void Insert_Front(char *msg,struct list *head);
void Drop_Front(struct list * head);
void Insert_Tail(char * msg, struct list * head);
void Drop_Tail(struct list *head);
void Foreach_Ele(struct list *head);


#endif
