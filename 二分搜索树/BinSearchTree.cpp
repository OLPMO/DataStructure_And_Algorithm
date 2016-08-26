#include <iostream>
#include <math.h>
using namespace std;
typedef struct treenode{
    int pos;
    int value;
    int level;
    treenode *pLeft;
    treenode *pRight;
    treenode(int value,int pos,int level) : value(value),pos(pos),level(level),pLeft(NULL),pRight(NULL){}
}TreeNode;
class BinSearchTree{
private:
    int leftDepth;
    int rightDepth;
    void AddNode(int value,int pos,TreeNode* root){
        TreeNode* expNode=this->root;
        TreeNode* parNode;
        while(NULL!=expNode){
             if(value>expNode->value){
                parNode=expNode;
                expNode=expNode->pRight;
                if(NULL==expNode){
                    parNode->pRight=new TreeNode(value,pos,parNode->level+1);
                    this->rightDepth=max((parNode->level+1),this->rightDepth);
                }
             }else{
                parNode=expNode;
                expNode=expNode->pLeft;
                if(NULL==expNode){
                    parNode->pLeft=new TreeNode(value,pos,parNode->level+1);
                    this->leftDepth=max(parNode->pLeft->level,this->leftDepth);
                }
             }
        }
        this->treeDepth=max(this->leftDepth,this->rightDepth);
    }
    //寻值程序的实现
    int SearchTree(int value,TreeNode* node){
        if(NULL==node){
            return -1;
        }
        if(value>node->value){
            SearchTree(value,node->pRight);
        }else if(value<node->value){
            SearchTree(value,node->pLeft);
        }else{
            return node->pos;
        }
    }
    void PrintSameDepth(TreeNode *pNode,int dep){
        if(dep>this->treeDepth||pNode==NULL ){
            return;
        }
        //第level层的节点只需递归level次
        if(1==dep){
            cout<<"#"<<pNode->value;
        }else{
            PrintSameDepth(pNode->pLeft,dep-1);
            PrintSameDepth(pNode->pRight,dep-1);
        }
    }
public :
    TreeNode *root=NULL;
    int treeDepth;
    void AddNode(int value,int pos){
        if(NULL==this->root){
            root=new TreeNode(value,pos,1);
            this->leftDepth=1;
            this->rightDepth=1;
            this->treeDepth=1;
        }else{
            this->AddNode(value,pos,this->root);
        }
    }
    //中序遍历
    void InOrderTreeTraversal(TreeNode *node){
        if(NULL==node){
            return;
        }
        if(NULL!=node->pLeft){
            InOrderTreeTraversal(node->pLeft);
        }
        cout<<"the pos is:"<<node->pos<<"--";
        cout<<"the value is:"<<node->value<<endl;
        if(NULL!=node->pRight){
            InOrderTreeTraversal(node->pRight);
        }
    }
    //树的前序遍历
    void FrontOrderTreeTraversal(TreeNode *node){
        if(NULL==node){
            return;
        }
        cout<<"the pos is:"<<node->pos<<"--";
        cout<<"the value is:"<<node->value<<endl;
        if(NULL!=node->pLeft){
            FrontOrderTreeTraversal(node->pLeft);
        }
        if(NULL!=node->pRight){
            FrontOrderTreeTraversal(node->pRight);
        }
    }
    //树的BFS遍历,自己写的
    void BFSBinSearchTree(){
        for(int i=1;i<=this->treeDepth;i++){
            cout<<endl<<"$$$$$$$$$$the depth is:"<<i<<" $$$$$$$$$$$$"<<endl;
            this->PrintSameDepth(this->root,i);
        }
    }

    //以下程序为寻值程序的接口,在二叉树中寻值，返回
    int SearchTree(int value){
        SearchTree(value,this->root);

    }
};


int main()
{
    int a[]={9,4,1,4,6,3,22,11,7};
    BinSearchTree bst;
    for(int i=0;i<9;i++){
        bst.AddNode(a[i],i);
    }
//    cout<<"My Tree Depth:" <<bst.treeDepth<<endl;
    bst.BFSBinSearchTree();
    return 0;
}
