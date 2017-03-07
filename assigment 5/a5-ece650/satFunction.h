#include "stdio.h"

int comNum(int n, int m);
//get the m combination from a[n];
// b[m] is to store the current combination( just the index in a[])
//num is the number of the combination
void combination(int a[],int n, int m, int b[],int c[][2],int num);
int cmp(const void *a,const void* b);
