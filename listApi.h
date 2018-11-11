/*
实现操作struct list 此结构的接口函数
*/
#ifndef _LISTAPI_H_
#define _LISTAPI_H_

#include "Public.h"

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

#define foreache_list(head,tmp) \
    for((tmp) = (head)->next;(tmp) != (head); (tmp) = (tmp)->next) \

struct list *FindByIndex(struct list *head ,struct list *localtion,int index);

void Add_Front(struct list *New,struct list *head,struct list *next);

void Del_Front(struct list *head,struct list *next);

void Add_Tail(struct list *New,struct list *head,struct list *prv);

void Del_Tail(struct list *head, struct list *prv);

int Empty_Check(struct list *head);

void Init_head(struct list * head);

#endif


