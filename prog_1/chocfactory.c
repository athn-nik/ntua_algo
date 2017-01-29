#include <stdio.h>
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
long InArr[200000][2];
//readlong is taken from corelab.ntua.gr
long readLong() {
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

//quicksort is taken from slides and slightly modified 
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
		
   while(1)
   {
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

int main () {

	long output=0, N, K, i, Sum, index;

	int err=scanf("%ld %ld", &N, &K);
	if (err<0){
		printf("Reading Error");
		return -1 ;	
	}	
	for (i=0;i<2*N;i=i+2) {		//construct input matrix 
		InArr[i][0]=readLong();	//and mark the beginnings with 1
		InArr[i][1]=1; 		//and the finishes with -1
		InArr[i+1][0]=readLong();
		InArr[i+1][1]=-1;
	}
	quickSort(InArr,0,2*N-1);
	output=InArr[0][0];
	index=0;
	Sum=0;
	for (i=0;i<2*N;i++) {
		if (InArr[i][0]!=output) {
			if (InArr[i][1]==1) Sum=Sum+(InArr[i][s0]-output)*index+1;	//mas endiaferoun mono oi ekkinhseis kai ta 
			else Sum=Sum+(InArr[i][0]-output)*index;			//stamathmata twn mhxanwn
		}									//opote ston index kratame to poses douleuoun
		else if (InArr[i][1]==1) Sum++;						//to output periexei thn xronikh stigmh pou 												//vriskomaste Sum kai to Sum thn suneisfora twn 											//mhxanwn			
		output=InArr[i][0];
		if (Sum>=K) {
			if (InArr[i][1]==1) {
				Sum=Sum-index-1;					//otan kseperasw to K elegxo
				output--;						//gia na vgalw swsto output
			}								//an vriskomai se enarksh h oxi
			while (Sum>=K) {						//kai gurizw pisw ton index analogws kai thn output
				Sum=Sum-index;
				output--;
			}
			printf("%ld\n",output+1);
			break;
		}
		index=index+InArr[i][1];
	}

	
	return 0;
}
