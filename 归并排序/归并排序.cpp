#include <iostream>

using namespace std;
/********************************************//**
 *int* mymerge(int* leftArr,int* rightArr,int leftLength,int rightLength)
 *\brief �������������ϲ������ϲ���������������
 *Ĭ�����������򣨴�С����,���ϲ������鶼���Ѿ��ź����
 * \param leftArr�������飬�����ϲ��ĵ�һ������
 * \param rightArr�������飬���ϲ��ĵڶ�������
 * \param leftLength������������鳤��
 * \param rightLength������������鳤��
 * \return �ϲ��õ������ַ��ͷָ�룩
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
 * \brief �ù鲢�����Ŀ������������򣬷���������������
 * \param arr:Ŀ������
 * \param start����Ŀ���������±�Ϊstart������ʼ����
 * \param length��Ҫ����ĸ���
 * \return ������������
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
