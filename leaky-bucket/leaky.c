#include <stdio.h>
#include <stdlib.h>

int main(){

	int bucket, outgoing, incoming, n[100], curr = 0;
	
	printf("Enter in the bucket size : ");
	scanf("%d", &bucket);
	printf("Enter in the outgoing rate : ");
	scanf("%d", &outgoing);
	printf("Enter in the number of incoming values : ");
	scanf("%d", &incoming);
	
	for(int i=0; i<incoming; i++) scanf("%d", &n[i]);
	
	for(int i=0; i<incoming; i++){
		
		curr = n[i] + curr;
		
		if(curr <= bucket){
			printf("Current status => %d/%d\n", curr, bucket);
			sleep(2);
		}
		else{
			printf("Dropped packets => %d\n", curr - bucket);
			curr = bucket;
			printf("Current status => %d/%d\n", curr, bucket);
			sleep(2);
		}
		curr = curr - outgoing;
		printf("After outgoing, current status => %d/%d\n", curr, bucket);
		sleep(2);
	}

}