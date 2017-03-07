#include<stdio.h>
#include"stdlib.h"
#include <pthread.h> 
#include <time.h>
#include <sys/time.h>
#include <errno.h>


#include "VC1.h"

#include "VC2.h"

#include "VC0.h"

#include "input.h"


void* thread0(void* ){
	int flag;
	flag=input(inPut,maxVertexNum);
	if (flag==1){
		exit(0);
	}	
		
}

void* thread1(void*){
	startVC0(edges, vertexes,inPut);
}

void* thread2(void*){
	startVC1(edges,inPut);
}

void* thread3(void*){
	startVC2(edges,inPut);
}


void getTime( void* function(void*), char name[]){
	int ret;
        struct timeval tpstart, tpend;
	float timeuse;
         pthread_t id;
        gettimeofday(&tpstart,NULL);
	ret = pthread_create(&id,NULL,function,NULL);
        if(ret != 0){
	printf("Error:Create pthread error!\n");
	fflush(stdout);
	exit(1);
	}
	pthread_join(id,NULL);
	gettimeofday(&tpend,NULL);
        timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
	timeuse/=1000000;
	//printf("%s %f \n",name,timeuse);
}


int main(){
       
	char name1[]="CNF-SAT-time:";
	char name2[]="APPROX-1-time:";
	char name3[]="APPROX-2-time:";
	while (1){
	pthread_t id0;
	int ret0;
        ret0 = pthread_create(&id0,NULL,thread0,NULL);
	if(ret0 != 0){
	printf("Error:Create pthread error!\n");
	fflush(stdout);
	exit(1);
	}
	pthread_join(id0,NULL);
	
        
	getTime( thread1,name1 );
	getTime( thread2,name2 );
	getTime( thread3,name3 );
	}

	return 0;
}
