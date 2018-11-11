/*
此处实现的是针对特定的链表结构实现的API
*/
#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include "Public.h"
void testfunction(struct list *head);
char * FindMsgByIndex(struct list *head, int index);
int Update_list(struct list *head,const char *path);
int Save_list(struct list *head,const char *path);
int GetFront_Drop(struct list *head,char *msg,int len);
int GetFront(struct list *head,char *msg,int len);
void Insert_Front(struct list *head,const char *msg);
void Drop_Front(struct list * head);

int GetTail_Drop(struct list *head, char *msg,int len);
int GetTail(struct list *head, char *msg,int len);
void Insert_Tail(struct list * head,const char * msg);
void Drop_Tail(struct list *head);

void Delete_All(struct list *head);
int Check_List(struct list *head);
int Count_list(struct list *head);
void Foreach_Ele(struct list *head);
void Init_Listhead(struct list *);

#endif
