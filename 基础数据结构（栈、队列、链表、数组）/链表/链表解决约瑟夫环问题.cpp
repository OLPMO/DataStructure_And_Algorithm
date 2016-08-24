#include <iostream>
/****************************************************
*这是用链表模拟解决约瑟夫问题的代码
*
*****************************************************/
typedef struct listnode{
	int weight;
	listnode* next;
}listNode;
class jospCircle{
    listNode* tail;
    public:
        jospCircle(){
            tail=NULL;
        }
// 为约瑟夫循环添加节点   
        void AddNode(int load){	
			listNode* newNode;
			//要用堆内存
            newNode=new listNode;
            newNode->weight=load;
            if(tail==NULL){  
                newNode->next=newNode;
                tail=newNode;
            }else{
				//tail是最后一个节点，那么tail的next指针就永远指向第一个节点
				//新节点的指针指向头部
				newNode->next=this->tail->next;
				//加入新节点前的最后一个节点的指针指向新节点
				this->tail->next=newNode;
				//让新加入的节点成为尾部
				this->tail=newNode;
            }  
//			std::cout<<"tail weight"<<this->tail->weight<<std::endl;
//			std::cout<<"tail next weight"<<this->tail->next->weight<<std::endl;
        }
		void ShowCircle(){
			listNode* tmp=this->tail->next;
			std::cout<<"the current list is:"<<std::endl;
			while(this->tail!=NULL&&tmp!=tail){
				std::cout<<tmp->weight<<"  ";
				tmp=tmp->next;
			}
			std::cout<<this->tail->weight<<"  ";
			std::cout<<std::endl;
		}
		/*约瑟夫问题：从1开始不停计数，每次计数，第n个结点都要被排除，
		*然后重新计数，知道只剩下一个结点
		*void EliminateNode(int step)
		*功能：解决约瑟夫循环问题
		*参数：step代表第几个结点需要被排除
		*/
		void EliminateNode(int step){
			listNode* stepNode=tail->next;
			int cnt=1;
			while(tail!=NULL&&(tail!=tail->next)){
				stepNode=stepNode->next;
				cnt++;
				if(cnt==(step-1)){
					//删除下一个结点
					listNode* tmpNode=stepNode->next;
					stepNode->next=tmpNode->next;
					if(tmpNode==tail){
						tail=stepNode;
					}
					
					std::cout<<"deleting:"<<tmpNode->weight<<std::endl;
					delete tmpNode;
					stepNode=stepNode->next;
					cnt=1;
				}
			}
		}
};
int main(int argc, char *argv[]){
    jospCircle circle;
	for(int i=0;i<6;i++){
		circle.AddNode(i);
	}
	circle.EliminateNode(4);
	circle.ShowCircle();
	return 0;
}
