#include <stdio.h>

#define INFINITY 65535
#define VERTEXT_NUMBER 9
//弗洛伊德算法算法可以说是动态规划的一个应用，如果没了解过动态规划，建议先去了解，有了动态规划的基础知识就很容易理解核心的动态
//转移方程了，也就很好理解那个三重循环
int graph[VERTEXT_NUMBER][VERTEXT_NUMBER] = {
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

int path[VERTEXT_NUMBER][VERTEXT_NUMBER];

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
	 for(int k=0;k<VERTEXT_NUMBER;k++)
		 //下面两个for循环的作用是遍历矩阵
        for(int i=0;i<VERTEXT_NUMBER;i++)
            for(int j=0;j<VERTEXT_NUMBER;j++)
            {
                if(graph[i][k]+graph[k][j]<graph[i][j]){
                    graph[i][j]=graph[i][k]+graph[k][j];
                    path[i][j]=path[i][k];
                }
            }
}

int main(void){
	Floyd();
	for(int i=0;i<VERTEXT_NUMBER;i++){
		for(int j=0;j<VERTEXT_NUMBER;j++){
			printf(" %d ",graph[i][j]);
		}
		printf("\n");
	}
	return 0;
}