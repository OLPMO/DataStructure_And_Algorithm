#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//next数组的计算与源字符串无关
void Get_Next(char *target,int *next,int length){
	int i=0,j=-1;
	next[0] = -1;
	//求取next的值时也可以充分利用以前所求得的next值
	//这是经典的next数据求法，效率较高，但不易理解
	while( i < length){
		if( j==-1 || target[i] == target[j] ){
			i++;
			j++;
			//如果前缀、后缀的最后一个不相等的值相等（对于后缀来说最后一个不相等的值就是要求next值的那一个值），否则，就是最大前缀
			if( target[j] == target[i]){
				next[i] = next[j];
			}else{
				//最大公共前缀的值
				next[i] = j;
			}
		}else{
			//对于最大公共前缀而言，匹配失败，可以用以前所求的数组，若果目标字符串非常大，就能大大缩短时间
			//要注意，因为匹配失败，此时i没变化
			j = next[j];
		}
	}
	
}

int KMP(char *sourceString,char *targetString){
	int *next;
	int tslength;
	char *pSource = sourceString;
	char *pTarget = targetString;
	tslength = strlen(targetString);
	next = (int *)malloc(sizeof(int)*tslength);
	Get_Next(targetString,next,tslength);
	for(int i=0;i<tslength;i++){
		printf("%d  ",next[i]);
	}
	printf("\n");
	 while((*pSource) && (*pTarget)){
		if( *pSource == *pTarget){
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
	}
	free(next);
	if( *pTarget == '\0'){
		return 1;
	}else{
		return 0;
	}
	
}
int main(){
	// 测试next数组的值
	// ababcaabc  next[]:-1 0 -1 0 2 -1 1 0 2
	// abCabCad  next[]: -1 0 0 -1 0 0 -1 4 
	// abcac   next[]:-1  0  0  -1  1
	// abcab -1 0 0 -1 0 
	char *ts = "abCabCad";
	int *next;
	int tslength;
	tslength = strlen(ts);
	next = (int *)malloc(sizeof(int)*tslength);
	Get_Next(ts,next,tslength);
	for(int i=0 ; i < tslength ; i++){
		printf("%d  ",next[i]);
	}
	printf("\n");
	
	//测试kmp的字符串匹配功能
	// char *ss = "BAPC";
	// char *ts = "BAPC";
	// if( 1 == KMP(ss,ts)){
		// printf("finded\n");
	// }else{
		// printf("no!\n");
	// }
	return 0;
}



