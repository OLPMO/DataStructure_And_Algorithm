#include <iostream>

using namespace std;
/********************************************//**
 *int* mymerge(int* leftArr,int* rightArr,int leftLength,int rightLength)
 *\brief 用于数组的有序合并，即合并完后是有序的数组
 *默认排序是升序（从小到大）,被合并的数组都是已经排好序的
 * \param leftArr：左数组，即被合并的第一个数组
 * \param rightArr：右数组，被合并的第二个数组
 * \param leftLength：左数组的数组长度
 * \param rightLength：右数组的数组长度
 * \return 合并好的数组地址（头指针）
 *
 ***********************************************/
int* mymerge(int* leftArr,int* rightArr,int leftLength,int rightLength){
    int length=leftLength+rightLength,leftPos=0,rightPos=0;
    int* tmp=new int[length];
    bool leftEndFlag=false,rightEndFlag=false;
    for(int i=0;i<length;i++){
        if(!leftEndFlag&&!rightEndFlag){
            if(leftArr[leftPos]<=rightArr[rightPos]){
                tmp[i]=leftArr[leftPos++];
                if(leftPos>=leftLength){
                    leftEndFlag=true;
                }
            }else{
                tmp[i]=rightArr[rightPos++];

                if(rightPos>=rightLength){
                    rightEndFlag=true;
                }
            }
        }else if(leftEndFlag){
            tmp[i]=rightArr[rightPos++];
        }else if(rightEndFlag){
            tmp[i]=leftArr[leftPos++];
        }
    }
    return tmp;
}
/********************************************//**
 *int* MergeSort(int* arr,int start,int length)
 * \brief 用归并排序对目标数组进行排序，返回排序后的新数组
 * \param arr:目标数组
 * \param start：从目标数组中下标为start的数开始排序
 * \param length：要排序的个数
 * \return 排序后的新数组
 *
 ***********************************************/
int* MergeSort(int* arr,int start,int length){
    int *leftTmp,*rightTmp,*tmp,*oneTmp=new int[1];
    int middle=(int)(length/2)+start;
    int a[1],b[1];
    if(length>=3){
        leftTmp=MergeSort(arr,start,middle-start);
        rightTmp=MergeSort(arr,middle,start+length-middle);
    }else if(2==length){
        a[0]=arr[start];
        b[0]=arr[start+1];
        return mymerge(a,b,1,1);
    }else{
        oneTmp[0]=arr[start];
        return oneTmp;
    }
    tmp=mymerge(leftTmp,rightTmp,middle-start,start+length-middle);
    delete leftTmp;
    delete rightTmp;
    return tmp;
}
int main(){
//    int a[]={8},b[]={4};
//    int acnt=sizeof(a)/sizeof(int),bcnt=sizeof(b)/sizeof(int);
//    int* merArr=mymerge(a,b,acnt,bcnt);
//    for(int i=0;i<acnt+bcnt;i++){
//        cout<<merArr[i]<<endl;
//    }
    int a[]={9,1};
    int *b=MergeSort(a,0,2);
    for(int i=0;i<2;i++){
        cout<<b[i]<<endl;
    }
    return 0;
}
