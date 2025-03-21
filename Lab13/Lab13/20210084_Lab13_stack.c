/* 
 * 작성일: 2021/05/28
 * 학  번: 20210084
 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_STRING 20

typedef struct node
{
	char data;
	struct node* next;
}NODE;
typedef struct
{
	int count;
	NODE* top;
}STACK;

void printStack(STACK *s);
int push(STACK *s, char data);
int pop(STACK *s, char *data);
int isEmpty(STACK *s);

int main()
{
	int len, i, ioRes;
	char str[MAX_STRING];
	STACK *stack;

	stack = (STACK*)malloc(sizeof(STACK));
	
	
	if (!stack)
	{
		printf("동적 할당 에러\n");
		return 100;
	}

	stack->count = 0;
	stack->top = NULL;
	
	while (1)
	{
		printf(">> ");
		ioRes = scanf("%s", str);

		if (ioRes == EOF)
			break;

		len = strlen(str);
		for (i = 0; i < len; i++)
		{
			push(stack, str[i]);
		}
		printStack(stack);

	} // while

	free(stack);
	printf("bye!\n");

	return 0;
} // main

void printStack(STACK *s)
{
	char data;

	printf("   ");
	while (pop(s, &data)) // 스택이 빌 때까지 pop 함수 호출
	{
		printf("%c", data);
	}
	printf("\n\n");

} // printStack


int push(STACK *s, char data)
{
	NODE *temp;
	int success = 1;

	// 스택 노드 생성
	temp = (NODE*)malloc(sizeof(NODE));

	if (!temp) // 동적 할당 실패시
		success = 0;
	else
	{
		temp->data = data;
		temp->next = s->top;
		s->top = temp;
		s->count++;
	}

	return success;
} // push // push 성공시 1, 실패시 0을 반환

int pop(STACK *s, char *data) // pop 성공시 1, 실패시 0을 반환
{
	NODE *temp;
	int success = 1;
	if (!isEmpty(s)) // 스택이 비어 있지 않으면(isEmpty 함수 호출)
	{
		*data =(s->top->data);
		temp = s->top;
		s->top = temp->next;
		s->count--;
		
		free(temp); // 노드 삭제
	}
	else
		success = 0;

	return success;
} // pop
  
int isEmpty(STACK* s) // 스택이 비어 있으면 1, 그렇지 않으면 0을 반환
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}