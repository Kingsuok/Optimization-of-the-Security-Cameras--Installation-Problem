
#include "stdio.h"
#include <stdlib.h>

#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif


#ifndef _INPUT_H
#define _INPUT_H
#include "input.h"
#endif



#ifndef _GRAPH_H
#define _GRAPH_H
#include "graph.h"
#endif

#ifndef _BFS_H
#define _BFS_H
#include "BFS.h"
#endif


int main(){
	int flag1=0;
	int flag2=0;
	int flag;
	alGraph graph;
	while(1){
		if (flag1==1){
			deleteGraph(&graph,inPut,edges);
			flag1=0;
		}
		flag=input(inPut,maxVertexNum);
		if (flag==1){
			return 0;

		}
		if(flag2==0){
			flag2=1;
			flag1=0;
		}
		int e=edges;
		int v=vertexes;
		int sta=startEnd[0];
		int end=startEnd[1];
		int inOrOut;
		if (sta==end){
			printf("%d-%d\n",sta,end);
		}
		else{
			creatAlGraph(&graph,inPut,e,v);
			inOrOut=BFS(&graph, visited,parent, sta,end, inPut, e);
			if (inOrOut==0){
				printf("%s\n","Error:There is no path.\n");
			}
			else{
				shortLine(&graph,parent,sta,end,end);
			}
		}
	}
	return 0;
}
