
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


void initQueue(cirQueue *Q);
int queueEmpty(cirQueue *Q);
int queueFull(cirQueue *Q);

void enQueue(cirQueue *Q,vertexType x);

vertexType deQueue(cirQueue *Q);
vertexType queueFront(cirQueue *Q);
extern int visited[maxVertexNum];// flag of BFS :one vertex is checked or not 
extern int parent[maxVertexNum];//store the shortest path of two vertexes
int BFS(alGraph *G,int *visited,int *parent,vertexType sta,vertexType end,int a[],int e);

void shortLine(alGraph *G,int *parent,vertexType sta,vertexType end,vertexType endDouble);
