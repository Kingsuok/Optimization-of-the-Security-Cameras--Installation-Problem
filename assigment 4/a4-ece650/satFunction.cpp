#include "stdio.h"


int comNum(int n, int m){
	
	
	return n*(n-1)/m;

}
//get the m combination from a[n];
// b[m] is to store the current combination( just the index in a[])
//num is the number of the combination
void combination(int a[],int n, int m, int b[],int c[][2],int num){
	int i;
	int j;
	static int countTem=0;
	for (i=n;i>=m;i--){
		b[m-1] = i-1;
		if(m>1){
			combination(a,i-1,m-1,b,c,num);
		}
	else{ 
			
			for (j= 0;j<2;j++){
				c[countTem][j]=a[b[j]];
				
		}
			countTem++;
                if(countTem == num){
                   countTem=0;
               }
		}
		}
	}

