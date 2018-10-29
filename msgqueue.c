
#include "msgqueue.h"
#include "listApi.h"
#include <stdio.h>
#include <string.h>

#include <stdlib.h>





static void free_msg(struct list *ptr)
{
	msgq_t *p = container_of(ptr, msgq_t, list);
	free(p->msg);
	p->msg = NULL;
	free(p);
	p = NULL;
}

static struct list * malloc_msg(char *msg)
{
	if(NULL == msg)
	{
		return NULL;
	}
	int len = strlen(msg);
	msgq_t *onemsg = (msgq_t *)malloc(sizeof(msgq_t));
	if(NULL == onemsg)
	{
		printf("msg is nill\n");
		return NULL;
	}
	onemsg->list.next = NULL;
	onemsg->list.prv = NULL;
	char *onestr = (char *)malloc(len+1);
	if(NULL == onestr)
	{
		printf("str is nill\n");
		return NULL;
	}
	strcpy(onestr,msg);
	onestr[len+1] = 0;
	onemsg->msg = onestr;
	return &onemsg->list;
}

int GetFront_Drop(struct list *head,char *msg,int len)
{
	struct list *tmp = head->next;
	if(tmp == head)
		return -1;

	msgq_t *p = container_of(tmp, msgq_t,list);
	strncpy(msg,p->msg,len);
	Del_Front(head,head->next);
	free_msg(tmp);
	return 0;
}
/*
参数1-head：链表的头
*/
void Insert_Front(char * msg, struct list * head)
{
	struct list *tmp = malloc_msg(msg);
	Add_Front(tmp,head,head->next);
}

void Drop_Front(struct list *head)
{
	struct list *tmp = head->next;
	if(tmp != head)
	{
		Del_Front(head,head->next);
		free_msg(tmp);
	}
}

/*
参数1-head：链表的头
*/
void Insert_Tail(char * msg, struct list * head)
{
	struct list *tmp = malloc_msg(msg);
	Add_Tail(tmp,head,head->prv);
}

int GetTail_Drop(struct list *head,char *msg,int len)
{
	struct list *tmp = head->prv;
	if(tmp == head)
		return -1;
	
	msgq_t *p = container_of(tmp,msgq_t,list);
	strncpy(msg,p->msg,len);
	Del_Tail(head,head->prv);
	free_msg(tmp);
	
	return 0;
}
/*
参数1-head：链表的头
*/
void Drop_Tail(struct list *head)
{
	struct list *tmp = head->prv;
	if(tmp != head)
	{
		Del_Tail(head,head->prv);
		free_msg(tmp);
	}
}

void Delete_All(struct list *head)
{
	struct list *tmp = NULL;
	int ret = Check_List(head);
	if(ret)
		return ;
	
	do
	{
		tmp = head->next;
		Drop_Tail(head);
	}while(tmp != head);
	
}

void Foreach_Ele(struct list *head)
{
	struct list *tmp = head->next;
	if(tmp == head)
		return;
	do
	{
		msgq_t *p = container_of(tmp, msgq_t, list);
		printf("%s\n",p->msg);
		tmp = tmp->next;
	}while(tmp != head);

}
/*
返回1 为空；返回0为非空
*/
int Check_List(struct list *head)
{
	return Empty_Check(head);
}

void Init_Listhead(struct list *head)
{
	Init_head(head);
}

