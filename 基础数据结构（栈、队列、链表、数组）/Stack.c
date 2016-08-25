#include <stdio.h>
#include<malloc.h>
#include<stdbool.h>
typedef struct node
{
	int data;
	struct node *pnext;
}NODE;
typedef struct stack//stack��ջ����˼,ջ��������
{
	NODE *pTOP;
	NODE *pBOTTOM;
}STACK;
void init_stack(STACK *s);
void push_stack(STACK *s,int val);//ѹջ������ջ
void pop_stack(STACK *s,int *ppopdata);//��ջ
void traverse_stack(STACK *s);
void clear_stack(STACK *s);
int main(int argc, char *argv[])
{
	STACK S;
	int popdata,popdata1;
	init_stack(&S);
	push_stack(&S,1);
	push_stack(&S,2);
	push_stack(&S,3);
	push_stack(&S,23);
	push_stack(&S,32);
	pop_stack(&S,&popdata);
	pop_stack(&S,&popdata1);
	traverse_stack(&S);
	printf("��ջ����Ϊ��%d,%d\n",popdata,popdata1);
	return 0;
}
void init_stack(STACK *s)
{
	s->pTOP=(NODE *)malloc(sizeof(NODE));
	if(NULL==s->pTOP)
	{
		printf("��Ǹ���ڴ����ʧ�ܡ�");
		exit(-1);
	}
	else
	{
		s->pBOTTOM=s->pTOP;
		s->pTOP->pnext=NULL;
	}	
}
void push_stack(STACK *s,int val)
{
	NODE *pnew=(NODE *)malloc(sizeof(NODE));
	if (NULL==pnew)
	{
		printf("��Ǹ�������ڴ�ʧ�ܡ�");
		exit(-1);
	}
	pnew->data=val;
	pnew->pnext=s->pTOP;
	s->pTOP=pnew;
}
void traverse_stack(STACK *s)
{
	NODE *pmiddle=s->pTOP;
	while (pmiddle!=s->pBOTTOM)
	{
		printf("%d\n",pmiddle->data);
		pmiddle=pmiddle->pnext;
	}
}
void pop_stack(STACK *s,int *ppopdata)
{
	NODE *pmiddle;
	if (s->pTOP==s->pBOTTOM)
	{
		printf("��ջΪ��ջ����ջʧ�ܣ�");
	}
	else
	{
		pmiddle=s->pTOP;
		*ppopdata=pmiddle->data;
	    s->pTOP=s->pTOP->pnext;
	    free(pmiddle);
		pmiddle=NULL;
	}
	
}
void clear_stack(STACK *s)
{
	NODE *pmiddle,*pmiddle1;
	pmiddle=s->pTOP;
	while(pmiddle!=s->pBOTTOM)
	{
		pmiddle1=pmiddle->pnext;
		free(pmiddle);
		pmiddle=pmiddle1;
	}
	s->pTOP=s->pBOTTOM;
}