#include <stdio.h>

int count=0;
bool JudDanger(int row,int i,int chess[][8])
{
	int j,k,flag1=0,flag2=0,flag3=0,flag4=0,flag5=0;
	for(j=0;j<8;j++)
	{
		if(chess[j][i]!=0) 
		{
			flag1=1;
			break;
		}
	}
	for(j=row,k=i;j>=0&&k>=0;j--,k--)
	{
		if(1==chess[j][k])
		{
			flag2=1;
			break;
		}
	}
	for(j=row,k=i;j<8&&k<8;j++,k++)
	{
		if(1==chess[j][k])
		{
			flag3=1;
			break;
		}
	}
	for(j=row,k=i;j<8&&k>=0;j++,k--)
	{
		if(1==chess[j][k]) 
		{
			flag4=1;
			break;
		}
	}
	for(j=row,k=i;j>=0&&k<8;j--,k++)
	{
		if(1==chess[j][k])
		{
			flag5=1;
			break;
		}
	}
	if(flag1||flag2||flag3||flag4||flag5)
		return false;
	else return true;
}
//row��ʾ�ӵڼ��п�ʼ��
//n��ʾ���ж�����
void EightQueen(int row,int n,int chess[][8])//ÿһ�ж�������һ��λ��
{
	int i,j,chess2[8][8];
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			chess2[i][j]=chess[i][j];
		}
	}
	if(8==row)
	{
		printf("��%d��:\n",count+1);
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				printf("%d ",chess2[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		count++;
	}
	else
	{
		for(i=0;i<n;i++)//ĳһ�е�ÿ��λ�ö����԰ڣ�����ÿ��λ�ö���һ�¡�ȷ����һ�е�λ�ã���ȷ����һ�е�λ�ã�ͬ�������ڶ��е�ÿһλ��Ҳ��һ��----��٣�
			            //Ȼ��ͣ��ѭ����ȥ
		{
			if(JudDanger(row,i,chess2))
			{
				for(j=0;j<8;j++)
				{
					chess2[row][j]=0;
				}
				chess2[row][i]=1;//����һ��ָ�֤����ǰһ����ȷ��һ��λ�ã�Ȼ��ݹ飬����һ����ٸ��ֿ���
				EightQueen(row+1,n,chess2);
			}
			
		}
	}
}
int main(int argc, char *argv[])
{
	int chess[8][8],i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			chess[i][j]=0;
		}
	}
	EightQueen(0,8,chess);
	printf("����%d�ְڷ���\n",count);
	
	return 0;
}
