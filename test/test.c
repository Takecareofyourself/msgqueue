
#include "msgqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct my{
	int key;
	char val[32];
};/*用户自定义结构体*/

int main(void)
{
	struct my a1;
	a1.key = 10;
	strcpy(a1.val,"test1");
	struct my a2;
	a2.key = 10;
	strcpy(a2.val,"test2");
	struct list head;
	InitListHead(&head);

	Insert_Front(&head,&a1,sizeof(a1));
	printf("%d\n",sizeof(a1));
	Insert_Front(&head,&a2,sizeof(a2));
	printf("%d\n",sizeof(a2));
	struct my *ele=NULL;
	//foreach_element(&head,ele){
		/*测试打印链表中的元素*/
		//printf("Key: %d\n",ele->key);
		//printf("Val: %s\n",ele->val);
	//}
	SaveListToFile(&head,"./my.txt");
	Delete_All(&head);
	printf("Num: %d\n",Count_list(&head));
	UpdateListFromFile(&head,"./my.txt");
	struct my *ele1=NULL;
	foreach_element(&head,ele1){
		/*测试打印链表中的元素*/
		printf("Key: %d\n",ele1->key);
		printf("Val: %s\n",ele1->val);
	}
	ele1 = (struct my *)FindMsgByIndex(&head,3);
	if(ele1){
		printf("Key: %d\n",ele1->key);
		printf("Val: %s\n",ele1->val);
	}else{
		printf("Not find\n");
	}
	return 0;
}
