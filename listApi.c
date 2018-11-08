#include "listApi.h"

#define NULL ((void *)0)
	
#if 0
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
#endif
/*location 参数需要一个指向NULL的指针*/
struct list *FindByIndex(struct list *head ,struct list *localtion,int index)
{
	int id = 0;
	struct list *prv = head;
	struct list *next = head;
	while(1)
	{
		if(index < 0){
			id--;
			prv = prv->prv;
		}
		if(index > 0)
		{
			id++;
			next = next->next;
		}
		if(prv == next){
			return NULL;
		}
		if(index == id){
			if(index < 0)
				localtion = prv;
			if(index > 0)
				localtion = next;
			return localtion;
		}
	}
	return NULL;
}

/*
参数head：为链表的头head
参数next：为链表的头head.next所指向的地址，即head的后一个链表节点
*/
void Add_Front(struct list *New,struct list *head,struct list *next)
{
	New->next = head->next;
	head->next = New;
	next->prv = New;
	New->prv = head;
}
	
void Del_Front(struct list *head,struct list *next)
{
	next->next->prv = head;
	head->next = next->next;
}
	
/*
参数head：为链表的头head
参数next：为链表的头head.prv所指向的地址，即head的前一个链表节点
*/
void Add_Tail(struct list *New,struct list *head,struct list *prv)
{
	
	New->prv = head->prv;
	head->prv = New;
	prv->next = New;
	New->next = head;
}
	
/*
参数head：为链表的头head
参数next：为链表的头head.prv所指向的地址，即head的前一个链表节点
*/
void Del_Tail(struct list *head, struct list *prv)
{
	prv->prv->next = head;
	head->prv = prv->prv;
}

int Empty_Check(struct list *head)
{
	int ret = 0;
	struct list *tmp1 = head->next;
	struct list *tmp2 = head->prv;
	if((tmp1 == head) && (tmp2 == head))
		ret = 1;
	return ret;
}
	
void Init_head(struct list *head)
{
	head->next = head;
	head->prv = head;
}
	
