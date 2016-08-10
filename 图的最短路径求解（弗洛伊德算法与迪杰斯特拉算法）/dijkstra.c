#include <stdio.h>

#define INFINITY 65535
#define VERTEXT_NUMBER 9
typedef struct graph{

	int vertexNum;//顶点的数量
	int adjList[VERTEXT_NUMBER][VERTEXT_NUMBER];//邻接表
}Graph;

//route数组存放的是在最短路径中该节点的前驱节点
//返回值为起始点verStart到终点verEnd之间最短路径的权值
//route存放的是该节点的前驱节点
//pathWeight存放的是起点到该点的最短路径的权值
int Dijktra(Graph dstGraph,int verStart,int verEnd,int *pathWeight,int *route){
	int i,j,min,tmpVer;
	int visited[dstGraph.vertexNum];
	
	for(i = 0; i < dstGraph.vertexNum ;i++ ){
		pathWeight[i] = dstGraph.adjList[verStart][i];
		visited[i] = 0;
		if( INFINITY != dstGraph.adjList[verStart][i]){
			route[i] = verStart;
		}else{
			route[i] = INFINITY;
		}
		
	}
	pathWeight[verStart] = 0;
	route[verStart] = verStart;
	visited[verStart] = 1;
	
	//每一个循环扩展一个节点
	for( i = 0 ; i < dstGraph.vertexNum ; i++ ){
		min = INFINITY;
		for( j = 1 ; j < dstGraph.vertexNum ; j++ ){
			if( 0 == visited[j] && pathWeight[j] < min ){
				min = pathWeight[j];
				tmpVer = j;
			}
		}
		
		visited[tmpVer] = 1;
		for( j = 0; j < dstGraph.vertexNum ; j++ ){
			if( 0 == visited[j] && (pathWeight[tmpVer] + dstGraph.adjList[tmpVer][j]) < pathWeight[j] ){
				route[j] = tmpVer;
				pathWeight[j] = (pathWeight[tmpVer] + dstGraph.adjList[tmpVer][j]);
			}
		}
		
	}
	return pathWeight[verEnd];
}

int main(void){
	int table[VERTEXT_NUMBER][VERTEXT_NUMBER] = {
	{0,1,5,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY},
	{1,0,3,7,5,INFINITY,INFINITY,INFINITY,INFINITY},
	{5,3,0,INFINITY,1,7,INFINITY,INFINITY,INFINITY},
	{INFINITY,7,INFINITY,0,2,INFINITY,3,INFINITY,INFINITY},
	{INFINITY,5,1,2,0,3,6,9,INFINITY},
	{INFINITY,INFINITY,7,INFINITY,3,0,INFINITY,5,INFINITY},
	{INFINITY,INFINITY,INFINITY,3,6,INFINITY,0,2,7},
	{INFINITY,INFINITY,INFINITY,INFINITY,9,5,2,0,4},
	{INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,7,4,0}
	};
	Graph mygraph;
	int pathWeight[VERTEXT_NUMBER],route[VERTEXT_NUMBER],sv;
	mygraph.vertexNum = 9;
	
	
	
	for(int i = 0;i<VERTEXT_NUMBER;i++){
		for(int j = 0 ;j<VERTEXT_NUMBER;j++){
			mygraph.adjList[i][j] = table[i][j];
			
		}
		
		
	}
	sv = Dijktra(mygraph,0,8,pathWeight,route);
	
	printf("sv:%d\n",sv);
	for( int i=0; i<9;i++){
		printf("  %d  ",route[i]);
	}
	printf("\n");
	for( int i=0; i<9;i++){
		printf("  %d  ",pathWeight[i]);
	}
	printf("\n");
	return 0;
}

