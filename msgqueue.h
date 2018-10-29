
#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include "Public.h"

typedef struct msgque{
	struct list list;
	char *msg;
}msgq_t;

#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
	 
#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
	 
#define container_of(ptr, type, member) ({      \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
		(type *)( (char *)__mptr - offsetof(type,member) );})


#define foreach_element(head,p) \
	typeof(*(head)) *tmp = (head)->next; \
	for(;(tmp) != (head);(p) = container_of( tmp, msgq_t, list) ,(tmp) = (tmp->next))

	
int GetFront_Drop(struct list *head,char *msg,int len);
void Insert_Front(char *msg,struct list *head);
void Drop_Front(struct list * head);

int GetTail_Drop(struct list *head,char *msg,int len);
void Insert_Tail(char * msg, struct list * head);
void Drop_Tail(struct list *head);

void Delete_All(struct list *head);
int Check_List(struct list *head);
void Foreach_Ele(struct list *head);
void Init_Listhead(struct list *);

#endif
