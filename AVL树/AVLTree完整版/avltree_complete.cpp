#include <iostream>
#include <math.h>
#define LL 1
#define LR -1
#define RR -1
#define RL 1
#define N 100010
#define M 50010
#define LEFT 1
#define RIGHT 2
/** 注意事项：
 *1.一旦节点的左右子树发生变化，节点的左右子树高度便要更新
 *2.一旦节点的子树高度发生变化，就应该重新计算节点的平衡因子
 *3.RZ表示R0（r zero）型删除后不平衡 ，RO表示R1型（r one）,RMO表示r-1型（r minus one），左边同理
*4.因为因插入节点而产生的不平衡经过旋转处理后的子树深度和插入之前相同，所以不影响插入路径上所有祖先的平衡度，即插入后可无需重算所有节点的平衡因子，只需算受影响的节点的平衡因子即可，提高效率
 *
 */

using namespace std;
//树的节点
int cnt,dstvalue;
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
    //旋转后要记得重算平衡因子的数值
    //左旋转,适用于RR型不平衡,删除元素后L0型，L-1型不平衡
    void LeftRotate(TreeNode *anceNode, TreeNode *parAnceNode){
        TreeNode *bNode;
        //取出b节点
        bNode=anceNode->pRight;
        //让A节点的右子树指向b的左子树
        anceNode->pRight=bNode->pLeft;
        anceNode->rightTreeDepth=bNode->leftTreeDepth;
        anceNode->bf=anceNode->leftTreeDepth-anceNode->rightTreeDepth;
        //让b的左子树指向A及节点
        bNode->pLeft=anceNode;
        //左子树发生了变化，重算左子树高度
        bNode->leftTreeDepth=max(anceNode->leftTreeDepth,anceNode->rightTreeDepth)+1;
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        //用b节点替代a节点
        if(NULL==parAnceNode){
            this->root=bNode;
        }else{
            if(parAnceNode->pLeft==anceNode){
                parAnceNode->pLeft=bNode;
                parAnceNode->leftTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }else if(parAnceNode->pRight==anceNode){
                parAnceNode->pRight=bNode;
                parAnceNode->rightTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }
            parAnceNode->bf=parAnceNode->leftTreeDepth-parAnceNode->rightTreeDepth;
        }

    }
    //先右后左旋转，适用于RL型旋转，删除元素后L1型不平衡
    void RightLeftRotate(TreeNode *anceNode, TreeNode *parAnceNode){
        TreeNode *aNode=anceNode;
        TreeNode *bNode=anceNode->pRight;
        TreeNode *cNode=anceNode->pRight->pLeft;
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
        if(NULL==parAnceNode){
            this->root=cNode;
        }else{
            if(parAnceNode->pLeft==anceNode){
                parAnceNode->pLeft=cNode;
                parAnceNode->leftTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }else if(parAnceNode->pRight==anceNode){
                parAnceNode->pRight=cNode;
                parAnceNode->rightTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }
            parAnceNode->bf=parAnceNode->leftTreeDepth-parAnceNode->rightTreeDepth;
        }

        //重算A,B,C节点的平衡因子
        aNode->bf=aNode->leftTreeDepth-aNode->rightTreeDepth;
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        cNode->bf=cNode->leftTreeDepth-cNode->rightTreeDepth;

    }


    //右旋转,适用于ll型不平衡,删除元素后R0型，R1型不平衡
    void RightRotate(TreeNode *anceNode, TreeNode *parAnceNode){
        TreeNode *bNode;
        if(NULL==anceNode){
            return;
        }
        //先把B节点取出来
        bNode=anceNode->pLeft;
        //让A节点的左子树指向b节点的右子树
        anceNode->pLeft=bNode->pRight;
        //重算左子树的高度，因为指向的是bnode的右子树，所以就与bnode的右子树高度相等，无需加1
        anceNode->leftTreeDepth=bNode->rightTreeDepth;
        //让b节点的有子树指向按节点
        bNode->pRight=anceNode;
        //重算bnode右节点高度,因为右子树指向了祖先节点（a节点），所以要求祖先节点的子树高度，再加1
        bNode->rightTreeDepth=max(anceNode->leftTreeDepth,anceNode->rightTreeDepth)+1;
        //让b节点替代A节点
        if(NULL==parAnceNode){
            this->root=bNode;
        }else{
            if(parAnceNode->pLeft==anceNode){
                parAnceNode->pLeft=bNode;
                //因为左子树指向了bnode，所以左子树高度为bnode的子树高度加一
                parAnceNode->leftTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }else if(parAnceNode->pRight==anceNode){
                parAnceNode->pRight=bNode;
                parAnceNode->rightTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
            }
            parAnceNode->bf=parAnceNode->leftTreeDepth-parAnceNode->rightTreeDepth;
        }

        //重算平衡因子,左右子树的高度
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        bNode->pRight->bf=bNode->pRight->leftTreeDepth-bNode->pRight->rightTreeDepth;

    }
    //先左后右型双旋转，适用于LR型不平衡，删除元素后R-1型不平衡
    void LeftRightRotate(TreeNode *anceNode, TreeNode *parAnceNode){
        TreeNode *bNode=anceNode->pLeft;
        TreeNode *cNode=bNode->pRight;
        bNode->pRight=cNode->pLeft;
        //让A节点的左子树指向C节点的右子树
        anceNode->pLeft=cNode->pRight;
        anceNode->leftTreeDepth=cNode->rightTreeDepth;
        //让B节点的右子树指向C节点的左子树
        bNode->pRight=cNode->pLeft;
        bNode->rightTreeDepth=cNode->leftTreeDepth;
        //让c节点的左子树指向B节点
        cNode->pLeft=bNode;
        cNode->leftTreeDepth=max(bNode->leftTreeDepth,bNode->rightTreeDepth)+1;
        //让C节点的右子树指向祖先节点（A节点）
        cNode->pRight=anceNode;
        cNode->rightTreeDepth=max(anceNode->leftTreeDepth,anceNode->rightTreeDepth)+1;
        //把祖先节点改为C节点
        if(NULL==parAnceNode){
            this->root=cNode;
        }else{
            if(parAnceNode->pLeft==anceNode){
                parAnceNode->pLeft=cNode;
                parAnceNode->leftTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }else if(parAnceNode->pRight==anceNode){
                parAnceNode->pRight=cNode;
                parAnceNode->rightTreeDepth=max(cNode->leftTreeDepth,cNode->rightTreeDepth)+1;
            }
            parAnceNode->bf=parAnceNode->leftTreeDepth-parAnceNode->rightTreeDepth;
        }

        //重算a，b，c节点的平衡因子
        anceNode->bf=anceNode->leftTreeDepth-anceNode->rightTreeDepth;
        bNode->bf=bNode->leftTreeDepth-bNode->rightTreeDepth;
        cNode->bf=cNode->leftTreeDepth-cNode->rightTreeDepth;

    }

    //AVL树增加节点的实现，包括重算子树高度及平衡因子，不必调用recalchilddepth，这样做可以提高效率
    void AddNode(int value,int pos,TreeNode *node){
        TreeNode *tmpNode=node,*parNode=NULL,*ancNode=NULL,*anceNode=NULL,*parAnceNode=NULL;
        //记录树是否平衡，平衡为真，不平衡为假；
        bool balFlag=true;
        while(NULL!=tmpNode){
            if(value>=(tmpNode->value)){
                if(NULL==tmpNode->pRight){
                    tmpNode->pRight=new TreeNode(value,pos,(tmpNode->level+1));
                    //当前节点的右子树高度
                    tmpNode->rightTreeDepth++;
                    tmpNode->bf=tmpNode->leftTreeDepth-tmpNode->rightTreeDepth;
                    break;
                }else{
                    ancNode=parNode;
                    parNode=tmpNode;
                    //想办法在tmpnode的级别检验出是否不平衡
                    tmpNode=tmpNode->pRight;
                    parNode->rightTreeDepth++;
                    parNode->bf=parNode->leftTreeDepth-parNode->rightTreeDepth;
                    if(parNode->bf<(-1)||parNode->bf>1){
                        parAnceNode=ancNode;
                        anceNode=parNode;
                        balFlag=false;
                    }
                }
            }else{
                if(NULL==tmpNode->pLeft){
                    tmpNode->pLeft=new TreeNode(value,pos,(tmpNode->level+1));
                    //当前节点的左子树高度
                    tmpNode->leftTreeDepth++;
                    tmpNode->bf=tmpNode->leftTreeDepth-tmpNode->rightTreeDepth;
                    break;
                }else{
                    ancNode=parNode;
                    parNode=tmpNode;
                    tmpNode=tmpNode->pLeft;
                    parNode->leftTreeDepth++;
                    parNode->bf=parNode->leftTreeDepth-parNode->rightTreeDepth;
                    if(parNode->bf<(-1)||parNode->bf>1){
                        parAnceNode=ancNode;
                        anceNode=parNode;
                        balFlag=false;
                    }
                }
            }
        }
        //出现了不平衡,要判断是属于哪一种类型的不平衡（LL,LR,RR,RL）,再采取相应的平衡措施
        if(!balFlag){
            if((NULL!=anceNode->pLeft)&&(LL==anceNode->pLeft->bf)){//LL型不平衡
                this->RightRotate(anceNode,parAnceNode);
            }else if((NULL!=anceNode->pLeft)&&(LR==anceNode->pLeft->bf)){//LR型不平衡
                this->LeftRightRotate(anceNode,parAnceNode);
            }else if((NULL!=anceNode->pRight)&&(RL==anceNode->pRight->bf)){//RL型不平衡
                this->RightLeftRotate(anceNode,parAnceNode);
            }else if((NULL!=anceNode->pRight)&&(RR==anceNode->pRight->bf)){//rr型不平衡
                this->LeftRotate(anceNode,parAnceNode);
            }

        }
        this->RecalDepth(this->root,1);
    }

    //删除后，用左最大（右最小）的元素去替换，只管删除，重算子树高度和平衡因子则调用recalchilddepth完成
    void DeleteNode(int pos,TreeNode *node,TreeNode *parDelNode,int dire){
        TreeNode *tmpNode,*parTmpNode=NULL;
        if(node==NULL){
            return;
        }
        if(node->pos==pos){
            //判断是哪种情形的删除
            //删除的节点为叶子节点时,直接删除即可
            if(NULL==node->pLeft&&NULL==node->pRight){
                delete node;
                if(LEFT==dire){
                    parDelNode->pLeft=NULL;

                }else if(RIGHT==dire){
                    parDelNode->pRight=NULL;
//
                }else{//当根节点为叶子节点时，删除了，整棵树就应该为空
                    this->root=NULL;
                }
            //若删除的节点有两个子树,用左子树最大值替换被删除的节点
            }else if((NULL!=node->pLeft)&&(NULL!=node->pRight)){
                //找到左子树中的最大值节点
                parTmpNode=node;
                tmpNode=node->pLeft;
                while(tmpNode->pRight!=NULL){
                    parTmpNode=tmpNode;
                    tmpNode=tmpNode->pRight;
                }
                //左子树中的最大值节点要么只有左子树，要么就是最右边的叶子节点
                if(NULL!=tmpNode->pRight){
                    tmpNode->pRight=node->pRight;
                }else{
                    if(parTmpNode==node){
                        tmpNode->pRight=node->pRight;

                    }else{
                        tmpNode->pLeft=node->pLeft;
                        tmpNode->pRight=node->pRight;
                    }
                }
                tmpNode->bf=tmpNode->leftTreeDepth-tmpNode->rightTreeDepth;
                if(LEFT==dire){
                    parDelNode->pLeft=tmpNode;
                }else if(RIGHT==dire){
                    parDelNode->pRight=tmpNode;
                }else{
                    this->root=tmpNode;
                }
                if(NULL!=parTmpNode){
                    parTmpNode->pRight=NULL;
                }
                delete node;
            }else if((NULL!=node->pRight)||(NULL!=node->pLeft)){//当要删除的节点只有一棵子树时
                if(NULL!=node->pRight){//只有右子树
                    if(LEFT==dire){
                        parDelNode->pLeft=node->pRight;
                    }else if(RIGHT==dire){
                        parDelNode->pRight=node->pRight;
                    }else{
                        this->root=node->pRight;
                    }
                }else{//只有左子树
                    if(LEFT==dire){
                        parDelNode->pLeft=node->pLeft;

                    }else if(RIGHT==dire){
                        parDelNode->pRight=node->pLeft;
                    }else{
                        this->root=node->pLeft;
                    }
                }
                delete node;
            }
            this->RecalChildDepth(this->root);
            this->MaintainBalace(this->root,NULL);
            return;
        }
        DeleteNode(pos,node->pLeft,node,LEFT);
        DeleteNode(pos,node->pRight,node,RIGHT);
    }

    void RecalChildDepth(TreeNode *node){
        if(NULL==node){
            return ;
        }
        //从底层往上算
        this->RecalChildDepth(node->pLeft);
        this->RecalChildDepth(node->pRight);
        if(NULL!=node->pLeft){
            node->leftTreeDepth=max(node->pLeft->leftTreeDepth,node->pLeft->rightTreeDepth)+1;
        }else{
            node->leftTreeDepth=0;
        }
        if(NULL!=node->pRight){
            node->rightTreeDepth=max(node->pRight->leftTreeDepth,node->pRight->rightTreeDepth)+1;
        }else{
            node->rightTreeDepth=0;
        }
        node->bf=node->leftTreeDepth-node->rightTreeDepth;
    }

    void MaintainBalace(TreeNode *node,TreeNode *parNode){
        if(NULL==node){
            return;
        }
        this->MaintainBalace(node->pLeft,node);
        this->MaintainBalace(node->pRight,node);
        int disBanlanceType=0;
        //L0型,L-1型不平衡
        if(-2==node->bf&&(0==node->pRight->bf||-1==node->pRight->bf)){
            this->LeftRotate(node,parNode);
            return ;
        }
        //L1型不平衡
        if(-2==node->bf&&1==node->pRight->bf){
            this->RightLeftRotate(node,parNode);
            return;
        }
        //R0,R1型不平衡
        if(2==node->bf&&(0==node->pLeft->bf||1==node->pLeft->bf)){
            this->RightRotate(node,parNode);
            return;
        }
        //R-1型不平衡
        if(2==node->bf&&-1==node->pLeft->bf){
            this->LeftRightRotate(node,parNode);
            return;
        }
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
    TreeNode *root;
    int treeDepth;
    BinSearchTree(){
        this->root=NULL;

    }

    void AddNode(int value,int pos){
        if(NULL==this->root){
            this->root=new TreeNode(value,pos,1);
            return ;
        }else{
           this->AddNode(value,pos,this->root);
        }
    }

    //因为pos才是唯一标识，所以用pos去删除
    void DeleteNode(int pos){
        DeleteNode(pos,this->root,NULL,0);
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
        this->RecalDepth(this->root,1);
        for(int i=1;i<=this->treeDepth;i++){
            cout<<endl<<"$$$$$$$$$$the depth is:"<<i<<" $$$$$$$$$$$$"<<endl;
            this->PrintSameDepth(this->root,i);
        }
        cout<<endl;
    }

    //以下程序为寻值程序的接口,在二叉树中寻值，返回
    int SearchTree(int value){
        return SearchTree(value,this->root);

    }

};
int main(){
    int acnt;
    //int a[]={9,4,1,4,6,3,22,11,7};
    int a[]={5,30,40,35,32};
    //int a[]={13,24,37,90,53};
    BinSearchTree bst;
    acnt=sizeof(a)/sizeof(int);
    for(int i=0;i<acnt;i++){
        bst.AddNode(a[i],i);
    }
    bst.BFSBinSearchTree();
    bst.InOrderTreeTraversal(bst.root);
    cout<<"------------------"<<endl;
    for(int i=0;i<acnt;i++){
        bst.DeleteNode(i);
        bst.BFSBinSearchTree();
        bst.InOrderTreeTraversal(bst.root);
        cout<<"-------------------"<<endl;
    }
    return 0;
}
