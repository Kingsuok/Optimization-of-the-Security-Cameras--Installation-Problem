#include "stdio.h"
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
//#include <sys/time.h> 

#define Max 1000
#define strMax 500


void input(int argc, char* argv[],int a[4]){
	int i;

	int buffer2;

	int sDef = 10;
	int nDef = 5;
	int lDef = 5;
	int cDef = 20;
	
	if(argc>0){
		for (i=1;i<argc;i+=2){
			
			if(argv[i][1]=='s'){
				sscanf(argv[i+1],"%d",&buffer2);
				sDef = buffer2;
				}else if(argv[i][1]=='n'){
					sscanf(argv[i+1],"%d",&buffer2);
					nDef = buffer2;
			}else if(argv[i][1]=='l'){
				sscanf(argv[i+1],"%d",&buffer2);
				lDef = buffer2;
				}else {
					sscanf(argv[i+1],"%d",&buffer2);
					cDef = buffer2;
			}
		
	}
	//printf("%d,%d,%d,%d",sDef,nDef,lDef,cDef);	

	//printf("%s",argv[i]);
	}
	a[0] = sDef; a[1] = nDef; a[2] = lDef;a[3]=cDef;
	
}
//random number
void randomGenerator (int min, int max,int n,int a[]){
	
	static int devUrandomFd = -1;
	char* nextRandomByte;
	int bytesToRead;
	unsigned randomValue;
	int i;

	assert (max >= min);

	if (devUrandomFd == -1){
		devUrandomFd = open("/dev/urandom",O_RDONLY);
		assert(devUrandomFd != -1);
	}

	for (i = 0;i < n;i++){
	nextRandomByte = (char*)&randomValue;
	bytesToRead = sizeof (randomValue);

	
	do{
		int bytesRead;
		bytesRead = read (devUrandomFd,nextRandomByte,bytesToRead);
		bytesToRead -= bytesRead;
		nextRandomByte +=bytesRead;

	}while (bytesToRead > 0);

	a[i]=(randomValue%(max-min+1))+min;
	}
	
}


void segment(int b[],int strNum,int nMin,int max ){

	randomGenerator(nMin,max,strNum,b);
}

int zeroSeg(int n,int a[]){
	int i;
	for(i=0;i<n/2-1;i++){
		if (a[2*i]==a[2*i+2]){
			if(a[2*i+1]==a[2*i+3]){
				return 1;
			}
		}
	}
	return 0;
}

int parallel(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	int temp;
	temp = (x2-x1)*(y4-y3)-(x4-x3)*(y2-y1);
	return temp;	
}

int collineation(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	int temp1;
	int temp2;
	int temp3;
	temp1=parallel( x1, y1,x2, y2,x3, y3, x4, y4);
	if (temp1==0){
		temp2=parallel( x3, y3,x1, y1,x1, y1, x4, y4);
		temp3=parallel( x3, y3,x2, y2,x2, y2, x4, y4);
		if(temp2==0||temp3==0){
			return 1;
		}
	}
	return 0;
}

int overLopSef(int n,int a[]){
	int temp=0;
	int i,j;
	for(i=0;i<n/2-2;i++){
		for (j=i+1;j<n/2-1;j++){
			temp=collineation( a[2*i],a[2*i+1],a[2*i+2],a[2*i+3],a[2*j],a[2*j+1],a[2*j+2],a[2*j+3]);
			if(temp==1){
				return 1;
			}
		}
	}
	return 0;
}

int overLapStr(int n1 ,int a[],int seg[],int b[][Max],int strN ){
	if (strN==1){
		return 0;
	}
	int i,j,k;
	int temp=0;
	for (i=0;i<n1/2-1;i++){
		for(k=0;k<strN-1;k++){
		for(j=0;j<seg[k];j++)
		{
         temp=collineation( a[2*i],a[2*i+1],a[2*i+2],a[2*i+3],b[k][2*j],b[k][2*j+1],b[k][2*j+2],b[k][2*j+3]);
		 if (temp==1){
			 return 1;
		 }
		}
		}
	}
	return 0;
}
void cooRan(int cNum,int coordinate[][Max],int strNum, int segment[]){
	int i;
	int temp1;
	int temp2;
	int flag1=1;
	int flag2=1;
	int count=0;
	int count1=0;
	for(i=0;i<strNum;i++){
		do{
		do{
		randomGenerator(-cNum,cNum,2*(segment[i]+1),coordinate[i]);
	
		temp1=overLopSef(2*(segment[i]+1),coordinate[i]);
		temp2=zeroSeg(2*(segment[i]+1),coordinate[i]);
		
		if(count<25){
			if(temp1==1||temp2==1){
				count++;
			}else{
				flag1=0;
			}
		
		}
		if(count==25){	
			printf("Error: failed to generate valid input for 25 simultaneous attempts");fflush(stdout);
			exit(EXIT_SUCCESS);
		}
		}while (flag1);
		flag1=1;
		count=0;
		temp1=overLapStr(2*(segment[i]+1) ,coordinate[i],segment,coordinate,i+1 );
		if(count1<25){
			if(temp1==1){
				count1++;
			}else{
				flag2=0;
			}
		
		}
		if(count1==25){	
			printf("Error: failed to generate valid input for 25 simultaneous attempts");fflush(stdout);
			exit(EXIT_SUCCESS);
		}
	}while(flag2);
	flag2=1;
	count1=0;
	}

}
//get input style of assigment1
void addStreet(int strNum,int seg[],int coordinate[][Max],char streets[][Max],int waitTim,int* strNumOld){
	static int flagRemove = 0;
    int i;
	int j;
	if (flagRemove == 1){
		usleep(waitTim*1000000);
		for (i=0;i<*strNumOld;i++){
			printf("r\"%d\"\n",i);fflush(stdout);
		}
	}
		for(i=0;i<strNum;i++){
		for(j=0;j<2*(seg[i]+1);j+=2){
          if (0==j){
		  	sprintf(streets[i],"a\"%d\"(%d,%d)",i,coordinate[i][j],coordinate[i][j+1]);
		  }else{           
            sprintf(streets[i],"%s(%d,%d)",streets[i],coordinate[i][j],coordinate[i][j+1]);
		  }
		  }
		}
		*strNumOld = strNum;
		flagRemove = 1;
}

int main(int argc, char* argv[]){
	
	int i;
	int sMin=2;
	int nMin=1;
	int lMin=5;
	int strNumOld = 0;
	int a[4];//store the parameters of the generator
	int strNum;//street number
	int waitTim;//
	int seg[Max];//the number of segment of each street
	int coordinate[strMax][Max];
	char streets[strMax][Max];
	input(argc,argv,a);
        while(1){
	randomGenerator(sMin, a[0],1,&strNum);//strNum :get the number of streets
	segment(seg,strNum,nMin,a[1] );//seg[Max]:the number of segment of each street
	randomGenerator(lMin,a[2],1,&waitTim);//waitTim:get waiteTime
	cooRan(a[3],coordinate,strNum, seg);//coordinate[][]:coordinates of each street
	addStreet(strNum,seg,coordinate,streets,waitTim,&strNumOld);//streets: input style of assigment1 
	
	for ( i=0;i<strNum;i++){
	        printf("%s",streets[i]);fflush(stdout);
		printf("\n");fflush(stdout);
	}
        printf("g\n");fflush(stdout);
        }
return 0;	
}
