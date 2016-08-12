#include <stdio.h>

#define INFINITY 655350
#define VERTEXT_NUMBER 1000
//题目大意：每个田都有一头牛，它们都要去到某个田里面矩形聚会，然后又返回，按最短路径来回，求牛来回的最大时间

//这道题用迪杰斯特拉算法要用一些逆向思维，多头牛走向同一个目的地可以想象为目的地向多头牛靠近。所以起始点应该设置为目的地（即要举行聚会的农场）
//一头牛来回的最短路径之所以有所不同是因为该邻接矩阵是有向的。
//所以要算来回的时间，只需要把邻接矩阵逆向，来再求一次（不能理解的话，可以用草稿字把图画出来，这就容易理解了）
typedef struct graph{
	int vertexNum;//顶点的数量
	int adjList[VERTEXT_NUMBER][VERTEXT_NUMBER];//邻接表
}Graph;

//route数组存放的是在最短路径中该节点的前驱节点
//返回值为起始点verStart到终点verEnd之间最短路径的权值
void Dijktra(Graph dstGraph,int verStart,int *pathWeight){
	int i,j,min,tmpVer;
	int visited[dstGraph.vertexNum];
	
	for(i = 0; i < dstGraph.vertexNum ;i++ ){
		pathWeight[i] = dstGraph.adjList[verStart][i];
		visited[i] = 0;
	}
	pathWeight[verStart] = 0;
	visited[verStart] = 1;
	
	//每一个循环扩展一个节点
	for( i = 0 ; i < dstGraph.vertexNum ; i++ ){
		min = INFINITY;
		for( j = 0 ; j < dstGraph.vertexNum ; j++ ){
			if( 0 == visited[j] && pathWeight[j] < min ){
				min = pathWeight[j];
				tmpVer = j;
			}
		}
		
		visited[tmpVer] = 1;
		//更新最短路径
		for( j = 0; j < dstGraph.vertexNum ; j++ ){
			if( 0 == visited[j] && (pathWeight[tmpVer] + dstGraph.adjList[tmpVer][j]) < pathWeight[j] ){
				pathWeight[j] = (pathWeight[tmpVer] + dstGraph.adjList[tmpVer][j]);
			}
		}
		
	}
	
}

//这是有向图逆转才有意义
//把路的方向逆转，就可以求到牛返回农场的最短路径
void ReverseAdjacentMatrix(Graph *dstGraph){
	int tmp = 0;
	for(int i = 0; i < dstGraph->vertexNum ; i++ ){
		for(int j = 0 ; j < i; j++ ){
			tmp = dstGraph->adjList[i][j];
			dstGraph->adjList[i][j] = dstGraph->adjList[j][i];
			dstGraph->adjList[j][i] = tmp;
			
		}
	}
	
}

int main(void){
	int n,m,x,a,b,t,maxLaihui,tmp;
	Graph mygraph;
	int goPathWeight[VERTEXT_NUMBER],backPathWeight[VERTEXT_NUMBER];
	//n个牛场，n头牛，m条路，在x号农场举行聚会
	scanf("%d%d%d",&n,&m,&x);
	mygraph.vertexNum = n;
	for(int i = 0 ; i < n ; i++ ){
		for(int j = 0 ; j  < n ; j++ ) {
			mygraph.adjList[i][j] = (j == i ) ? 0 : INFINITY; 
		}
	}
	
	for(int j = 0 ; j < m ; j++ ){
		scanf("%d%d%d",&a,&b,&t);
		//输入是从1开始算起的，而计算机是从0开始算起的所以要减一
		mygraph.adjList[(a-1)][(b-1)] = t;
	}
	
	// printf("\n------------------------\n");
	// for(int i = 0 ; i < n ; i++ ){
		// for(int j = 0 ; j  < n ; j++ ){
			// printf("%d ",mygraph.adjList[i][j]);
		// }
		// printf("\n");
	// }
	// printf("\n------------------------\n");
	

	Dijktra(mygraph,(x-1),goPathWeight);
	ReverseAdjacentMatrix( &mygraph );
	Dijktra(mygraph,(x-1),backPathWeight);
	
	// for(int i = 0 ; i < n ; i++ ){
		// for(int j = 0 ; j  < n ; j++ ){
			// printf("%d ",mygraph.adjList[i][j]);
		// }
		// printf("\n");
	// }
	// printf("\n------------------------\n");
	
	maxLaihui = 0;
	for(int i = 0 ; i < n ; i++ ){	
		// printf("gopathWeight[%d]:%d,backPathWeight[%d]:%d\n",i,goPathWeight[i],i,backPathWeight[i]);
		if( ( goPathWeight[i] + backPathWeight[i] ) > maxLaihui){
			maxLaihui = goPathWeight[i] + backPathWeight[i];
		}

	}
	printf("%d\n",maxLaihui);
	return 0;
}



