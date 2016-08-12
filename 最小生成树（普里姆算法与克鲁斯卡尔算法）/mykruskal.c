#include <stdio.h>

#define INFINITY 65535
#define VERTEXT_NUMBER 6
//要用到并查集的知识，因为要查找两个节点是否在同一科书中
typedef struct edge{
	int begin;
	int end;
	int weight;
}Edge;

// int graph[VERTEXT_NUMBER][VERTEXT_NUMBER] = {
	// {0,1,5,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY},
	// {1,0,3,7,5,INFINITY,INFINITY,INFINITY,INFINITY},
	// {5,3,0,INFINITY,1,7,INFINITY,INFINITY,INFINITY},
	// {INFINITY,7,INFINITY,0,2,INFINITY,3,INFINITY,INFINITY},
	// {INFINITY,5,1,2,0,3,6,9,INFINITY},
	// {INFINITY,INFINITY,7,INFINITY,3,0,INFINITY,5,INFINITY},
	// {INFINITY,INFINITY,INFINITY,3,6,INFINITY,0,2,7},
	// {INFINITY,INFINITY,INFINITY,INFINITY,9,5,2,0,4},
	// {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,7,4,0}
// };
int graph[VERTEXT_NUMBER][VERTEXT_NUMBER] = {
	{0,6,1,5,INFINITY,INFINITY},
	{6,0,5,INFINITY,3,INFINITY},
	{1,5,0,5,6,4},
	{5,INFINITY,5,0,INFINITY,2},
	{INFINITY,3,6,INFINITY,0,6},
	{INFINITY,INFINITY,4,2,6,0},
	
};
Edge graEdge[ (VERTEXT_NUMBER * VERTEXT_NUMBER)];
Edge treeEdge[VERTEXT_NUMBER];
int preNode[VERTEXT_NUMBER];


/** void quicksort(long *arr,int start,int last)
 *\brief 快速排序，在原数组的基础上进行排序
 *
 * \param start：进行排序的数组的起点下标
 * \param last：进行排序的数组的终点下标,排序数组包含该下标的元素
 * \return 无
 *
 */
void quicksort(Edge *arr,int start,int last){
    if(start>=last){
        return ;
    }
    int left=start,right=last,pos=start+1;
	Edge tmp,pivotValue=arr[start];
    while(left!=right){
        if(arr[pos].weight>pivotValue.weight){
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

//查找并查集中的祖先元素
int find(int nodeA){
	int anceA=preNode[nodeA],tmp;
	//如果他不是根节点，循环，直至找到根节点
	while(anceA != preNode[anceA]){
		anceA = preNode[anceA];
	}
	//压缩并查集，让一课集合内的节点都指向一个根（代表元素）
	while(anceA != preNode[nodeA]){
		tmp = preNode[nodeA];
		preNode[nodeA] = anceA;
		nodeA = tmp;
	}
	return anceA;
}

//合并两个集合的根节点（代表元素）
void merge(int unionA,int unionB){
	preNode[unionB] = unionA;
}

int Kruskal(){
	int treeWeight = 0;
	int edgeCnt=0; //记录已遍历多少条边
	int treeEdgeCnt = 0;
	int beParent,endParent;
	for(int i= 0 ; i < VERTEXT_NUMBER ;i++){	
		//初始化并查集
		preNode[i] = i;
	}
	//最小生成树有n-1条边，n为节点数
	while( treeEdgeCnt < (VERTEXT_NUMBER-1)){
		//如果这条边上的两个节点的祖先不一样，把它们相连，它们的相连不会造成回环，以为它们属于不同的树（集合）
		if( (beParent = find(graEdge[edgeCnt].begin)) !=  (endParent = find(graEdge[edgeCnt].end)) ){
			treeEdge[treeEdgeCnt] = graEdge[edgeCnt];
			treeEdgeCnt++;
			treeWeight += graEdge[edgeCnt].weight;	
			merge(graEdge[edgeCnt].begin,graEdge[edgeCnt].end);
			printf("treeWeight:%d\n",treeWeight);
		}
		edgeCnt++;
	}
	return treeWeight;
	
}


int main(){
	int min;
	int edgeCnt=0;
	for(int i = 0 ; i < VERTEXT_NUMBER ; i++ ){
		for(int j = 0 ; j < VERTEXT_NUMBER ; j++){
			if( graph[i][j] != 0 && INFINITY != graph[i][j] ){
				graEdge[edgeCnt].begin = i ;
				graEdge[edgeCnt].end = j ;
				graEdge[edgeCnt].weight = graph[i][j] ;
				// printf("begin:%d,end:%d,weight:%d\n",graEdge[edgeCnt].begin,graEdge[edgeCnt].end,graEdge[edgeCnt].weight);
				edgeCnt++;
			}
		}
	}
	quicksort(graEdge,0,edgeCnt-1);
	min = Kruskal();
	for(int  i = 0; i< (VERTEXT_NUMBER-1) ;i++){
		printf("begin:%d,end:%d,weight:%d\n",treeEdge[i].begin,treeEdge[i].end,treeEdge[i].weight);
	}
	printf("min:%d\n",min);
	return 0;
}
