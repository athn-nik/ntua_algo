#include <stdio.h>
#include <stdlib.h>

struct cont{
    long long first;
    long long second;
};

int N,M,K,i,j;
struct cont states[1000][1000];
int cost[1000][1000];



struct cont search (int i, int j){
    int l,m;
    struct cont max;
    max.first = states[i][j+1].first;
    max.second = states[i][j+1].second;
    for (l=i; l<=i+K; l++){
        for (m=j; m<=j+K; m++){
            if ((l <= N-1)&&(m <= M-1)&&((l != i)||(m != j))){
                if ((states[l][m].second) > (max.second)) max = states[l][m];
                else if (((states[l][m].second) == (max.second))&&((states[l][m].first) < (max.first))) max = states[l][m];
            }
        }
    }
    return max;
}


int main(int argc, char *argv[]){

    scanf("%d %d %d",&N,&M,&K);

    struct cont max;
    for (i=0; i<N; i++){
        for (j=0; j<M; j++){
            scanf("%d", &cost[i][j]);
        }
    }
      
    for (i = N-1; i>=0; i--){
        for (j = M-1; j>=0; j--){
            if ((i == N-1)&&(j == M-1)){
                states[i][j].first = 0LL;
                states[i][j].second = (long long) cost[i][j];
            }
            else{
                max = search(i,j);
                states[i][j].first = max.second;
                states[i][j].second = max.first + (long long) cost[i][j];  
            } 
        }
    }
    
    states[0][0].second -= cost[0][0];
    printf("%lld %lld\n", states[0][0].first, states[0][0].second);
    return 0;
}
