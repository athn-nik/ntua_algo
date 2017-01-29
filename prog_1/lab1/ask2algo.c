#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() 
{
	long d = 0L, x = 0L;
	char c;

	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}
//void quickSort( int[], int, int);
int partition( long[][2], int, int);



void quickSort( long a[][2], int l, int r)
{
   int j;

   if( l < r ) 
   {
	
   	// divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}



int partition( long a[][2], int l, int r) {
   int i, j;
   long t2,t1,pivot = a[l][0];
   i = l; j = r+1;
		
   while( 1)
   {	//if (a[0][i]==0 || a[0][j]==0) break;
   	do ++i; while( a[i][0] <= pivot && i <= r );
   	do --j; while( a[j][0] > pivot );
   	if( i >= j ) break;
   	t1 = a[i][0]; a[i][0] = a[j][0]; a[j][0] = t1;
	t2 = a[i][1]; a[i][1] = a[j][1]; a[j][1] = t2;   
}
   t1 = a[l][0]; a[l][0] = a[j][0]; a[j][0] = t1;
t2 = a[l][1]; a[l][1] = a[j][1]; a[j][1] = t2;
   return j;
}

int main (){
clock_t begin, end;
double time_spent;

begin = clock();
long N=readLong();
long K=readLong();
long A[N][2];
long i=0;
//printf("%ld %ld \n",N,K);
for(i=0;i<N;i++){	
	A[i][0]=readLong();
	A[i][1]=readLong();
	//printf("%ld,%ld\n",A[i][0],A[i][1]);
}
quickSort(A,0,N-1);
for(i=0;i<N;i++){	
	//printf("%ld %ld\n",A[i][0],A[i][1]);
//}
//for(i=0;i<N;i++){	
//	if (A[0][i]=!=A[0][++i])
}
long B[N],sol;
for (i=0;i<N;i++){
  B[i]=A[i][1]-A[i][0]+1;
//printf("%ld\n",B[i]);
}
long current=A[0][1];
long sum=B[0];
//printf("%ld\n",sum);


   for (i=1;i<N;i++){
        if (current>A[i][1]){
		//long prev_current=current;        	
		
		current=A[i][1];
		//long prev_current=current;            
		}	
            //sum_prev=sum;
		//printf("%ld\n",sum);
	    sum=sum+B[i];
        if (sum>=K) {
            index=i;
            //printf("%ld\n",sum);            
            break;
            }
        }
	//printf("%ld, %ld\n",sum,current);
	//long c=sum-K
       sol=current-sum+K;
       printf("%ld\n",sol); 

       

//for (i=0;i<N;i++){
//B[i]=A[0][i];//
//}
/* here, do your time-consuming job */
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("%lf seconds\n",time_spent);
return 0;
}
