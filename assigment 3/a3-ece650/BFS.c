
#include "stdio.h"


#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif

#ifndef _GRAPH_H
#define _GRAPH_H
#include "graph.h"
#endif



typedef struct{
	int front;
	int rear;
	int count;
	vertexType data[maxVertexNum];
}cirQueue;


void initQueue(cirQueue *Q){
	Q->front=Q->rear=0;
	Q->count=0;
}
int queueEmpty(cirQueue *Q){
	return 0==Q->count;
}
int queueFull(cirQueue *Q){
	return maxVertexNum==Q->count;
}

void enQueue(cirQueue *Q,vertexType x){
	if(queueFull(Q))
		printf("Error:The queue has been full.\n");
	Q->count++;
	Q->data[Q->rear]=x;
	Q->rear=(Q->rear+1)%maxVertexNum;
}

vertexType deQueue(cirQueue *Q){
	vertexType temp;
	if(queueEmpty(Q))
		printf("Error:The queue has been empty.\n");
	temp=Q->data[Q->front];
	Q->count--;
	Q->front=(Q->front+1)%maxVertexNum;
	return temp;
}
vertexType queueFront(cirQueue *Q){
	if(queueEmpty(Q))
		printf("Error:The queue has been full.\n");
	return Q->data[Q->front];
}

int visited[maxVertexNum];// flag of BFS :one vertex is checked or not 
int parent[maxVertexNum];//store the shortest path of two vertexes
int BFS(alGraph *G,int *visited,int *parent,vertexType sta,vertexType end,int a[],int e){//sta is the start vertex,
	int i,temp;
	int inOrOut=0;
	cirQueue Q;
	for (i=0;i<2*e;i++){
		visited[a[i]]=0;
	}
	initQueue(&Q);
	enQueue(&Q,sta);
	visited[sta]=1;
	edgeNode *p;
	while(!queueEmpty(&Q)){
		temp=deQueue(&Q);
		p=G->aList[temp].firstEdge;
		while(p!=NULL){
			if (!visited[p->adjvex]){
				visited[p->adjvex]=1;
				enQueue(&Q,p->adjvex);
				parent[p->adjvex]=temp;
				if (p->adjvex==end){
					inOrOut=1;
				}
			}
			p=p->next;
		}
	}
	return inOrOut;
}

void shortLine(alGraph *G,int *parent,vertexType sta,vertexType end,vertexType endDouble){
	parent[sta]=-1;
	int j=end;
	if (parent[j]!=parent[sta])
		shortLine( G,parent, sta, parent[j],endDouble);
	if (G->aList[j].vertex!=endDouble){
		printf("%d-",G->aList[j].vertex);fflush(stdout);
	}
	else{
		printf("%d\n",G->aList[j].vertex);fflush(stdout);
	}
}
