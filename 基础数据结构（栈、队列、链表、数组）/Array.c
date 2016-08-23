#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct shuzu
{
	int *pBase;
	int cnt;
	int len;
}Array;
void init_arr(Array *parr,int length);  //�ֺŲ���ʡ
bool append_arr(Array *parr,int value); //׷��
bool insert_arr(Array *parr,int pos,int invalue); // pos��ʾ�ڵڼ���������Ƕ��
bool delete_arr(Array *parr,int pos,int *denum);
int get();
bool is_empty(Array *parr);
bool is_full(Array *parr);
void sort_arr(Array *parr);//�ɴ�С����
void show_arr(Array *parr); 
void inversion_arr(Array *parr);//����

int main(int argc, char *argv[])
{
	Array Arr;
	int delnum;
	init_arr(&Arr,6);
	append_arr(&Arr,44);
	append_arr(&Arr,-2);
	append_arr(&Arr,5);
    append_arr(&Arr,435);
	insert_arr(&Arr,2,4);
	delete_arr(&Arr,3,&delnum);
	sort_arr(&Arr);
	show_arr(&Arr);
	printf("\n��ɾ��������Ϊ��%d\n",delnum);
	inversion_arr(&Arr);
	show_arr(&Arr);
	printf("\n");
	
	return 0;
}
void init_arr(Array *parr,int length)
{
	parr->pBase=(int *)malloc(sizeof(int)*length);
	memset(parr->pBase,0,sizeof(int)*length);
	if(parr->pBase==NULL)
	{
		printf("��Ǹ����ʼ��ʧ�ܣ�");
        exit(1);
	}
	else
	{
		parr->len=length;
		parr->cnt=0;
	}

}
void show_arr(Array *parr)
{
	int i=0;
	for(;i<(parr->cnt);i++)
	{
		printf("%d ",parr->pBase[i]);
	}
}
bool is_full(Array *parr)
{
	if(parr->cnt>=parr->len)
		return true;
	if(parr->cnt<parr->len)
		return false;
}
bool is_empty(Array *parr)
{
	if(parr->cnt==0)
		return true;
	else
		return false;
}
bool append_arr(Array *parr,int value)
{
	if(is_full(parr))
		return false;
	else
	{
		parr->pBase[parr->cnt]=value;
		(parr->cnt)++;
		return true;
	}
}
bool insert_arr(Array *parr,int pos,int invalue)
{
	int i=parr->cnt;
	if(is_full(parr)||pos>parr->cnt||is_empty(parr))
		return false;
	for(;i>pos;i--)
	{
		parr->pBase[i]=parr->pBase[i-1];
	}
	parr->pBase[pos]=invalue;
	(parr->cnt)++;
	return true;
}
bool delete_arr(Array *parr,int pos,int *dlnum)
{
	int i;
	if(is_empty(parr))
		return false;
	*dlnum=parr->pBase[pos-1];
	for(i=pos-1;i<(parr->cnt)-1;i++)
	{
		parr->pBase[i]=parr->pBase[i+1];
	}
    (parr->cnt)--;
	return true;
}
void sort_arr(Array *parr)
{
	int i=0,j,t;
	for(;i<(parr->cnt)-1;i++)
	{
		for(j=i+1;j<=(parr->cnt)-1;j++)
		{
			if(parr->pBase[i]<parr->pBase[j])
			{
				t=parr->pBase[i];
				parr->pBase[i]=parr->pBase[j];
				parr->pBase[j]=t;
			}
		}
	}
}
void inversion_arr(Array *parr)
{
	int t,i,j;
	i=0;
	j=(parr->cnt)-1;
	for(;i<j;i++,j--)
	{
		t=parr->pBase[i];
		parr->pBase[i]=parr->pBase[j];
		parr->pBase[j]=t;
	}
}
