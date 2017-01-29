#include <stdio.h>
#include <stdlib.h>
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


int main(){

long N=readLong();
long M=readLong();
long K=readLong();

long myfriend;
long me;
int i,j;
long Room[N][M];

for(i=0;i<N;i++){
	for(j=0;j<M;j++){
		Room[i,j]=readLong();
	}	
}

}
