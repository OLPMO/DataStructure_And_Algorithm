#include <iostream>
#define NMAX 500010
using namespace std;
long long cnt=0;
//直接对arr进行操作
//right 为右边的不可以取的尽头的值。
void mymerge(long long* newArr,long long *arr,int left,int middle,int right){
    long leftPos=left,rightPos=middle;
    bool leftEndFlag=false,rightEndFlag=false;
    if(1==(right-left)){
        newArr[left]=arr[left];
        return;
    }
    for(long i=left;i<right;i++){
        if(!leftEndFlag&&!rightEndFlag){
            if(arr[leftPos]<=arr[rightPos]){
                newArr[i]=arr[leftPos++];
                if(leftPos>=middle){
                    leftEndFlag=true;
                }
            }else{
                newArr[i]=arr[rightPos++];
                //要加上leftPos右边的值的个数，因为右边的值都比leftPos的值大
                //所以leftPos右边的值也都会比当前的右端的值大，而一旦当前右端的值过去以后
                //这些情况就会被忽略，计数器的值就会偏小
                cnt=cnt+(middle-leftPos);
                if(rightPos>=right){
                    rightEndFlag=true;
                }
            }
        }else if(leftEndFlag){
            newArr[i]=arr[rightPos++];

        }else if(rightEndFlag){
            newArr[i]=arr[leftPos++];
        }
    }
    for(int i=left;i<right;i++){
        arr[i]=newArr[i];
    }
}
void  MergeSort(long long* sortArr,long long* arr,int start,int length){
    long middle=(long)(length/2)+start;
    if(length>=3){
        MergeSort(sortArr,arr,start,middle-start);
        MergeSort(sortArr,arr,middle,start+length-middle);
    }else if(2==length){
        return mymerge(sortArr,arr,start,start+1,start+2);
    }else{
        return mymerge(sortArr,arr,start,middle,start+1);
    }
    mymerge(sortArr,arr,start,middle,start+length);
    return;
}
int main(){
    long long a[NMAX]={0},sorta[NMAX]={0};
    long i=0,n=0;
    cin>>n;
    while(0!=n){
        cnt=0;
        for(i=0;i<n;i++){
            cin>>a[i];
        }
        MergeSort(sorta,a,0,n);
        cout<<cnt<<endl;
        cin>>n;
    }
//    long a[]={9,1,0,5,4,3},sorta[6];
//    MergeSort(sorta,a,0,6);
//  //  mymerge(sorta,a,0,1,2);
//    for(int i=0;i<6;i++){
//        cout<<sorta[i]<<"  ";
//    }
//    cout<<"cnt:"<<cnt<<endl;
    return 0;
}
