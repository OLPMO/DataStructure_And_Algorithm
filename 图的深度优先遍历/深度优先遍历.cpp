#include <iostream>
#define NONODE 65536
using namespace std;
int noCnt=0;
class GraphTraverse{


public:
	//封装做得不好，但重要的是逻辑，因为逻辑比较简单，所以注释就少点
	/*
	*深度优先遍历，第一个参数是邻接矩阵，第二个参数是记录节点记录情况的数组，第三个参数是从哪个节点开始遍历
	*/
    void DFSTraverse(int graph[][4],int visited[],int vsNode){
        if(vsNode>=noCnt){
            return;
        }
        if(0==visited[vsNode]){
            cout<<"The visiting node is:"<<vsNode<<endl;
            visited[vsNode]=1;
            for(int i=0;i<noCnt;i++){
                if(1==graph[vsNode][i]&&0==visited[i]){
                    DFSTraverse(graph,visited,i);
                }
            }
        }
        DFSTraverse(graph,visited,vsNode+1);
    }

};
int main()
{
//    int g[4][4]={{0,0,1,0},{0,1,0,0},{1,1,0,1},{1,0,0,0}};
//    int g[5][5]={{0,0,0,1,1},{0,0,0,0,0},{0,0,0,0,0},{0,1,1,0,0},{0,1,0,0,0}};
    int g[4][4]={{0,0,1,1},{0,0,1,1},{0,1,0,0},{0,1,1,0}};
    int visited[4]={0};
    noCnt=4;
    GraphTraverse traGraph;
    //traGraph.BfsTraverse(g,visited,0);
    traGraph.DFSTraverse(g,visited,0);
    return 0;
}
