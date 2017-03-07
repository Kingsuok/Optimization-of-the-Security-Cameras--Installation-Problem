
#include "stdio.h"

#include <stdlib.h>

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

void creatAlGraph(alGraph *G,int a[],int e,int v){//n:the number of vertexes,a[]:the edges,e:the number of edges
	int i,k,l;
	G->n = v;
	G->e = e;
	edgeNode *s;
	for (i=0;i<2*e;i++){
		G->aList[a[i]].vertex=a[i];
		G->aList[a[i]].firstEdge=NULL;
	}
	for(k=0;k<e;k++){
		l=2*k;
		s=(edgeNode *)malloc(sizeof(edgeNode));
		s->adjvex=a[l+1];
		s->next=G->aList[a[l]].firstEdge;
		G->aList[a[l]].firstEdge=s;

		s=(edgeNode *)malloc(sizeof(edgeNode));
		s->adjvex=a[l];
		s->next=G->aList[a[l+1]].firstEdge;
		G->aList[a[l+1]].firstEdge=s;
	}

}

void deleteGraph(alGraph *G,vertexType a[],vertexType e){
	int i;
	for (i=0;i<2*e;i++){
		edgeNode *q;
		edgeNode *p=G->aList[a[i]].firstEdge;
		while (p){
			q=p;
			p=p->next;
			free(q);
		}
		G->aList[a[i]].firstEdge=NULL;
	}
}

