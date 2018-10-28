
#ifndef _LISTAPI_H_
#define _LISTAPI_H_

typedef struct list{
	struct list *prv;
	struct list *next;
}list_t;

void Add_Front(struct list *New,struct list *head,struct list *next);

void Add_Tail(struct list *New,struct list *head,struct list *prv);

void Del_Tail(struct list *head, struct list *prv);

void Init_head(struct list * head);

#endif

