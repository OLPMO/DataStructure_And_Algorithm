#include<stdio.h>
#include<stdlib.h>
/*出自：http://www.fishc.com
*这个是我从鱼c工作室的论坛上下载的代码
*它构造next数组的函数比我的效率要高，因此就把它放在github上供大家参考了。
*侵权立删
*/

void get_next(char *T,int *next)//该函数是为了得到T字符串每一个字符对应的next数组的值
{
	int count=0,front,rear;
	while(T[count])
	{
		count++;
	}
	front=0;//前缀
	rear=1;//后缀
	next[0]=-1;
	next[1]=0;
	while(rear<=count)
	{
		if(front==-1||T[front]==T[rear])//只有next【0】才可以等于-1，其余的字符的next值最低只可以等于0，当后面的值回溯到第一个时就应把0赋值它
		{
	    	front++;
	    	rear++;
			if(T[rear]!=T[rear-1])//加一个判断是为了提高效率（如：aaaac这个例子）
			{
				next[rear]=front;
			}
			else
			{
				next[rear]=next[rear-1];
			}

		}
    	else
		{
		    front=next[front];//相当于递归，next数组的作用就是为了提供在对应的位置失配时所要回溯的位置
			//因此当前缀元素失配是就要把对应的next值赋值给前缀，进行重新匹配（回溯）
		}
	}
}
int index_KMP(char *S,char *T,int Tlen,int pos)
//pos表示从第几个位置开始检索,tlen表示next数组的长度即t字符串的有效字符长度
{
	int i=pos,j=0,*next;
	next=(int *)malloc((Tlen*10)*sizeof(int));
	get_next(T,next);
	while(S[i]&&T[j])
	{
		
		if(S[i]==T[j])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
		}
		if(j==-1)
		{
			j=0;
			i++;
		}
	}
	free(next);
	if(j>=Tlen) return i-j+1;//返回的应是t字符串所在的位置
	else return 0;
}
int main()
{
	char s[100]="ffffffffffffffffafffaffffbfffffffffffff";
	char t[6]="af";
	int i,next[6],result=0;
//以下代码为测试get-next函数的代码
/*
    get_next(s,next);
	for(i=0;i<6;i++)
	{
		printf("%d ",next[i]);
	}
	printf("\n");
*/
	result=index_KMP(s,t,2,0);
	printf("%d\n",result);
	return 1;
}