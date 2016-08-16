#include <iostream>
using namespace std;
#define N 10010
/*快排时间复杂度的理解
*快速排序每次将待排序数组分为两个部分，在理想状况下，每一次都将待排序数组划分成等长两个部分，则需要logn次划分，底数为2。然而每*一次都要经过n次比较运算才能对其进行划分，所以理想情况下其空间复杂度为O(nlogn)，O(n)=nlogn，底数为2
*而在最坏情况下，即数组已经有序或大致有序的情况下，每次划分只能减少一个元素，即每次划分后左边或右边这有一个数，而另一边则由n-2
*个数。此时，快速排序将不幸退化为冒泡排序，所以快速排序最坏情况的O（n）为O(n^2)。
*所以，快排的时间复杂度下界为O(nlogn)，而上限则为O(n^2)。在实际应用中，快速排序的平均时间复杂度为O(nlogn)。
*/
/** void quicksort(long *arr,int start,int last)
 *\brief 快速排序，在原数组的基础上进行排序
 *
 * \param start：进行排序的数组的起点下标
 * \param last：进行排序的数组的终点下标
 * \return 无
 *
 */
void quicksort(long *arr,int start,int last){
    if(start>=last){
        return ;
    }
    int left=start,right=last,pos=start+1;
    long pivotValue=arr[start],tmp=0;
    while(left!=right){
        if(arr[pos]>pivotValue){
            //由于两个数进行了交换，pos位置的值是新值，所以不用后移
            tmp=arr[right];
            arr[right--]=arr[pos];
            arr[pos]=tmp;
        }else{
            arr[left++]=arr[pos];
            pos++;
        }
    }
    arr[left]=pivotValue;
    quicksort(arr,start,left-1);
    quicksort(arr,left+1,last);
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
//    quicksort(a,0,6);
//    for(int i=0;i<7;i++){
//        cout<<a[i]<<endl;
//    }
    return 0;
}
