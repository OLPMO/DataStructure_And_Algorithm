#include <iostream>
#define NONODE 65536
using namespace std;
int noCnt=0;
class GraphTraverse{

public:
    void BFSTraverse(int graph[][4],int visited[],int vsNode){
        if(vsNode>=noCnt){
            return;
        }
        int listCnt=0,j;
        int *dstList=new int[noCnt];
        if(0==visited[vsNode]){
            cout<<"The visiting node is:"<<vsNode<<endl;
            visited[vsNode]=1;
            listCnt=0;
            for(int i=0;i<noCnt;i++){
                if(1==graph[vsNode][i]&&0==visited[i]){
                    cout<<"The visiting node is:"<<i<<endl;
                    visited[i]=1;
					//用数组模仿队列
                    dstList[listCnt++]=i;
                }
            }
            dstList[listCnt]=NONODE;
            j=0;
            while(dstList[j]!=NONODE){
                 BFSTraverse(graph,visited,dstList[j]);
                 j++;
            }
        }
        BFSTraverse(graph,visited,vsNode+1);
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
    traGraph.BFSTraverse(g,visited,0);
    return 0;
}
