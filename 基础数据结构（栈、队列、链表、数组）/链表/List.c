#include <stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node
{
	int data;
	struct node *pnext;
}NODE;
NODE *create_list();
void traverse_list(NODE *phead);
bool is_empty(NODE *phead);
int length_list(NODE *phead);
bool insert_list(NODE *phead,int pos,int val);  //��pHead��ָ������ĵ�pos���ڵ�ĺ������һ���µĽ�㣬�ýڵ��ֵ��val�� ����pos��ֵ�Ǵ�1��ʼ
bool delete_list(NODE *phead,int pos);
void sort_list(NODE *phead);//�ɴ�С������
bool find_list(NODE *phead,int val);
int main(int argc, char *argv[])
{
	NODE *phead;
	phead=create_list();
	//traverse_list(phead);
    /*if (is_empty(phead))
    {
		printf("����Ϊ��\n");
    }
	else traverse_list(phead);
	printf("�������Ч�ڵ���Ϊ��%d\n",length_list(phead));
	*/
	/*if(insert_list(phead,-1,9))traverse_list(phead);
	else printf("����ʧ�ܣ�\n");
	*/
	/*if (delete_list(phead,3))
	{
		traverse_list(phead);
	}
	else printf("ɾ��ʧ�ܣ�\n");
	*/
	sort_list(phead);
	traverse_list(phead);
	return 0;
}
NODE *create_list()
{
	int value,len,i;
	NODE *PHEAD,*PTAIL,*PNEW;
	PHEAD=(NODE *)malloc(sizeof(NODE));
	if(PHEAD==NULL)
	{
		printf("��Ǹ���ڴ����ʧ�ܡ�");
		exit(1);
	}
	PHEAD->pnext=NULL;
	PTAIL=PHEAD;
	printf("��������Ҫ���ɵ�����ڵ������");
	scanf("%d",&len);
	for(i=0;i<len;i++)
	{
		printf("\n�������%d���ڵ�����ݣ�",i+1);
		scanf("%d",&value);
		PNEW=(NODE *)malloc(sizeof(NODE));
		PNEW->data=value;
		PTAIL->pnext=PNEW;
		PTAIL=PNEW;
		PTAIL->pnext=NULL;
	}
	return PHEAD;
}
void traverse_list(NODE *phead)
{
	phead=phead->pnext;
	while(phead->pnext!=NULL)
	{
		printf("%d\n",phead->data);
		phead=phead->pnext;
	}
	printf("%d\n",phead->data);
}
bool is_empty(NODE *phead)
{
	if(phead->pnext==NULL)
      return true;
	else return false;
}
int length_list(NODE *phead)
{
	int len=1;
	phead=phead->pnext;
	if (phead==NULL)
	{
		return 0;
	}
	while(phead->pnext!=NULL)
	{
		len++;
		phead=phead->pnext;
	}
	return len;
}
bool insert_list(NODE *phead,int pos,int val)
{
	int i=1;
	NODE *pmiddle,*pinsert;
	if(pos<1||pos>length_list(phead))
		return false;
	phead=phead->pnext;
	while(i<pos)
	{
		phead=phead->pnext;
		i++;
	}
	pinsert=(NODE *)malloc(sizeof(NODE));
	pinsert->data=val;
	pmiddle=phead->pnext;
	phead->pnext=pinsert;
	pinsert->pnext=pmiddle;
	return true;	
}
bool delete_list(NODE *phead,int pos)
{
	int i=1;
	NODE *pdelete;
	if(pos<1||pos>length_list(phead))
		return false;
	phead=phead->pnext;
	while(i<pos-1)
	{
		phead=phead->pnext;
		i++;
	}
	pdelete=phead->pnext;
	phead->pnext=pdelete->pnext;
	free(pdelete);
	return true;
}
void sort_list(NODE *phead)
{
	int i,j,len,t;
	len=length_list(phead);
	NODE *pmax;
	pmax=phead->pnext;
	phead=pmax->pnext;
	for(i=0;i<len-1;i++)
	{
		for (j=i+1;j<len;j++)
		{
			if (pmax->data<phead->data)
			{
				t=pmax->data;
				pmax->data=phead->data;
				phead->data=t;
			}
			phead=phead->pnext;
		}
	    pmax=pmax->pnext;
		phead=pmax->pnext;
	}
}

bool find_list(NODE *phead,int val){
	NODE* tmp=phead;
	while(tmp->pnext != NULL){
		if( tmp->data == val){
			return true;
		}
		tmp=tmp->pnext;
	}
	if( tmp->data == val){
		return true;
	}else{
		return false;
	}
}