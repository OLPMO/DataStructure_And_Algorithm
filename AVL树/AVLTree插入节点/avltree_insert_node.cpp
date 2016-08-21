#include <iostream>
#include <math.h>
#define LL 1
#define LR -1
#define RR -1
#define RL 1
/** 注意事项：
 *1.一旦节点的子树高度发生变化，就应该重新计算节点的平衡因子
 *
 *
 *
 *
 */

using namespace std;
//树的节点
typedef struct treenode{
    int pos;
    int value;
    int level;//该节点位于第几层
    int bf;//平衡因子,bf=leftDepth-rightDepth
    int leftTreeDepth;//左子树深度
    int rightTreeDepth;//右子树深度
    treenode *pLeft;
    treenode *pRight;
    treenode(int value,int pos,int level):value(value),pos(pos),level(level),pLeft(NULL),pRight(NULL){
        leftTreeDepth=0;
        bf=0;
        rightTreeDepth=0;
    }
}TreeNode;
class BinSearchTree{
private:
//    int leftDepth;
//    int rightDepth;
    TreeNode* anceNode=NULL;
    TreeNode* parAnceNode=NULL;
    //旋转后要记得重算平衡因子的数值
    //左旋转,适用于RR型不平衡
    void RR_LeftRotate(){
        TreeNode *bNode;

        //取出b节点
        bNode=this->anceNode->pRight;
        //让A节点的右子树指向b的左子树
        this->anceNode->pRight=bNode->pLeft;
        this->anceNode->rightTreeDepth=bNode->leftTreeDepth;
        //让b的左子树指向A及节点
        bNode->pLeft=this->anceNode;
        //左子树发生了变化，重算左子树高度
        bNode->leftTreeDepth=max(this->anceNode->leftTreeDepth,this->anceNode->rightTreeDepth)+1;
        //用b节点替代a节点
        if(NULL==this->parAnceNode){
            this->root=bNode;
        }else{
            if(this->parAnceNode->pLeft==this->anceNode){
                this->parAnceNode->pLeft=bNode;
                this->parAnceNode->leftTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }else if(this->parAnceNode->pRight==this->anceNode){
                this->parAnceNode->pRight=bNode;
                this->parAnceNode->rightTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }
            this->parAnceNode->bf=this->parAnceNode->leftTreeDepth-this->parAnceNode->rightTreeDepth;
        }

        //重算a，b两个节点的平衡因子
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        this->anceNode->bf=this->anceNode->leftTreeDepth-this->anceNode->rightTreeDepth;
        cout<<"RR_RR_RR_RR_RR_RR_RR_"<<endl;
    }
    //先右后左旋转，适用于RL型旋转
    void RL_RightLeftRotate(){
        TreeNode *aNode=this->anceNode;
        TreeNode *bNode=this->anceNode->pRight;
        TreeNode *cNode=this->anceNode->pRight->pLeft;
        //先让A节点的右子树指向C节点的左子树
        aNode->pRight=cNode->pLeft;
        aNode->rightTreeDepth=cNode->leftTreeDepth;
        //让B节点的左子树指向C节点的右子树
        bNode->pLeft=cNode->pRight;
        bNode->leftTreeDepth=cNode->rightTreeDepth;
        //让C节点的左子树指向A节点
        cNode->pLeft=aNode;
        cNode->leftTreeDepth=max(aNode->leftTreeDepth,aNode->rightTreeDepth)+1;
        //让C节点的右子树指向B节点
        cNode->pRight=bNode;
        cNode->rightTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
        //让c节点成为祖先节点
        if(NULL==this->parAnceNode){
            this->root=cNode;
        }else{
            if(this->parAnceNode->pLeft==this->anceNode){
                this->parAnceNode->pLeft=cNode;
                this->parAnceNode->leftTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }else if(this->parAnceNode->pRight==this->anceNode){
                this->parAnceNode->pRight=cNode;
                this->parAnceNode->rightTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }
             this->parAnceNode->bf=this->parAnceNode->leftTreeDepth-this->parAnceNode->rightTreeDepth;
        }

        //重算A,B,C节点的平衡因子
        aNode->bf=aNode->leftTreeDepth-aNode->rightTreeDepth;
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        cNode->bf=cNode->leftTreeDepth-cNode->rightTreeDepth;
        cout<<"RL_RL_RL_RL_RL_RL_"<<endl;
    }


