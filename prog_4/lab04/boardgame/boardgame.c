#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

char grid[200][200];
long  myascii[26][2];
char spicies[200][50000];
int  len[200],visited[40000];
 struct Graph* graph;
 	int N,M,K;
// A structure to represent an adjacency list node
struct AdjListNode
{
    int  dest;
 	int  indegree;
 	int  outdegree;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
//    newNode = newAdjListNode(src);
  //  newNode->next = graph->array[dest].head;
   // graph->array[dest].head = newNode;
}
 
// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}
 
void DFS(graph,i)
{
   struct AdjListNode  *  p;
   //newAdjListNode(dest)
    printf("\n%d",i);
    p=graph->array[i].head;
    visited[i]=1;
    while(p!=NULL)
    {
       i=p->dest;
       
       if(!visited[i])
            DFS(graph,i);
        p=p->next;
    }
}


int main(int argc, char *argv[]){
	int i,j;
	//printf("MPhka\n");
	scanf("%d %d",&N,&M);
	getchar();
	for (i=0;i<N;i++){
		for (j=0;j<M;j++){
			grid[i][j]=getchar();
		//	printf("%d",grid[i][j]);
		}
		getchar();
	}
	for (i=0;i<=25;i++){
	
		scanf("%ld %ld",&myascii[i][0],&myascii[i][1]);
	}
    scanf("%d",&K);
    char c;
    i=0;
    getchar();
   
    for(j=0;j<K;j++){
    	i=0;
    	while ((c=getchar())!='\n'){
			spicies[j][i]=c;
			i++;
			printf("%c",c);		
		}
		len[j]=i;
		printf("   %d \n", len[j]);
	}
	
	char str[200];
	//to print my string is ii!!
	
	//int ii;
	for(j=0;j<K;j++)
	{
		for(i=0;i<len[j]/2;i++)
		{
				char temp=spicies[j][i];
				spicies[j][i]=spicies[j][len[j]-i-1];
				spicies[j][len[j]-i-1]=temp;
		}
		/*for(ii=0;ii<len[j];ii++){
			printf("%c",spicies[j][ii]);
		
		}
		printf("\n");
		*/	
	}
 	int V=M*N;
  graph = createGraph(V);
 
 	for(i=0;i<N;i++){
 		for(j=0;j<M;j++){
 				if (((myascii[grid[i][j]-97][0]+i)<N && (myascii[grid[i][j]-97][0]+i)>=0) && ((myascii[grid[i][j]-97][1]+j)<M && (myascii[grid[i][j]-97][1]+j)>=0))
 		{
 					
 				//the graph is at first reversed 
 				addEdge(graph,i*M+j,(myascii[grid[i][j]-97][0]+i)*M+myascii[grid[i][j]-97][1]+j); 		
 //				graph->array[i].	
 		}
 		else
 		{
 				//	printf("%d\n",grid[i][j]-97);
 				addEdge(graph, i*M+j, i*M+j); 		
 		}
 			
 		} 			
 	}
    // print the adjacency list representation of the above graph
  //  printGraph(graph);
 
  	for(i=0;i<M*N;i++){
        visited[i]=0;
	} 
 //for ()
 	DFS(graph,/*i*/0);
 	return 0;
}
