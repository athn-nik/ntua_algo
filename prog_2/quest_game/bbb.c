#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
typedef struct context {
	long long key;
	int row;
	int col;
} node;

typedef struct Hnode {
        node h[201];
} maxheap;

int N,M,K;
long long First[1000][1000],Second[1000][1000];
long long quest[1000][1000];
maxheap colmax[1000];
maxheap rowmax;


long readLong() 
{
	long d = 0L, row = 0L;
	char c;

	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return row;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { row = row*10 + (c-'0'); d = 1; }
		else if (d == 1) return row;
	}
	return -1;
}




int father(int);

maxheap maxheap_fix (maxheap, int);

maxheap change(maxheap , int , long long,int , int );

maxheap insert(maxheap , long long  , int  , int );

maxheap delete(maxheap, int, int);


int main() {

	int i,j;
	node help;
	
	N=readLong();
	M=readLong();
	K=readLong();

	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			quest[i][j]=readLong();
		}
	}
	
	for(j=0;j<K;j++) {
		rowmax.h[j].key=-1;
		rowmax.h[j].row = -1;
		rowmax.h[j].col = -1;
		for (i=0;i<M;i++){
			colmax[i].h[j].key=-1;
			colmax[i].h[j].row = -1;
			colmax[i].h[j].col = -1;
		}
	}
	
	First[N-1][M-1] = 0LL;
    Second[N-1][M-1] = 0LL;
    
for (i = N-1; i>=0; i--) {  
				memset(rowmax.h, -1, K * sizeof(long long));
      for (j = M-1; j>=0; j--) {
            if ((i==N-1)&&(j==M-1)) {                               
								colmax[j] = insert(colmax[j],quest[i][j],i,j);
								rowmax = colmax[j];
			}
            else {
				if (i==N-1) {
					help = rowmax.h[0];
					First[i][j] = quest[help.row][help.col] + Second[help.row][help.col];
                                	Second[i][j]= First[help.row][help.col];
					colmax[j] = insert(colmax[j],quest[i][j]+Second[i][j],i,j);	
					if ((rowmax.h[K-1].key) == -1) {
						rowmax = insert(rowmax,quest[i][j]+Second[i][j],i,j);
						}				
					else {
						rowmax = delete(rowmax,i,j+K);
						rowmax = insert(rowmax,quest[i][j]+Second[i][j],i,j);				
					}			
				}
				else {
					if (colmax[j].h[0].key > rowmax.h[0].key) 
						{
							help = colmax[j].h[0];
						} 
					else if (colmax[j].h[0].key == rowmax.h[0].key) 
					{
						if(First[colmax[j].h[0].row][colmax[j].h[0].col]<First[rowmax.h[0].row][rowmax.h[0].col]) 
						{
							help = colmax[j].h[0];
						} 				
						else help = rowmax.h[0]; 				
					}
					else  {
						help = rowmax.h[0];
					} 
							First[i][j] = quest[help.row][help.col] + Second[help.row][help.col];
                            Second[i][j]= First[help.row][help.col];
					if ((rowmax.h[K-1].key) == -1) {  
						if (colmax[j].h[0].key > quest[i][j]+Second[i][j]) {
							rowmax = insert(rowmax,colmax[j].h[0].key,colmax[j].h[0].row,colmax[j].h[0].col); 
							}
						else if (colmax[j].h[0].key == quest[i][j]+Second[i][j]) {
							if (First[i][j]<First[colmax[j].h[0].row][colmax[j].h[0].col]) {
								rowmax = insert(rowmax,quest[i][j]+Second[i][j],i,j);
								} 				
							else {
								rowmax = insert(rowmax,colmax[j].h[0].key,colmax[j].h[0].row,colmax[j].h[0].col); 				
							}
						}
						else {
						rowmax = insert(rowmax,quest[i][j]+Second[i][j],i,j);				
						}
					}					
					else {
						if (colmax[j].h[0].key > quest[i][j]+Second[i][j]) {
							rowmax = delete(rowmax,i,j+K);					
							rowmax = insert(rowmax,colmax[j].h[0].key,colmax[j].h[0].row,colmax[j].h[0].col);
						}
						else if (colmax[j].h[0].key == quest[i][j]+Second[i][j]) {
							if (First[i][j]<First[colmax[j].h[0].row][colmax[j].h[0].col]){ 
								rowmax = insert(rowmax,quest[i][j]+Second[i][j],i,j); 
								}				
							else {
								rowmax = insert(rowmax,colmax[j].h[0].key,colmax[j].h[0].row,colmax[j].h[0].col); 				
								}
						}						
						else {
							rowmax = delete(rowmax,i,j+K);					
							rowmax = insert(rowmax,quest[i][j]+Second[i][j],i,j);						
						}					
					}		
					if ((colmax[j].h[K-1].key) == -1) {
						colmax[j] = insert(colmax[j],quest[i][j]+Second[i][j],i,j);				
						}
					else {
						colmax[j] = delete(colmax[j],i+K,j);	
						colmax[j] = insert(colmax[j],quest[i][j]+Second[i][j],i,j);				
					}
				}
              }
           }
     }
	
	printf("%lld %lld\n", First[0][0], Second[0][0]);

	return 0;
}

int father(int i) {
	if (i%2==0) return (i/2-1);
	else return (i/2);
}
maxheap maxheap_fix (maxheap swros, int i) {
	int l=2*i+1;
	int r=2*i + 2;
	int max;
	node temp;
	if (l<=(K-1)&&((swros.h[l].key)>swros.h[i].key)) max = l;
	else max = i;
	if (r<=(K-1)&&(swros.h[r].key>swros.h[max].key)) max = r;
	if (max != i) {
		temp = swros.h[i];
		swros.h[i] = swros.h[max];
		swros.h[max] = temp;
		swros = maxheap_fix (swros, max); 		
	}
	return swros;
}


maxheap insert(maxheap swros , long long key , int x1 , int y1) {
	int len = K;
	swros.h[len].key = -1;
	swros.h[len].row = -1;
	swros.h[len].col = -1;
	swros = change(swros,len,key,x1,y1);
	return swros;
}


maxheap change(maxheap swros, int i , long long key ,int x1, int y1) {
	node temp;
	swros.h[i].key = key;
	swros.h[i].row = x1;
	swros.h[i].col = y1;	 
	while ((i>0)&&(((swros.h[father(i)]).key)<(swros.h[i].key))) {
			temp = swros.h[i];
			swros.h[i] = swros.h[father(i)];
			swros.h[father(i)] = temp;
			i = father(i);
	}
	return swros; 
}

maxheap delete(maxheap swros, int xx, int yy) {
	int jj;	
	for (jj=0; jj<K; jj++) {
		if ((swros.h[jj].row == xx)&&(swros.h[jj].col == yy)) {
			swros.h[jj].key = -1;
			swros.h[jj].row = -1;
			swros.h[jj].col = -1;
			swros = maxheap_fix(swros,jj);
			break;
		}
	}
	return swros;
}


