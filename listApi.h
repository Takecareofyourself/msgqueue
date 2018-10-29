
#ifndef _LISTAPI_H_
#define _LISTAPI_H_

#include "Public.h"

void Add_Front(struct list *New,struct list *head,struct list *next);

void Del_Front(struct list *head,struct list *next);

void Add_Tail(struct list *New,struct list *head,struct list *prv);

void Del_Tail(struct list *head, struct list *prv);

int Empty_Check(struct list *head);

void Init_head(struct list * head);

#endif


