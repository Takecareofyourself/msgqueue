
#include "msgqueue.h"
#include "listApi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef DEBUG
typedef struct msgque{
	struct list list;
	unsigned int size;
	void *msg;
}msgq_t;
#endif


#define foreach_element_in(head,p) \
	typeof(*(head)) *tmp = (head)->next; \
	for((p) = element_entry(tmp, typeof(*(p)), list);\
		(tmp) != (head);\
		(tmp) = (tmp->next),(p) = element_entry( tmp, typeof(*(p)), list))
#if 0
#define foreach_elementV2(head,p) \
			foreache_list((head),(tmp))
#endif 

int UpdateListFromFile(struct list *head,const char *path)
{
	unsigned int size = 0;
	int len = 0;
	void *ele = NULL;
	if(NULL == path){
		return -1;
	}
	if(access(path,F_OK)){
		return -1;
	}
	FILE *fp = fopen(path,"rb");
	if(fp == NULL)
		return -1;
	while(1)
	{
		len = fread(&size,sizeof(size),1,fp);
		if(len <= 0)
			break;
		ele = malloc(size);
		if(ele == NULL){
			printf("Malloc is error\n");
			break;
		}
		memset(ele,0,size);
		len = fread(ele,size,1,fp);
		if(len > 0){
			Insert_Tail(head,(void *)ele,size);
		}
		if(ele){
			free(ele);
			ele = NULL;
		}
	}
	return 0;
}

int SaveListToFile(struct list *head,const char *path)
{
	msgq_t *p = NULL;
	if(NULL == path){
		return -1;
	}
	FILE *fp = fopen(path,"wb");
	if(fp == NULL){
		return -2;
	}
	if(Check_List(head)){
		return -3;
	}
	
	foreach_element_in(head,p){
		fwrite(&(p->size),sizeof(p->size),1,fp);
		fwrite(p->msg,p->size,1,fp);
	}
	fclose(fp);
	return 0;
}

void * FindMsgByIndex(struct list *head, int index)
{
	msgq_t *p = NULL;
	struct list *tmp = NULL;
	tmp = FindByIndex(head,tmp,index);
	if(tmp != NULL){
		p = container_of(tmp,msgq_t,list);
		return p->msg;
	}
	return NULL;
}


static void free_msg(struct list *ptr)
{
	msgq_t *p = element_entry(ptr, msgq_t, list);
	free(p->msg);
	p->msg = NULL;
	free(p);
	p = NULL;
}

static struct list * malloc_msg(void *msg,unsigned int size)
{
	if(NULL == msg)
	{
		return NULL;
	}
	msgq_t *onemsg = (msgq_t *)malloc(sizeof(msgq_t));
	if(NULL == onemsg)
	{
		printf("msg is nill\n");
		return NULL;
	}
	memset(onemsg,0,sizeof(msgq_t));
	onemsg->list.next = NULL;
	onemsg->list.prv = NULL;
	onemsg->size = size;
	void *onestr = malloc(size);
	if(NULL == onestr)
	{
		printf("str is nill\n");
		return NULL;
	}
	memcpy(onestr,msg,size);
	onemsg->msg = onestr;
	return &onemsg->list;
}

int GetFront_Drop(struct list *head,void *msg)
{
	struct list *tmp = head->next;
	if(Check_List(head))
		return -1;

	msgq_t *p = element_entry(tmp, msgq_t,list);
	memcpy(msg,p->msg,p->size);
	Del_Front(head,head->next);
	free_msg(tmp);
	return 0;
}

int GetFront(struct list *head,void *msg)
{
	struct list *tmp = head->next;
	if(Check_List(head))
		return -1;
	msgq_t *p = element_entry(tmp, msgq_t,list);
	memcpy(msg,p->msg,p->size);
	return 0;
}
/*
参数1-head：链表的头
*/
void Insert_Front(struct list * head,void * msg,unsigned int size)
{
	struct list *tmp = malloc_msg(msg,size);
	if(NULL == tmp)
		return;
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
void Insert_Tail(struct list * head,void *msg,unsigned int size)
{
	struct list *tmp = malloc_msg(msg,size);
	if(NULL == tmp)
		return;
	Add_Tail(tmp,head,head->prv);
}

int GetTail_Drop(struct list *head, void *msg)
{
	struct list *tmp = head->prv;
	if(Check_List(head))
		return -1;
	
	msgq_t *p = element_entry(tmp,msgq_t,list);
	memcpy(msg,p->msg,p->size);
	Del_Tail(head,head->prv);
	free_msg(tmp);
	
	return 0;
}

int GetTail(struct list *head,void *msg)
{
	struct list *tmp = head->prv;
	if(Check_List(head))
		return -1;
	
	msgq_t *p = element_entry(tmp,msgq_t,list);
	memcpy(msg,p->msg,p->size);

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

int Count_list(struct list *head)
{
	int i = 0;
	struct list *tmp = head->next;
	if(tmp == head)
		return 0;
	do
	{
		i++;
		tmp = tmp->next;
	}while(tmp != head);
	return i;
}

void Foreach_Ele(struct list *head)
{
	struct list *tmp = head->next;
	if(tmp == head)
		return;
	do
	{
		msgq_t *p = container_of(tmp, msgq_t, list);
		//printf("%s\n",p->msg);
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

void InitListHead(struct list *head)
{
	Init_head(head);
}

