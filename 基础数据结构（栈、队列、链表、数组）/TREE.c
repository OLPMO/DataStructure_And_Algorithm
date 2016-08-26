#include<stdio.h>
#include<stdlib.h>
typedef struct tree
{
    int data;
    struct tree *pRTree;
    struct tree *pLTree;
}Tree;
struct tree * createtree()//因为函数内的是栈空间，一退出函数就会把空间都释放掉，所以要用手动分配的方式建树
{
	Tree *ptnode1=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode2=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode3=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode4=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode5=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode6=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode7=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode8=(Tree *)malloc(sizeof(Tree));
	Tree *ptnode9=(Tree *)malloc(sizeof(Tree));
	ptnode1->data=1;
	ptnode1->pRTree=ptnode5;
	ptnode1->pLTree=ptnode2;
	ptnode2->data=2;
	ptnode2->pRTree=ptnode4;
	ptnode2->pLTree=ptnode3;
	ptnode3->data=3;
	ptnode4->data=4;
	ptnode3->pRTree=NULL;
	ptnode3->pLTree=NULL;
	ptnode4->pLTree=NULL;
	ptnode4->pRTree=NULL;
	ptnode5->data=5;
	ptnode5->pRTree=ptnode7;
	ptnode5->pLTree=ptnode6;
	ptnode6->data=6;
	ptnode6->pLTree=NULL;
	ptnode6->pRTree=NULL;
	ptnode7->data=7;
	ptnode7->pRTree=NULL;
	ptnode7->pLTree=ptnode8;
	ptnode8->data=8;
	ptnode8->pRTree=ptnode9;
	ptnode8->pLTree=NULL;
	ptnode9->data=9;
	ptnode9->pLTree=NULL;
	ptnode9->pRTree=NULL;
	return ptnode1;
}
void xiantraverse(struct tree *pt)
{
	if(pt!=NULL)
	{
		printf("%d ",pt->data);
		if(pt->pLTree!=NULL)
		{
			xiantraverse(pt->pLTree);
		}
		if(pt->pRTree!=NULL)
     	{
			xiantraverse(pt->pRTree);
		}
	}
}
void middletraverse(struct tree *pt)
{
	if(pt!=NULL)
	{
		
		if(pt->pLTree!=NULL)
		{
			middletraverse(pt->pLTree);
		}
		printf("%d ",pt->data);
		if(pt->pRTree!=NULL)
     	{
			middletraverse(pt->pRTree);
		}
	}
}
void lasttraverse(struct tree *pt)
{
	if(pt!=NULL)
	{
		
		if(pt->pLTree!=NULL)
		{
			lasttraverse(pt->pLTree);
		}
		
		if(pt->pRTree!=NULL)
     	{
			lasttraverse(pt->pRTree);
		}
		printf("%d ",pt->data);
	}
}
int main()
{
	Tree *pt;
    pt=createtree();
	//printf("%d\n",pt->pRTree->data);
 //   xiantraverse(pt);
//	middletraverse(pt);
	lasttraverse(pt);
    return 0;
}