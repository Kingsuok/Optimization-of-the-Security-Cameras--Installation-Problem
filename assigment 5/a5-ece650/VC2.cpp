#include<stdio.h>
#include"stdlib.h"

#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif


int cmp ( const void *a , const void *b )
{
  return *(int *)a - *(int *)b; 
}

void VC2(int edges,int inPut[]){
    int left[maxVertexNum];
	int i,k;
	int temp;
	int count=edges;
	int goal[MAXVER];
	int goalNum = 0;
	int tempLeft[maxVertexNum];
	int inPutTem[maxVertexNum];
	
	//int vertexCover[MAXVER];
	for(i = 0;i<2*edges;i++){
		inPutTem[i]=inPut[i];
	}
	for (i=0;i<edges;i++){
		left[i] = 2*i;
	}
	   

	while(1){
	    goal[goalNum] = inPutTem[0];
		goalNum++;
		goal[goalNum] = inPutTem[1];
		goalNum++;
		temp =0;
	for (i=0;i<count;i++){
		
	
		if (inPut[left[i]]!=inPutTem[0]&&inPut[left[i]+1]!=inPutTem[0]&&inPut[left[i]]!=inPutTem[1]&&inPut[left[i]+1]!=inPutTem[1]){
			tempLeft[temp] = left[i];
			temp++;
		}
	}
	if (temp!=0){		
	count = temp;	
	for (k=0;k<temp;k++){
		left[k]=tempLeft[k];
		inPutTem[2*k]=inPut[tempLeft[k]];
		inPutTem[2*k+1]=inPut[tempLeft[k]+1];
	}

	}else{
		break;
	}
	}

	qsort(goal,goalNum,sizeof(goal[0]),cmp);
	printf("APPROX-VC-2: ");
	fflush(stdout);
	for (k=0;k<goalNum;k++){
		if (k!=goalNum-1){
			printf("%d,",goal[k]);
			fflush(stdout);
		}else{
			printf("%d\n",goal[k]);
			fflush(stdout);
		}

	}
}

void startVC2(int edges, int inPut[]){
	VC2(edges,inPut);
}

