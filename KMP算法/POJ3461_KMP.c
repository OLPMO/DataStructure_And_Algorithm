#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char w[10100],t[1000100];
int next[10100];
//next数组的计算与源字符串无关


void Get_Next(char *target,int length){
	int i=0,j=-1;
	next[0] = -1;
	// 这是经典的next数据求法，效率较高，但不易理解
	//注：next数组有length个值，而不是length-1个值
	while( i < length){
		if( j==-1 || target[i] == target[j] ){
			i++;
			j++;
			// 如果前缀、后缀的最后一个不相等的值相等（对于后缀来说最后一个不相等的值就是要求next值的那一个值），
			if( target[j] == target[i]){
				next[i] = next[j];
			}else{
				next[i] = j;
			}
		}else{
			j = next[j];
		}
	}
	
}

int KMP(char *sourceString,char *targetString,int targetlength){
	int occurNum = 0;
	int tmp;
	char *pSource = sourceString;
	char *pTarget = targetString;
	while((*pSource) ){
		if(  *pSource == *pTarget ){
			pSource++;
			pTarget++;
		}else{
			if( -1 == next[pTarget-targetString]){
				pSource++;
				pTarget = targetString;
			}else{
				pTarget = targetString + next[pTarget-targetString];
			}
		} 
		//这个要深入理解next数组的含义才能理解
		if( *pTarget == '\0'){
			occurNum++;
			tmp = next[(pTarget-targetString)];
			if( tmp < 0 ){
				pTarget = targetString; 
			}else{
				pTarget = targetString + tmp;
			}
			
			
			
		}
	}
	return occurNum;	
}


int main(){
	int wslength,tslength;
	int caseNum;
	int occurNum = 0;

	scanf("%d",&caseNum);
	for(int i = 0 ; i < caseNum ; i++){
		scanf("%s%s",w,t);
		tslength = strlen(t);//text
		wslength = strlen(w);//word
		
		Get_Next(w,wslength);
		// for( int j = 0;j<wslength;j++){
			// printf("%d ",next[j]);
		// }
		// printf("\n");
		occurNum = KMP(t,w,wslength);
		printf("%d\n",occurNum);
	}
	
	return 0;
}



