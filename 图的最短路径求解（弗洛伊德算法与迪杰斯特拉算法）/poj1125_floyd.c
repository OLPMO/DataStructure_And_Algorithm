
//poj1125很明显用弗洛伊德算法，因为这是一个多源最短路径求解

#include <stdio.h>
#define INFINITY 655350
#define VERTEXT_NUMBER 200
//弗洛伊德算法算法可以说是动态规划的一个应用，如果没了解过动态规划，建议先去了解，有了动态规划的基础知识就很容易理解核心的动态
//转移方程了，也就很好理解那个三重循环
int graph[VERTEXT_NUMBER][VERTEXT_NUMBER];

int path[VERTEXT_NUMBER][VERTEXT_NUMBER];
int t;
void Floyd(){
	/*
	*其状态转移方程如下： map[i,j]:=min{map[i,k]+map[k,j],map[i,j]}；
	*	map[i,j]表示i到j的最短距离，K是穷举i,j的断点，map[n,n]初值应该为0，或者按照题目意思来做。
	*	当然，如果这条路没有通的话，还必须特殊处理，比如没有map[i,k]这条路。----引自百度百科
	*/
	//循环VERTEXT_NUMBER次，每一次构造一个状态（矩阵），下一个状态的转移与上一个状态的结构又相互关联
	//通俗来讲，每次循环循环，都是把k点作为中间点，寻找i、j两点间的最短路径。但是，用k点作为中间点寻找最短路径时，又可以
	//需要用k-1点结果。例如:a,b,c,d 四个点，a与d相隔两个点分别为b和c，要寻找a与d点的最短路径，就要通过a与c点间的最短路径
	//而a与c点的最短路径，是以b为中间点求取的。
	//也就是说单纯以b点或c点为中间点求取a点与d点的最短距离是不行的，但是同时把b、c两点作为中间点时可以求取a点与d点的最短路径的
	//即c作为中间点求取路径时，是根据b为中间点时的结果
	
	for(int k=0;k < t;k++){
		//下面两个for循环的作用是遍历矩阵
        for(int i=0;i < t;i++){
			for(int j=0;j < t;j++){
				 
				//如果j和i相等证明是自己向自己传播消息，比较无意义
                if(i != j && graph[i][k]+graph[k][j]<graph[i][j]){
					
                    graph[i][j]=graph[i][k]+graph[k][j];
                    path[i][j]=path[i][k];
                }
            }
		}
	 }
		
            
}

int main(void){
	int y,weight,n,x;
	int rowMax,allRowsMin;
	int rowNum = 0;
	int rowDisJoinFlag =0;
	//每一组数据有t个经纪人
	scanf("%d",&t);
	while( 0 != t ){
		//路径数组与图的数组清零
		for(int i =0 ; i < t ;i++){
			for(int  j = 0 ; j < t ;j++){
				path[i][j] = j;
				graph[i][j] = INFINITY;
			}
		}
		for(x = 0 ; x < t ; x++){
			//第x个经纪人认识n个经纪人
			scanf("%d",&n);
			for(int j=0 ; j < n ; j++){
				//经纪人x向经纪人y传递消息要weight分钟
				scanf("%d",&y);
				scanf("%d",&weight);
				//printf("x: %d,y:%d,weight:%d\n",x,(y-1),weight);
				//经纪人的number是从1开始算起的，而电脑从零算起
				graph[x][(y-1)] = weight;
			}
		}//构图完毕
		// printf("\n------------------\n");
		// for(int i =0 ; i < t ;i++){
			// for(int  j = 0 ; j < t ;j++){		
				// printf("%d ",graph[i][j]);
			// }
			// printf("\n");
		// }
		// printf("\n------------------\n");
		
		
		Floyd();
		
		// for(int i =0 ; i < t ;i++){
			// for(int  j = 0 ; j < t ;j++){		
				// printf("%d ",graph[i][j]);
			// }
			// printf("\n");
		// }
		
		allRowsMin = INFINITY;
		for(int i =0 ; i < t ;i++){
			rowDisJoinFlag = 0;
			rowMax = 0;
			for(int  j = 0 ; j < t ;j++){
				//如果这一行除了自己与自己还有值为INFINITY的值，证明这一个经纪人无法向所有的其他经纪人传达消息，应该废除
				if( j != i && graph[i][j] == INFINITY){
					rowDisJoinFlag = 1;
					break;
				}
				if( graph[i][j] != INFINITY && graph[i][j] > rowMax){
					rowMax = graph[i][j];
				}
		
			}
			//在能向所有经纪人传播消息的经纪人当中，选取花费时间最少的那一位经纪人
			if( 0 == rowDisJoinFlag && rowMax != 0 && rowMax < allRowsMin ){
				allRowsMin = rowMax;
				rowNum = i;
			}
		}
		printf("%d %d\n",rowNum+1,allRowsMin);
		scanf("%d",&t);
	}
	return 0;
}