#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//next数组的计算与源字符串无关
void Get_Next(char *target,int *next){
	int length = strlen(target);
	int maxNext;
	// char curChar;
	char *phead=target,*ptail,*lastPtail;
	
	next[0] = -1;

	for(int  i = 1 ; i < length ; i++){
		ptail = target + i - 1;
		phead = target;
		maxNext = 0;
		
		lastPtail = ptail;
		// printf("i:%d\n",i);
		while( phead < (target+ i ) && ptail >= target ){
			if( *phead == *ptail && ptail < (target + i)){
				phead++;
				ptail++;
			}else{
				if( (phead - target) > maxNext && *(ptail) == target[i]){
					maxNext = phead - target ;
				}
				phead = target;
				ptail = lastPtail;
				ptail--;
				lastPtail = ptail;	
			}	
		}
		
		if( target[maxNext] == target[i] ){
			next[i] = next[maxNext];
		}else{
			next[i] = maxNext;
		}
		// printf("maxnext:%d,i:%d,maxNextc:%c,ic:%c \n",maxNext,i,target[maxNext],target[i]);
		// printf("%d  ",next[i]);
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



