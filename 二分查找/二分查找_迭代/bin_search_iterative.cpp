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
//迭代实现
int bin_search_iterative(int* arr,int key,int start,int last){
    int middle;
    while(start<=last){
        middle=(int)((last-start)/2)+start;
        if(key>arr[middle]){
        //若要查找的值在右边，就可以扩大左边界
            start=middle+1;
        }else if(key<arr[middle]){
        //若要查找的值在左边，就可以缩小右边界
            last=middle-1;
        }else{
            return middle;
        }
    }
    return -1;
}

int main()
{
    int a[]={1,6,9,11};
    for(int i=0;i<14;i++){
        cout<<"the key is:"<<i<<"--";
        cout<<"the pos is:"<<bin_search_iterative(a,i,0,3)<<endl;
    }
    return 0;
}
