
#include "msgqueue.h"
#include "listApi.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
	for((p) = container_of(tmp, typeof(*(p)), list);\
		(tmp) != (head);\
		(tmp) = (tmp->next),(p) = container_of( tmp, typeof(*(p)), list))

int Update_list(struct list *head,const char *path)
{
	msgq_t *p = NULL;
	int len = 0;
	char nbuff[32] = {0};
	if(NULL == path){
		return -1;
	}
	if(access(path,F_OK)){
		return -1;
	}
	FILE *fp = fopen(path,"r");
	if(fp == NULL)
		return -1;
	while(!feof(fp)){
		fgets(nbuff,32,fp);
		len = strlen(nbuff);
		if(len <= 1)
			continue;
		if(	nbuff[len-1] == '\n')
			nbuff[len-1] = '\0';
		Insert_Tail(head,nbuff);
	}
	return 0;
}

int Save_list(struct list *head,const char *path)
{
	msgq_t *p = NULL;
	if(NULL == path){
		return -1;
	}
	FILE *fp = fopen(path,"w");
	if(fp == NULL){
		return -2;
	}
	if(Check_List(head)){
		return -3;
	}
	
	foreach_element(head,p){
		fprintf(fp,"%s\n",p->msg);
	}
	fclose(fp);
	return 0;
}


static void free_msg(struct list *ptr)
{
	msgq_t *p = container_of(ptr, msgq_t, list);
	free(p->msg);
	p->msg = NULL;
	free(p);
	p = NULL;
}

static struct list * malloc_msg(const char *msg)
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
	if(Check_List(head))
		return -1;

	msgq_t *p = container_of(tmp, msgq_t,list);
	strncpy(msg,p->msg,len);
	Del_Front(head,head->next);
	free_msg(tmp);
	return 0;
}

int GetFront(struct list *head,char *msg,int len)
{
	struct list *tmp = head->next;
	if(Check_List(head))
		return -1;
	msgq_t *p = container_of(tmp, msgq_t,list);
	strncpy(msg,p->msg,len);
	return 0;
}
/*
参数1-head：链表的头
*/
void Insert_Front( struct list * head,const char * msg)
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
void Insert_Tail(struct list * head,const char * msg)
{
	struct list *tmp = malloc_msg(msg);
	Add_Tail(tmp,head,head->prv);
}

int GetTail_Drop(struct list *head, char *msg,int len)
{
	struct list *tmp = head->prv;
	if(Check_List(head))
		return -1;
	
	msgq_t *p = container_of(tmp,msgq_t,list);
	strncpy(msg,p->msg,len);
	Del_Tail(head,head->prv);
	free_msg(tmp);
	
	return 0;
}

int GetTail(struct list *head,char *msg,int len)
{
	struct list *tmp = head->prv;
	if(Check_List(head))
		return -1;
	
	msgq_t *p = container_of(tmp,msgq_t,list);
	strncpy(msg,p->msg,len);

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

