#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//next数组的计算与源字符串无关
void Get_Next(char *target,int *next){
	int length = strlen(target);
	int maxNext;
	char *phead=target,*ptail,*lastPtail;
	
	next[0] = -1;
	//这种求取next值的方法非常直观（即使求取当前下标的最大公共前后缀），容易理解但是效率
	for(int  i = 1 ; i < length ; i++){
		ptail = target + i - 1;
		phead = target;
		maxNext = 0;
		
		lastPtail = ptail;
	
		//while循环的作用是求取最大公共前后缀，原理就是用暴力的方法，一个从头部走一个从尾部走
		while( phead < (target+ i ) && ptail >= target ){
			if( *phead == *ptail && ptail < (target + i)){
				
				phead++;
				ptail++;
			}else{
				//把最大值保存下来
				if( (phead - target) > maxNext && *(ptail) == target[i]){
					maxNext = phead - target ;
				}
				phead = target;
				
				ptail = lastPtail;
				ptail--;
				//把尾部的值保存下来，因为移动指针时会破坏这个值，这个值的意义是，最大后缀从当前位置开始匹对
				lastPtail = ptail;	
			}	
		}
		
		if( target[maxNext] == target[i] ){
			next[i] = next[maxNext];
		}else{
			next[i] = maxNext;
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
	Get_Next(targetString,next);
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
	//ababcaabc  next[]:-1 0 -1 0 2 -1 1 0 2
	//abCabCad  next[]: -1 0 0 -1 0 0 -1 4 
	//abcac   next[]:-1  0  0  -1  1
	//abcab -1 0 0 -1 0 
	// char *ts = "abcab";
	// int *next;
	// int tslength;
	// tslength = strlen(ts);
	// next = (int *)malloc(sizeof(int)*tslength);
	// Get_Next(ts,next);
	// for(int i=0 ; i < strlen(ts) ; i++){
		// printf("%d  ",next[i]);
	// }
	// printf("\n");
	// free(next);
	char *ss = "BAPC";
	char *ts = "BAPC";
	if( 1 == KMP(ss,ts)){
		printf("finded\n");
	}else{
		printf("no!\n");
	}
	return 0;
}



