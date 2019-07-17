#include <stdio.h>
#include <iostream>
using namespace std;

void swap(int *a,int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void HeapAdjust(int a[],int inode,int length){
	int child;
	//建的时候是从底向上建，就能保证所有父节点都大于其子节点。排序的时候因为都是和最底下的叶子节点交换，所以便需要从顶向下维护堆
	for(int i = inode ; 2*i<=length ; i = child){
		if( (2*i+1) <= length){
			child = a[2*i]>a[2*i+1]?(2*i):(2*i+1);
		}else if((2*i) <=length){
			child = 2*i;
		}
		if(a[i]<a[child]){
			swap(&a[i],&a[child]);
		}else{
			break;
		}
	}
	
}
//a是待排序数组，length是数组长度,升序 （排序数组的下标以1为起点）
void heapsort(int a[],int length){
	//从最后一个非叶子节点开始维护堆，因为是完全二叉树，所以最后一个非叶子节点之前的节点都是非叶子节点
	for(int i=length/2;i>0;i--){
		HeapAdjust(a,i,length);
	}
	// for(int i=1;i<=8;i++){
		// cout<<a[i]<<" ";
	// }
	// cout<<endl;
	for(int i = length;i>1;i--){
		swap(&a[1],&a[i]);
		HeapAdjust(a,1,i-1);
	}
}
//排序数组的下标以1为起点
int main(void){
	int a[]={0,4,5,12,45,23,22,12,11};
	heapsort(a,8);
	cout<<"after sort:"<<endl;
	for(int i=1;i<=8;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	return 0;
}