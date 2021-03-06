

#include "stdio.h"


#ifndef _FORMAT_H
#define _FORMAT_H
#include "format.h"
#endif

void initialChar(char a[],int n){
	int i;
	for (i=0;i<n;i++){
		a[i]='a';
	}

}
void initialInt(int a[],int n){
	int i;
	for (i=0;i<n;i++){
		a[i]=-1;
	}

}
int negative(char a[],int n){
	int i;
	for (i=0;i<n;i++){
		if(a[i]=='-'){
			return 1;
		}
	}
	return 0;
}

int inOrOut(int a1,int a2,int b[],int n2){
	int i;
	int flag1=0;
	int flag2=0;
	for (i=0;i<n2;i++){
		if(b[i]==a1){
			flag1=1;
		}
		if (b[i]==a2){
			flag2=1;
		}
		if (flag1==1 &&flag2==1){
			return 1; 
		}
	}
	return 0;
}



int startEnd[2];//store the start and end vertexes
int edges;//store the number of the edges
int vertexes;//the number of the vertexes
int inPut[maxVertexNum];//store the vertexes of edges 
int flagSquence=0;// detect whether input is V at first
int input(int inPut[],int n){
	char *p1;
	int buf1;
	int buf2;
	int flag1=0;
	char inPut1[maxVertexNum];
	char c;
	while (1){
		int i=0; 
		int n=0;  
		initialChar(inPut1,maxVertexNum);
		while ((c = getchar())!= '\n') {
			if (c==EOF){
				return 1;
			}
			inPut1[n]=c;
			n++;
		}

		if (inPut1[0]=='V'){
			if (inPut1[2]=='-'){
				printf("%s\n","Error: the number shoule not be negative.");
				continue;
			}
			else{
				sscanf(inPut1,"V %d",&buf1);
				if (flag1==0){
					vertexes=buf1;
					flag1=1;
					continue;
				}
				else{
					printf("%s\n","Error: V has been inputed.");
					continue;
				}
			}
		}
		if (inPut1[0]=='E'){
			if (flag1==1){
				if(negative(inPut1,sizeof(inPut1))){
					flag1=0;
					printf("%s\n","Error:the number is not negative.");
					continue;
				}
                              if(inPut1[3]=='}'){
				flag1 = 0;
                                edges=0;
                               
				continue;
				}
				i=0;
				for (p1=inPut1;*p1!='}';p1++){
					if (*p1=='<'){
						sscanf(p1,"<%d,%d>",&buf1,&buf2);
						if (buf1<=(vertexes-1)&&buf2<=(vertexes-1)){
							inPut[i]=buf1;
							inPut[i+1]=buf2;
							i+=2;

						}else
						{
							printf("%s\n","Error: E is not correct.");
							flag1=0;
							break;
						}
					}
				}
                                if(flag1==0){
		                 continue;
		                 }
				edges=i/2;
				if (flagSquence==0){
					flagSquence=1;
				}
				break;
			}
			else
			{
				printf("%s\n","Error:V should be inputed firstly.");
				continue;
			}
		}   
		if (flagSquence==0){
			printf("%s\n","Error:V,E should be inputted at first.");
			continue;
		}
		
	
	}
	return 0;
}