    //右旋转,适用于ll型不平衡
    void LL_RightRotate(){
        TreeNode *bNode;
        if(NULL==this->anceNode){
            return;
        }
        //先把B节点取出来
        bNode=this->anceNode->pLeft;
        //让A节点的左子树指向b节点的右子树
        this->anceNode->pLeft=bNode->pRight;
        //重算左子树的高度，因为指向的是bnode的右子树，所以就与bnode的右子树高度相等，无需加1
        this->anceNode->leftTreeDepth=bNode->rightTreeDepth;
        //让b节点的有子树指向按节点
        bNode->pRight=this->anceNode;
        //重算bnode右节点高度,因为右子树指向了祖先节点（a节点），所以要求祖先节点的子树高度，再加1
        bNode->rightTreeDepth=max(this->anceNode->leftTreeDepth,this->anceNode->rightTreeDepth)+1;
        //让b节点替代A节点
        if(NULL==this->parAnceNode){
            this->root=bNode;
        }else{
            if(this->parAnceNode->pLeft==this->anceNode){
                this->parAnceNode->pLeft=bNode;
                //因为左子树指向了bnode，所以左子树高度为bnode的子树高度加一
                this->parAnceNode->leftTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }else if(this->parAnceNode->pRight==this->anceNode){
                this->parAnceNode->pRight=bNode;
                this->parAnceNode->rightTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }
            this->parAnceNode->bf=this->parAnceNode->leftTreeDepth-this->parAnceNode->rightTreeDepth;
        }

        //重算平衡因子,左右子树的高度
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        bNode->pRight->bf=bNode->pRight->leftTreeDepth-bNode->pRight->rightTreeDepth;
        cout<<"LL_LL_LL_LL_"<<endl;
    }
    //先左后右型双旋转，适用于LR型不平衡
    void LR_LeftRightRotate(){
        TreeNode *bNode=this->anceNode->pLeft;
        TreeNode *cNode=bNode->pRight;
        bNode->pRight=cNode->pLeft;
        //让A节点的左子树指向C节点的右子树
        this->anceNode->pLeft=cNode->pRight;
        this->anceNode->leftTreeDepth=cNode->rightTreeDepth;
        //让B节点的右子树指向C节点的左子树
        bNode->pRight=cNode->pLeft;
        bNode->rightTreeDepth=cNode->leftTreeDepth;
        //让c节点的左子树指向B节点
        cNode->pLeft=bNode;
        cNode->leftTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
        //让C节点的右子树指向祖先节点（A节点）
        cNode->pRight=this->anceNode;
        cNode->rightTreeDepth=max(this->anceNode->leftTreeDepth,this->anceNode->rightTreeDepth)+1;
        //把祖先节点改为C节点
        if(NULL==this->parAnceNode){
            this->root=cNode;
        }else{
            if(this->parAnceNode->pLeft==this->anceNode){
                this->parAnceNode->pLeft=cNode;
                this->parAnceNode->leftTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }else if(this->parAnceNode->pRight==this->anceNode){
                this->parAnceNode->pRight=cNode;
                this->parAnceNode->rightTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }
            this->parAnceNode->bf=this->parAnceNode->leftTreeDepth-this->parAnceNode->rightTreeDepth;
        }

        //重算a，b，c节点的平衡因子
        this->anceNode->bf=this->anceNode->leftTreeDepth-this->anceNode->rightTreeDepth;
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        cNode->bf=cNode->leftTreeDepth-cNode->rightTreeDepth;
        cout<<"LR_LR_LR_LR_LR_"<<endl;
    }


