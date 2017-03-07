#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif


typedef struct eNode{
	int adjvex;
	struct eNode *next;
}edgeNode;

typedef struct vNode{
	vertexType vertex;
	edgeNode *firstEdge;
}vertexNode;

typedef vertexNode adjList[maxVertexNum];  
typedef struct{
	adjList aList;
	int n,e;
}alGraph;

void creatAlGraph(alGraph *G,int a[],int e,int v);
void deleteGraph(alGraph *G,vertexType a[],vertexType e);
