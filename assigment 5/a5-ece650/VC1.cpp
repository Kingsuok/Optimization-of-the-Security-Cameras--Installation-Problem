/***********************APPROX-VC-1***********************************/
#include<stdio.h>
#include"stdlib.h"

#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif

//get the signal vertexes in the edges ;return the number of the 
void vertexSingle(int edges,int inPut[],int* verEdgNum,int vertexesForEdges[]){    
	int i,j;
	int flag;
	int count = 0;
	for (i=0;i<2*edges;i++){
		flag = 0;
		if(count==0){
			vertexesForEdges[count]=inPut[i];
			count++;
		}else{
		for (j=0;j<count;j++){
			if(inPut[i]==vertexesForEdges[j]){
				flag = 1;
			}
		}
		if(flag == 0){
			vertexesForEdges[count]=inPut[i];
			count++;
		}
		}		
	}
	*verEdgNum = count;
}


void Degree(int edges, int inPut[],int verEdgNum,int vertexesForEdges[],int vertex1[]){
	int count;
	int i,j;
	for (i = 0;i<verEdgNum;i++){
		count =0;		
		for (j=0;j<2*edges;j++){		
			if(inPut[j]==vertexesForEdges[i]){				
                count++;
			}
		}
		vertex1[i] = count;			
	}	
}

void sortDegree(int verEdgNum,int vertex[]){
	int i,j;
	int temp = 0;
	for(i=0;i<verEdgNum-1;i++){
		int max = vertex[i];
		int maxIndex = i;
		
		for (j =i+1;j<verEdgNum;j++){
			if(max<vertex[j]){
				max = vertex[j];
				maxIndex = j;
			}
		}
		temp = vertex[i];
		vertex[i] = max;
		vertex[maxIndex] = temp;
	}
}

void sortVerEdg(int edges,int inPut[],int* verEdgNum,int vertexesForEdges[] ){
	int vertex1[MAXVER];
	int vertexTem[MAXVER];
	int vertexesForEdgesTem[MAXVER];
	int i,j,k;
	vertexSingle(edges, inPut,verEdgNum,vertexesForEdges );
    Degree(edges, inPut,*verEdgNum,vertexesForEdges,vertex1);
	for(i =0;i<*verEdgNum;i++){
		vertexTem[i] = vertex1[i];
		vertexesForEdgesTem[i] = vertexesForEdges[i];
	}
	sortDegree(*verEdgNum,vertexTem);

	int count = *verEdgNum;
	int left[MAXVER];
	int leftTemp[MAXVER];
	for(i=0;i<*verEdgNum;i++){
		left[i]=i;

	}
	
	int temp;
	int flag;

	for(i=0;i<*verEdgNum;i++){
		temp =0;
		flag =0;
		for(j=0;j<count;j++){
			if(vertexTem[i]==vertex1[left[j]]&&flag==0){
				vertexesForEdges[i]= vertexesForEdgesTem[left[j]];
				flag=1;
				continue;
			}
			leftTemp[temp] = left[j];
			temp++;
		}
		count = temp;
		for (k=0;k<temp;k++){
			left[k] = leftTemp[k];			
		}

	}

   
}

void vertexesInEdges(int* verEdgNum,int vertexesForEdges[],int edges,int inPut[]){
	int left[maxVertexNum];
	int i,j,k;
	int temp;
	int flag;
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
	sortVerEdg(edges,inPutTem,verEdgNum,vertexesForEdges );
		temp =0;
		flag = 0;
	for (j=0;j<count;j++){

		if((inPut[left[j]]==vertexesForEdges[0]||inPut[left[j]+1]==vertexesForEdges[0])&&flag==0){
			goal[goalNum] = vertexesForEdges[0];
		    goalNum++;
			flag = 1;
		}
		if (inPut[left[j]]!=vertexesForEdges[0]&&inPut[left[j]+1]!=vertexesForEdges[0]){
			tempLeft[temp] = left[j];
			temp++;
		}
	}
	if (temp!=0){		
	count = temp;
	edges =temp;
	for (k=0;k<temp;k++){
		left[k]=tempLeft[k];
		inPutTem[2*k]=inPut[tempLeft[k]];
		inPutTem[2*k+1]=inPut[tempLeft[k]+1];
	}

	}else{
		break;
	}
	}

	sortDegree(goalNum, goal);
	printf("APPROX-VC-1: ");
	fflush(stdout);
	for (k=goalNum-1;k>=0;k--){
		if (k!=0){
			printf("%d,",goal[k]);
			fflush(stdout);
		}else{
			printf("%d\n",goal[k]);
			fflush(stdout);
		}

	}
}

void startVC1(int edges, int inPut[]){
	int vertexesForEdges[MAXVER];//store the id of the vertexes in the edges without the repeated vertexes
    int verEdgNum; //store the number of vertexes in edges
	
	vertexesInEdges(&verEdgNum,vertexesForEdges,edges,inPut);
}
/***********************APPROX-VC-1***********************************/
