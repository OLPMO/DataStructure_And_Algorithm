#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
typedef struct queue
{
	int *pBase;
	int front;
	int rear;
}QUEUE;
void init_queue(QUEUE *pQ);
void traverse_queue(QUEUE *pQ);
bool en_queue(QUEUE *pQ,int Val);
bool del_queue(QUEUE *pQ,int *pVal);
bool empty_queue(QUEUE *pQ);
bool full_queue(QUEUE *pQ);
int main(int argc, char *argv[])
{
	QUEUE Q;
	int val;
	init_queue(&Q);
    en_queue(&Q,1);
	en_queue(&Q,2);
	en_queue(&Q,3);
	en_queue(&Q,4);
	en_queue(&Q,5);

	traverse_queue(&Q);
	if(del_queue(&Q,&val)) printf("出队成功。出队元素为：%d\n",val);
	else printf("抱歉！出队失败。\n");
	traverse_queue(&Q);
	

	
	return 0;
}
void init_queue(QUEUE *pQ)
{
	pQ->pBase=(int *)malloc(sizeof(int)*6);
	pQ->front=0;
	pQ->rear=0;
}
bool empty_queue(QUEUE *pQ)
{
	if(pQ->front==pQ->rear)
		return true;
	else
		return false;
}
bool full_queue(QUEUE *pQ)
{
	if(pQ->front==(pQ->rear+1)%6)
		return true;
	else
		return false;
}
bool en_queue(QUEUE *pQ,int Val)
{
	if(full_queue(pQ))
		return false;
	else
	{
		pQ->pBase[pQ->rear]=Val;
		pQ->rear=(pQ->rear+1)%6;
		return true;
	}
}
bool del_queue(QUEUE *pQ,int *pVal)
{
	if(empty_queue(pQ))
		return false;
	else
	{
		*pVal=pQ->pBase[pQ->front];
		pQ->front=(pQ->front+1)%6;
		return true;
	}
}
void traverse_queue(QUEUE *pQ)
{
	int i;
	i=pQ->front;
	while(i!=pQ->rear)
	{
		printf("%d\n",pQ->pBase[i]);
		i=(i+1)%6;
	}
}