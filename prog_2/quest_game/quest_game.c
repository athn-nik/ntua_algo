#include <stdio.h>
#include <stdlib.h>

long long F[1000][1000],S[1000][1000];
int coins[1000][1000];
int N,M,K,i,j;

int* search (int i, int j) {
	int l,m;
	static int arr[2];
	int max = -1;
	int help=0,y=0;
	for (l=i; l<=i+K; l++) {
		if (l>=N) break;
		for (m=j; m<=j+K; m++) {
			if (m>=M) break;
			if (!((l==i)&&(m==j))) {
				help = coins[l][m]+S[l][m];
			        if (help>max) {
					max=help;
					arr[0]=l;
					arr[1]=m;
					y = F[l][m];
				}
				else if ((help==max)&&(F[l][m] < y)) {
					max = coins[l][m]+F[l][m];
					arr[0]=l;
					arr[1]=m;
				}
			}
		}
	}
	return arr;
}


int main(int argc, char *argv[]) {

	if (!(scanf("%d %d %d",&N,&M,&K))) printf("Error with N,M,K read.\n");

	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			if (!(scanf("%d", &coins[i][j]))) printf("Error with array read.\n");
		}
	}
	int * index;
	int a,b;

	for (i = N-1; i>=0; i--) {
		for (j = M-1; j>=0; j--) {
			if ((i==N-1)&&(j==M-1)) {
				F[i][j] = 0LL;
        			S[i][j] = 0LL;
			}
			else {
				index = search(i,j);
				a = index[0];
				b = index[1];
				//printf("%d %d\n",a,b);
				F[i][j] = (long long) coins[a][b] + S[a][b];
				S[i][j]= F[a][b];
			}  
		} 
	}

	printf("%lld %lld\n", F[0][0], S[0][0]);
/*	
	printf("THE COINS ARRAY IS:\n");
        for (i=0; i<N;i++) {
                for (j=0; j<M; j++) { printf("%lld ", coins[i][j]); }
                printf("\n");
        }
	printf("\nTHE FIRST ARRAY IS:\n");
	for (i=0; i<N;i++) {
		for (j=0; j<M; j++) { printf("%lld ", F[i][j]); }
		printf("\n");
	}
	printf("THE SECOND ARRAY IS:\n");
	for (i=0; i<N;i++) {
                for (j=0; j<M; j++) { printf("%lld ", S[i][j]); }
                printf("\n");
        }
*/   
	return 0;
}


