/*
此处实现的是针对特定的链表结构实现的API
*/
#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include "Public.h"
#include <stdio.h>

#define DEBUG
#ifdef DEBUG
typedef struct msgque{
	struct list list;
	unsigned int size;
	void *msg;
}msgq_t;

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define container_of(ptr, type, member) ({      \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
		(type *)( (char *)__mptr - offsetof(type,member) );})

#define element_entry(ptr,type,member)  container_of(ptr, type, member)
#define foreach_element(head,ele) \
	struct list *tmp = (head)->next; \
	msgq_t *p = NULL; \
	for((p) = element_entry(tmp, msgq_t, list),ele = p->msg;\
		(tmp) != (head);\
		(tmp) = (tmp->next),(p) = element_entry( tmp,msgq_t, list),ele = p->msg)

#endif 
//char * FindMsgByIndex(struct list *head, int index);
//int Update_list(struct list *head,const char *path);
int Save_list(struct list *head,const char *path);
int GetFront_Drop(struct list *head,void *msg);
int GetFront(struct list *head,void *msg);
void Insert_Front(struct list *head,void *msg,unsigned int size);
void Drop_Front(struct list * head);

int GetTail_Drop(struct list *head, void *msg);
int GetTail(struct list *head, void *msg);
void Insert_Tail(struct list * head,void *msg,unsigned int size);
void Drop_Tail(struct list *head);

void Delete_All(struct list *head);
int Check_List(struct list *head);
int Count_list(struct list *head);
void Foreach_Ele(struct list *head);
void Init_Listhead(struct list *);

#endif
