#include <stdio.h>

#define INFINITY 65535
#define VERTEXT_NUMBER 3

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
// int graph[VERTEXT_NUMBER][VERTEXT_NUMBER] = {
	// {0,6,1,5,INFINITY,INFINITY},
	// {6,0,5,INFINITY,3,INFINITY},
	// {1,5,0,5,6,4},
	// {5,INFINITY,5,0,INFINITY,2},
	// {INFINITY,3,6,INFINITY,0,6},
	// {INFINITY,INFINITY,4,2,6,0},
	
// };
int graph[VERTEXT_NUMBER][VERTEXT_NUMBER] = {
{0,990,692},
{990,0,179},
{692,179,0}	
};

int treeNode[VERTEXT_NUMBER];    
int edgeCost[VERTEXT_NUMBER];
int visited[VERTEXT_NUMBER];
int nodeCnt;

void Prim(){
	int tmpVer,tmpWeight,minEdge;
	edgeCost[0] = INFINITY;
	visited[0] = 1;
	treeNode[0] = 0;
	// for( int i=0;i<VERTEXT_NUMBER;i++){
		// printf(" %d ",visited[i]);
		
	// }
	for(int i = 1;i < VERTEXT_NUMBER; i++ ){
		minEdge = INFINITY;
		for( int j = 0 ; j < VERTEXT_NUMBER ;j++){//在已有的顶点内寻找，权值最少的边，并且改变的另一个顶点不在已有集合内
			if( 1 == visited[j] ){
				for( int  k =0; k < VERTEXT_NUMBER ; k++){
					if(  0 == visited[k] && graph[j][k] < minEdge && graph[j][k] != 0){
						tmpVer = k;
						tmpWeight = graph[j][k];
						minEdge = tmpWeight;
						// printf("j: %d,k:%d,minEdge:%d,tmpVer:%d\n",j,k,minEdge,tmpVer);
					}
				}
				
			}
			
			
		}
		treeNode[i] = tmpVer;
		visited[tmpVer] = 1;
		edgeCost[i] = tmpWeight;
	
	 }
	
	
}

int main(){
	Prim();
	for(int i=0;i<VERTEXT_NUMBER;i++){
		printf(" %d ",treeNode[i]);
	}
	printf("\n------------------------\n");
	for(int i=0;i<VERTEXT_NUMBER;i++){
		printf(" %d ",edgeCost[i]);
	}
	printf("\n");
	return 0;
}

