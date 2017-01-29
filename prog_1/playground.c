#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int InArr[700][700],S_PartSum[701],PartSum[700];				//orismos global metavlhtwn gia taxuthta

int main() {
	int N,K,i,j,s=0,l,out_helper,trexon; 					
	long int output=0;		
	char rd[495000];		//at least 1*max(N)^2 from fread definition
	//clock_t begin, end;
	//double time_spent;
	
	//begin = clock();
	int er=scanf("%d %d",&N,&K);
	

	if (er<0) {
		exit(-1);
		printf("Reading Error!!");
	}
	
	er=fread(rd,1,(N+1)*N+1,stdin);	//eisodos apo stdin

	if (er<0) {
		printf("Reading Error!!");
		exit(-1);
	}  		//read and check for errors

	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			while (rd[s]<'0' || rd[s]>'1'){ 
			s++;				//while i am not in the correct range
			}
			InArr[i][j]=rd[s]-'0';
			s++;
		}
	}	
	
	for (i=0; i<N; i++) {	
			
	   for (j=0; j<N; j++) PartSum[j]=0;					//mhdenisme partial sums
	
		for (j=i; j<N; j++) {	
			trexon=S_PartSum[0];
			S_PartSum[0]=0;	
										//merika athroismata apo i mexri j grammh toy A
			for (s=0; s<N; s++) {
				PartSum[s] =PartSum[s]+ InArr[j][s];  			
			}

			
			for (s=1; s<=N; s++) {
				S_PartSum[s] = S_PartSum[s-1] + PartSum[s-1];  	//ftiaxe merika athroismata gia to trexwn partsum
			}
		
			s=0;			
			while (s<=N) {
				out_helper=1;	
				l=s+1;							//elegxos partsum seiriaka krataw trexon gia elegxo
				while (l<=N) {                                         //apostashs upoloipwn apo auto
					if (S_PartSum[l] == trexon) out_helper++;
					else {
					     if (S_PartSum[l] > (trexon+K)) break;		 //an exw apostash megaluterh apo K sta merika 												 //athoismata break giati den xreiazetai elegxos allos 															//den exw parallhlogrammo
					     if (S_PartSum[l] == (trexon+K)) output =output+out_helper; //psaxe an exw aposstash K se duo 														//stoixeia tou Part sum pou shmainei k 													      	      //dentra vrhka parallhlogrammo!!
						
					}	
					l++;			
				}
				s = s+out_helper;		
				trexon = S_PartSum[s];			//sunexise me ta upoloipa stoixeia toy Spartsum kai vres ola me 									//apostaseis K tote exw paidikh xara me K dentra
			}		
		}	
	 }
	printf("%ld\n", output);
	//end = clock();
	//time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("%lf\n",time_spent);
	return 0;
}
