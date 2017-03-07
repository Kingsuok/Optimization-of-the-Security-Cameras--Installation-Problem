
#include <stdlib.h>
#include "SAT.h"
#include <stdio.h>
#include <unistd.h>
#include "satFunction.h"
#include "input.h"

int main(){
int i;
int j;
int k;
int l;
int x;
int flag;
int count;
int vertexNum;
int c[maxLiteral];
int index[maxNum][maxNum];
int comb[maxNum][2];
int comV;
int comK;
int vertexCount[maxNum];
int kCount[maxNum];
int b[2];
int variableNum;
int coverVertex[maxNum];
int result;

while(true){
flag=input(inPut,maxVertexNum);
		if (flag==1){
		return 0;
		}

vertexNum = vertexes; 

int p[2], bak;

pipe(p);
bak = dup(STDOUT_FILENO);
dup2(p[1], STDOUT_FILENO);


for(x=1;x<=vertexNum;x++){
	
	k=x;
        count=0;
	for (i=0;i<vertexNum;i++){
		for (j=0;j<k;j++){
          count++;
          index[i][j]=count;
        
			  
		}
	}
	SAT_Manager mgr = SAT_InitManager();
	SAT_SetNumVariables(mgr,vertexNum*k);
        
	for (i=0;i<k;i++){
		
		for (j=0;j<=vertexNum;j++){
			
			c[j] = (index[j][i] << 1);
			
		}
		
		SAT_AddClause(mgr, c, vertexNum);
	}
     
	for(i=0;i<vertexNum;i++){
		vertexCount[i]=i;
        
	}
       
	for (i = 0;i<k;i++){
		kCount[i] = i;
          
	}
if(k>1){
comK = comNum(k ,2);

combination(kCount,k, 2, b,comb,comK);

for (i = 0;i <vertexNum ;i++){
	for (j =0; j<comK;j++){
		
		for(l=0;l<2;l++){
         c[l] = (index[i][comb[j][l]]<<1)+1;
		 
		}
		SAT_AddClause(mgr, c, 2);
	}
}
}

comV = comNum(vertexNum,2);

combination(vertexCount,vertexNum,2,b,comb,comV);

for (i = 0;i <k ;i++){
	for (j =0; j<comV;j++){
		
		for(l=0;l<2;l++){
         c[l] = (index[comb[j][l]][i]<<1)+1;
		
		}
		SAT_AddClause(mgr, c, 2);
	}
}

for(i = 0;i<2*edges;i+=2){

	for (j=0;j<k;j++){
		c[j] = (index[inPut[i]][j]<<1);
	}
	for(j=k;j<2*k;j++){
		c[j] = (index[inPut[i+1]][j-k]<<1);
	}
	SAT_AddClause(mgr, c, 2*k);

}
  
    

    result = SAT_Solve(mgr);
	if(result == SATISFIABLE){
         dup2(bak, STDOUT_FILENO);
	 variableNum = SAT_NumVariables(mgr);
	for(i = 1; i <= variableNum; i++) {
	    int assigment = SAT_GetVarAsgnment(mgr, i);

	    if(assigment == 1) {

		   if (i%k!=0)
	                printf("%d ", i/k); 
		   if (i%k==0)
	           {
		       printf("%d ", i/k-1);
		   }			
	    }
	    
	}
       
	printf("\n"); fflush(stdout);
        //SAT_Reset(mgr);	
		break;
	}else if (result != SATISFIABLE && k==vertexNum)
        {
	    printf("unsat.\n"); fflush(stdout);
        }
        else{
                
	//SAT_Reset(mgr);
               continue;
	}
}
        
    

}
return 0;
}
