#include <stdio.h>
#include <stdlib.h>
#define BSIZE 1<<15


long N,K;
int i,j,A[2500][2500];
int sum,heat[2501];
int E[2500][2500];


char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() 
{
	int d = 0, x = 0;
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

int totalCost(int L, int R)
{
	return A[R][R] - A[R][L-1] - A[L-1][R] + A[L-1][L-1];
}

int calc(int divs, int pos, int searchL, int searchR)
{
	E[divs][pos] = 1000000000;
	int ret = searchL;
	int t,i;
	for(i = searchL; i <= searchR; i++)
	{
	    t = E[divs-1][i] + totalCost(i+1, pos);
		if(t < E[divs][pos])
		{
			E[divs][pos] = t;
			ret = i;
		}
	}
	return ret;
}

void solve(int divs, int L, int R, int searchL, int searchR)
{
	if(L > R)
		return;
	if(L == R)
	{
		calc(divs, L, searchL, searchR);
		return;
	}
	if (searchR>R-1) searchR=R-1;
	//searchR = min(searchR, R-1);
	int i;
	if(searchL == searchR)
	{
		for( i = L; i <= R; i++)
			calc(divs, i, searchL, searchR);
		return;
	}
	int M = (L + R) / 2;
	int optM = calc(divs, M, searchL, searchR);
	solve(divs, L, M-1, searchL, optM);
	solve(divs, M+1, R, optM, searchR);
}


int main(){
	
 N=readLong();
 K=readLong();
// for(i=0;i<N;i++)
// 	for(j=0;j<N;j++)
// 		A[i][j]=0;	
//construction of input
//	printf("%ld",N);
 for(i=1;i<=N;i++){
 	for(j=1;j<=N;j++){
 		if(i!=j && j>i){
 			A[i][j]=readLong(); 		
 		}
 		if(j<i){
 			A[i][j]=A[j][i];
 		}
 	}
 }
 
 for(i = 1; i <= N; i++){
    for( j = 1; j <= N; j++){
			A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
	}
 }
 
 int i;
 for( i = 1; i <= N; i++)
		E[1][i] = totalCost(1, i);
 for( i = 2; i <= K; i++)
		solve(i, 2, N, i-1, N);
//thermothta apo KAI thn i ws KAI thn j ousia sto idio mpoukali
//heat[i]-heat[j+1] gi auto o pinakas heat einai 2501!!!! 
 
/* for(i=0;i<N;i++){
 	for(j=0;j<K;j++){
 		
 		
 		minHeat[i][j]=
        	
 	}
 }*/
  

// for(i=0;i<N;i++){
//	printf("\n");
//	for(j=0;j<N;j++){
//		printf("%d ",A[i][j]);	
	//}
// }


	printf(" %d ",E[N][K]);
	return 0;

}







