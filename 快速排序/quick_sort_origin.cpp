#include <iostream>
using namespace std;
#define N 10010
//这是原始版的快速排序，直接按照快排的思想来写的，较为容易理解
void quicksort(long *arr,int start,int last){
    if(start>=last){
        return ;
    }
    long* tmp=new long[(last+1-start)];
    int left=0,right=last-start,pivotValue=arr[start];
    int arrPos=start+1;
    while(arrPos<=last){
        if(arr[arrPos]>pivotValue){
            tmp[right--]=arr[arrPos];
        }else{
            tmp[left++]=arr[arrPos];
        }
        arrPos++;
    }
    tmp[left]=pivotValue;
    for(int i=start,j=0;i<=last;j++,i++){
        arr[i]=tmp[j];
    }
    delete tmp;
    quicksort(arr,start,left+start-1);
    quicksort(arr,start+left+1,last);
}
int main()
{
    long a[N]={0};
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    quicksort(a,0,n-1);
    cout<<a[(int)(n/2)];
//    for(int i=0;i<8;i++){
//        cout<<a[i]<<endl;
//    }
    return 0;
}
