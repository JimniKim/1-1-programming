#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char name[20];
	int exam[2];
	float avg;
	char grade;
}STUDENT;

typedef struct node
{
	STUDENT data;
	struct node* next;
}NODE;

typedef struct
{
	int count;
	NODE* head;
	NODE* tail;
}LIST;

void insert_node(LIST* plist);
void print_list(LIST* plist);

int main()
{
	char command[20], find_human[20];
	LIST slist; int i,j;
	slist.count = 0; 
	slist.head = NULL;
	slist.tail = NULL;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	while (1)
	{
		printf(">> ");
		scanf("%s", command);
		if (!strcmp(command, "add"))
			insert_node(&slist); 
		if (!strcmp(command, "print"))
			print_list(&slist);
		if (!strcmp(command, "find"))
		{
			printf("이름: ");
			scanf("%s", find_human);
			for (temp = slist.head, i = 0; temp->next != NULL; temp = temp->next, i++)
				if (!strcmp(temp->data.name, find_human))
				{
					printf("번호   이름\t\t중간  기말  평균  (학점)\n");
					printf("%d      %s\t\t %d     %d  %4.1f   (%c)\n", i + 1, temp->data.name, temp->data.exam[0], temp->data.exam[1], temp->data.avg, temp->data.grade);
					break;
				}
			if (temp->next == NULL && !strcmp(temp->data.name, find_human))
				printf("%d      %s\t\t %d     %d  %4.1f   (%c)\n", slist.count, temp->data.name, temp->data.exam[0], temp->data.exam[1], temp->data.avg, temp->data.grade);
		}
		if (!strcmp(command, "quit"))
			break;
		printf("\n");
	}
	return 0;
}
void insert_node(LIST* plist)
{
	
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->next = NULL;
	printf("이름: ");
	scanf("%s", temp->data.name);
	printf("중간고사: ");
	scanf("%d", &(temp->data.exam[0]));
	printf("기말고사: ");
	scanf("%d", &(temp->data.exam[1]));
	if (plist->head == NULL)
		plist->head = temp;
	else
		plist->tail->next = temp;
	plist->tail = temp;
	(plist->count)++;
	temp->data.avg = (temp->data.exam[0] + temp->data.exam[1]) / 2.0;
	switch ((int)temp->data.avg/ 10)
	{
	case 10:
	case 9: temp->data.grade = 'A'; break;
	case 8: temp->data.grade = 'B'; break;
	case 7: temp->data.grade = 'C'; break;
	default:temp->data.grade = 'D'; break;
	}
}
void print_list(LIST* plist)
{
	NODE* temp; int i=0; 
	printf("번호   이름\t\t중간  기말  평균  (학점)\n");
	for (temp = plist->head; temp->next != NULL; temp = temp->next,i++)
		printf("%d      %s\t\t %d     %d  %4.1f   (%c)\n", i + 1, temp->data.name, temp->data.exam[0], temp->data.exam[1], temp->data.avg, temp->data.grade);
	if(temp->next == NULL)
		printf("%d      %s\t\t %d     %d  %4.1f   (%c)\n", plist->count, temp->data.name, temp->data.exam[0], temp->data.exam[1], temp->data.avg, temp->data.grade);
}
