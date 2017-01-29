#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <limits.h>
#define N 1000000
#define BSIZE 1<<15

typedef struct heapNode {
    int distance;
    int x;
    int y;
} heapNode;
 
typedef struct PQ {
    heapNode* heap;
    int size;
} PQ;
 
void insert(heapNode aNode, heapNode* heap, int size) {
    int idx;
    heapNode tmp;
    idx = size + 1;
    heap[idx] = aNode;
    while (heap[idx].distance < heap[idx/2].distance && idx > 1) {
    tmp = heap[idx];
    heap[idx] = heap[idx/2];
    heap[idx/2] = tmp;
    idx /= 2;
    }
}

void shiftdown(heapNode* heap, int size, int idx) {
    int cidx;        //index for child
    heapNode tmp;
    for (;;) {
        cidx = idx*2;
        if (cidx > size) {
            break;   //it has no child
        }
        if (cidx < size) {
            if (heap[cidx].distance > heap[cidx+1].distance) {
                ++cidx;
            }
        }
        //swap if necessary
        if (heap[cidx].distance < heap[idx].distance) {
            tmp = heap[cidx];
            heap[cidx] = heap[idx];
            heap[idx] = tmp;
            idx = cidx;
        } else {
            break;
        }
    }
}
 
heapNode removeMin(heapNode* heap, int size) {
    //int cidx;
    heapNode rv = heap[1];
    heap[1] = heap[size];
    --size;
    shiftdown(heap, size, 1);
    return rv;
}

void enqueue(heapNode node, PQ *q) {
    insert(node, q->heap, q->size);
    ++q->size;
}
 
heapNode dequeue(PQ *q) {
   heapNode rv = removeMin(q->heap, q->size);
   --q->size;
   return rv; 
}
 
void initQueue(PQ *q, int n) {
   q->size = 0;
   q->heap = (heapNode*)malloc(sizeof(heapNode)*(n+1));
}



typedef struct grid {
	int cost;	    // the cost, as it is calculated by Dijkstra algorithm
	int explored; 	// explored = 1 if the node has been explored
} grid_t;




grid_t A[1000][1000];	
int dist[1000][1000];	

long int Dijkstra(int L, int W, PQ *q) {
	int i, j, x, y;
	long int final_cost;
	heapNode u, node;
	while (1) {
		u = dequeue(q); 	//extract min from priority 
		x = u.x;
		y = u.y;
		if ((A[x][y].explored != 1) && (A[x][y].cost < 4000)) { 
			A[x][y].explored = 1; 

			// 1. enqueue all "down" neighbours
			for (i = x; i < L; i++){ 
				if (!A[i][y].explored) {
					if (A[i][y].cost < 4000) {
						if (A[i][y].cost == 0){
							final_cost = dist[x][y] + A[i][y].cost; // if goal is found, return...
							return final_cost;
						}
						if (dist[i][y] > dist[x][y] + A[i][y].cost){
							dist[i][y] = dist[x][y] + A[i][y].cost; 
							node.x = i;
							node.y = y;
							node.distance = dist[i][y];
							enqueue(node, q);		  
						}
					}
					else break; // if a barrier is found, break... 
				} 
			}

			// 2. enqueue all "up" neigbours
			for (i = x; i >= 0; i--){ 
				if (!A[i][y].explored) {
					if (A[i][y].cost < 4000) { 
						if (A[i][y].cost == 0){
							final_cost = dist[x][y] + A[i][y].cost; // if goal is found, return...
							return final_cost;
						}
						if (dist[i][y] > dist[x][y] + A[i][y].cost){
							dist[i][y] = dist[x][y] + A[i][y].cost; 
							node.x = i;
							node.y = y;
							node.distance = dist[i][y];
							enqueue(node, q);		  
						}
					}
					else break;	// if a barrier is found, break... 
				} 
			}


			// 3. enqueue all "right" neigbours
			for (j = y; j < W; j++){ 
				if (!A[x][j].explored) {
					if (A[x][j].cost < 4000) {
						if (A[x][j].cost == 0){
							final_cost = dist[x][y] + A[x][j].cost; // if goal is found, return...
							return final_cost;
						}
						if (dist[x][j] > dist[x][y] + A[x][j].cost){
							dist[x][j] = dist[x][y] + A[x][j].cost; 
							node.x = x;
							node.y = j;
							node.distance = dist[x][j];
							enqueue(node, q);		   
						}
					}
					else break; // if a barrier is found, break... 
				} 
			}

			// 4. enqueue all "left" neighbours
			for (j = y; j >= 0; j--){ 
				if (!A[x][j].explored) {
					if (A[x][j].cost < 4000) {
						if (A[x][j].cost == 0){
							final_cost = dist[x][y] + A[x][j].cost; // if goal is found, return...
							return final_cost;
						}
						if (dist[x][j] > dist[x][y] + A[x][j].cost){
							dist[x][j] = dist[x][y] + A[x][j].cost; 
							node.x = x;
							node.y = j;
							node.distance = dist[x][j];
							enqueue(node, q);		   
						}
					}
					else break; // if a barrier is found, break... 
				} 
			}
		}
	}
}



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

int main(int argc, char *argv[]){
    long int result;
    int flag=0, L,W,i,j;
    PQ q;
    heapNode node;

    scanf("%d %d", &L, &W);
    initQueue(&q, N);    // initialize a priority queue with fixed size N

    for (i=0; i<L; i++){
        for (j=0; j<W; j++){
            A[i][j].cost = readLong();
            A[i][j].explored = 0;
            if (A[i][j].cost == 0){
                if (flag++ == 0){
                    node.x = i;
                    node.y = j;
                    node.distance = 0;   
                    enqueue(node, &q);
                }
                dist[i][j] = 0;
            }   
            else dist[i][j] = INT_MAX;
        }
    }

    result = Dijkstra(L, W, &q);
    printf("%ld\n",result);
    return 0;
}
