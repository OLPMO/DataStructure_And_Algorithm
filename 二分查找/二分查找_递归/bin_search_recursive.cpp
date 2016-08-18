#include <iostream>

using namespace std;
/**int bin_search(int* arr,key,int start,int last)
 * \brief 对排序好的数组进行二分查找,
 *        O(n)=logn,底数为2
 * \param arr：需要查找的数组
 * \param key：被查找的值
 * \param start：开始查找的位置
 * \param last：查找的结束位置（包含在查找范围内）
 * \return 若找到，返回位置值；没找到，返回-1
 *
 */

int bin_search(int* arr,int key,int start,int last){
    if(start>last){
        return -1;
    }
    int middle=(int)((last-start)/2)+start;
    if(key>arr[middle]){
        return bin_search(arr,key,middle+1,last);
    }else if(key<arr[middle]){
        return bin_search(arr,key,start,middle-1);
    }else{
        return middle;
    }
}

int main()
{
    int a[]={1,6,8,9,11};

    for(int i=0;i<14;i++){
        cout<<"the key is:"<<i<<"--";
        cout<<"the pos is:"<<bin_search(a,i,0,4)<<endl;
    }

    return 0;
}
