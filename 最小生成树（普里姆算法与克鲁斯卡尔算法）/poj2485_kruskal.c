#include <stdio.h>
////本代码使用克鲁斯卡尔算法解决POJ的第2485题
#define INFINITY 655350
#define MAX_VERTEXT_NUMBER 600
//要用到并查集的知识，因为要查找两个节点是否在同一科书中
typedef struct edge{
	int begin;
	int end;
	int weight;
}Edge;

int graph[MAX_VERTEXT_NUMBER][MAX_VERTEXT_NUMBER];
Edge graEdge[ (MAX_VERTEXT_NUMBER * MAX_VERTEXT_NUMBER)];
Edge treeEdge[MAX_VERTEXT_NUMBER];
int preNode[MAX_VERTEXT_NUMBER];
int nodeNum;
//记录边的数目
int edgeCnt;

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
	int edgeMaxWeight = 0;
	int edgeCnt=0; //记录已遍历多少条边
	int treeEdgeCnt = 0;
	int beParent,endParent;
	for(int i= 0 ; i < nodeNum ;i++){	
		//初始化并查集
		preNode[i] = i;
	}
	//最小生成树有n-1条边，n为节点数
	while( treeEdgeCnt < (nodeNum-1)){
		if( (beParent = find(graEdge[edgeCnt].begin)) !=  (endParent = find(graEdge[edgeCnt].end)) ){
			treeEdge[treeEdgeCnt] = graEdge[edgeCnt];
			treeEdgeCnt++;
			if( graEdge[edgeCnt].weight > edgeMaxWeight){
				edgeMaxWeight = graEdge[edgeCnt].weight ;
			}
			merge(beParent,endParent);
			// printf("treeWeight:%d\n",treeWeight);
		}
		edgeCnt++;
	}
	return edgeMaxWeight;
	
}

void ChangeToEdge(){
	edgeCnt = 0;
	for(int i = 0 ; i < nodeNum ; i++ ){
		for(int j = 0 ; j < nodeNum ; j++){
			if( graph[i][j] != 0 && INFINITY != graph[i][j] ){
				graEdge[edgeCnt].begin = i ;
				graEdge[edgeCnt].end = j ;
				graEdge[edgeCnt].weight = graph[i][j] ;		
				edgeCnt++;
			}
		}
	}
	
}

int main(){
	int maxedge;
	int t,i,j,k;
	scanf("%d",&t);
	for( i =0; i < t ; i++){
		scanf("%d",&nodeNum);
		for( j = 0 ; j < nodeNum ; j++){
			for( k = 0 ; k < nodeNum ; k++){
				scanf("%d",&graph[j][k]);
			}
		}
		//把邻接矩阵转换的边提取出来
		ChangeToEdge();
		quicksort(graEdge,0,edgeCnt-1);
		maxedge = Kruskal();
		printf("%d\n",maxedge);
	}

	return 0;
}
