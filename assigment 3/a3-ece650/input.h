
#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif


void initialChar(char a[],int n);
void initialInt(int a[],int n);
int negative(char a[],int n);
int inOrOut(int a1,int a2,int b[],int n2);

extern int startEnd[2];//store the start and end vertexes
extern int edges;//store the number of the edges
extern int vertexes;//the number of the vertexes
extern int inPut[maxVertexNum];//store the vertexes of edges 
extern int flagSquence;// detect whether input is V at first
int input(int inPut[],int n);
