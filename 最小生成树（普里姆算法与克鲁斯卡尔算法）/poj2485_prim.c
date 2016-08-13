

#include <stdio.h>

#define INFINITY 655350
#define VERTEXT_NUMBER 1000

//本代码使用普里姆算法解决POJ的第2485题
int graph[VERTEXT_NUMBER][VERTEXT_NUMBER];

int treeNode[VERTEXT_NUMBER];    
int edgeCost[VERTEXT_NUMBER];
int visited[VERTEXT_NUMBER];
int maxTreeEdge;
int nodeNum ;

void Prim(){
	int tmpVer,tmpWeight,minEdge;
	edgeCost[0] = INFINITY;
	visited[0] = 1;
	maxTreeEdge = 0;
	for(int i = 1;i < nodeNum; i++ ){
		minEdge = INFINITY;
		for( int j = 0 ; j < nodeNum ;j++){//在已有的顶点内寻找，权值最少的边，并且改变的另一个顶点不在已有集合内
			if( 1 == visited[j] ){
				for( int  k =0; k < nodeNum ; k++){
					if(  0 == visited[k] && graph[j][k] != 0 && graph[j][k] < minEdge ){
						tmpVer = k;
						tmpWeight = graph[j][k];
						minEdge = tmpWeight;
					}
				}
				
			}
			
			
		}
	
		visited[tmpVer] = 1;
		edgeCost[i] = tmpWeight;
		if( tmpWeight > maxTreeEdge ){
			maxTreeEdge = tmpWeight;
		}
	}
	
	
}

int main(){
	int t,i,j,k;
	scanf("%d",&t);
	for( i =0; i < t ; i++){
		scanf("%d",&nodeNum);
		for( j = 0 ; j < nodeNum ; j++){
			visited[j] = 0;
			edgeCost[j] = 0;
			for( k = 0 ; k < nodeNum ; k++){
				scanf("%d",&graph[j][k]);
			}
		}
		Prim();
		printf("%d\n",maxTreeEdge);
	}
	
	
	return 0;
}