    //AVL树增加节点的实现
    void AddNode(int value,int pos,TreeNode *node){
//        cout<<"--------------------------------------------"<<endl;
        TreeNode *tmpNode=node,*parNode=NULL,*ancNode=NULL;
        //记录树是否平衡，平衡为真，不平衡为假；
        bool balFlag=true;
        while(NULL!=tmpNode){
            if(value>=(tmpNode->value)){
                if(NULL==tmpNode->pRight){
                    tmpNode->pRight=new TreeNode(value,pos,(tmpNode->level+1));
                    //当前节点的右子树高度
                    tmpNode->rightTreeDepth++;
                    tmpNode->bf=tmpNode->leftTreeDepth-tmpNode->rightTreeDepth;
//                    cout<<"node-value:"<<tmpNode->value<<"--";
//                    cout<<"node-bf:"<<tmpNode->bf<<endl;
//                    cout<<"node-value:"<<tmpNode->pRight->value<<"--";
//                    cout<<"node-bf:"<<tmpNode->pRight->bf<<endl;
                    break;
                }else{
                    ancNode=parNode;
                    parNode=tmpNode;
                    //想办法在tmpnode的级别检验出是否不平衡
                    tmpNode=tmpNode->pRight;
                    parNode->rightTreeDepth++;
                    parNode->bf=parNode->leftTreeDepth-parNode->rightTreeDepth;
                    if(parNode->bf<(-1)||parNode->bf>1){
                        cout<<"nobalance value"<<parNode->value<<endl;
                        this->parAnceNode=ancNode;
                        this->anceNode=parNode;
                        if(NULL!=ancNode){
                            cout<<"ancNode-value:"<<ancNode->value<<endl;
                        }
                        cout<<"parNode-value"<<parNode->value<<endl;
                        cout<<"tmpNode-value"<<tmpNode->value<<endl;
                        balFlag=false;
                    }
//                    cout<<"node-value:"<<parNode->value<<"--";
//                    cout<<"node-bf:"<<parNode->bf<<endl;
                }
            }else{
                if(NULL==tmpNode->pLeft){
                    tmpNode->pLeft=new TreeNode(value,pos,(tmpNode->level+1));
                    //当前节点的左子树高度
                    tmpNode->leftTreeDepth++;
                    tmpNode->bf=tmpNode->leftTreeDepth-tmpNode->rightTreeDepth;
//                    cout<<"node-value:"<<tmpNode->value<<"--";
//                    cout<<"node-bf:"<<tmpNode->bf<<endl;
//                    cout<<"node-value:"<<tmpNode->pLeft->value<<"--";
//                    cout<<"node-bf:"<<tmpNode->pLeft->bf<<endl;
                    break;
                }else{
                    ancNode=parNode;
                    parNode=tmpNode;
                    tmpNode=tmpNode->pLeft;
                    parNode->leftTreeDepth++;
                    parNode->bf=parNode->leftTreeDepth-parNode->rightTreeDepth;
                    if(parNode->bf<(-1)||parNode->bf>1){
                       cout<<"nobalance value"<<parNode->value<<endl;
                        this->parAnceNode=ancNode;
                        this->anceNode=parNode;
//                        if(NULL!=ancNode){
//                            cout<<"ancNode-value:"<<ancNode->value<<endl;
//                        }
//                        cout<<"parNode-value"<<parNode->value<<endl;
//                        cout<<"tmpNode-value"<<tmpNode->value<<endl;
                        balFlag=false;
                    }
//                    cout<<"node-value:"<<parNode->value<<"--";
//                    cout<<"node-bf:"<<parNode->bf<<endl;
                }
            }
        }
        //出现了不平衡,要判断是属于哪一种类型的不平衡（LL,LR,RR,RL）,再采取相应的平衡措施
        if(!balFlag){
//            cout<<"nononononono"<<endl;
            if((NULL!=this->anceNode->pLeft)&&(LL==this->anceNode->pLeft->bf)){//LL型不平衡
                this->LL_RightRotate();
            }else if((NULL!=this->anceNode->pLeft)&&(LR==this->anceNode->pLeft->bf)){//LR型不平衡
                this->LR_LeftRightRotate();
            }else if((NULL!=this->anceNode->pRight)&&(RL==this->anceNode->pRight->bf)){//RL型不平衡
                this->RL_RightLeftRotate();
            }else if((NULL!=this->anceNode->pRight)&&(RR==this->anceNode->pRight->bf)){//rr型不平衡
                this->RR_LeftRotate();
            }

        }
        this->RecalDepth(this->root,1);
//        cout<<"--------------------------------------------"<<endl;
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
            cout<<"  "<<pNode->value;
        }else{
            PrintSameDepth(pNode->pLeft,dep-1);
            PrintSameDepth(pNode->pRight,dep-1);
        }
    }
    void RecalDepth(TreeNode *node,int level){
        if(node==NULL){
            return;
        }
        if(node==this->root){
            this->treeDepth=1;
        }else{
            //这样写会多算，因为同一层的节点会算多次
            //this->treeDepth++;
            this->treeDepth=max(level,this->treeDepth);
        }
        node->level=level;
        RecalDepth(node->pLeft,level+1);
        RecalDepth(node->pRight,level+1);
    }
public :
    TreeNode *root=NULL;
    int treeDepth;
    void AddNode(int value,int pos){
        if(NULL==this->root){
            this->root=new TreeNode(value,pos,1);
            return ;
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
        cout<<"pos:"<<node->pos<<"--";
        cout<<"bf:"<<node->bf<<"--";
        cout<<"leftTreeDepth:"<<node->leftTreeDepth<<"--";
        cout<<"rightTreeDepth:"<<node->rightTreeDepth<<"--";
        cout<<"value:"<<node->value<<endl;
        if(NULL!=node->pRight){
            InOrderTreeTraversal(node->pRight);
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
        return SearchTree(value,this->root);

    }

};
int main(){
    //int a[]={9,4,1,4,6,3,22,11,7};
    int a[]={5,30,40,35,32};
    //int a[]={13,24,37,90,53};
    BinSearchTree bst;
    for(int i=0;i<5;i++){
       bst.AddNode(a[i],i);
    }
    bst.InOrderTreeTraversal(bst.root);
   // cout<<"My Tree Depth:" <<bst.treeDepth<<endl;
    bst.BFSBinSearchTree();
    return 0;
}
