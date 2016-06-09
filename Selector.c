#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 20

int main(){
	srand(time(NULL));
	key_t key = 2137;
	struct timeval startTime, stopTime;
	float timeMeasurement;
	int shmid;
	char *sharedMemory;
	int sameCharacters=1;
	int i;

	gettimeofday(&startTime,NULL);

	shmid = shmget(key, SHMSIZE*sizeof(char), IPC_CREAT | 0666);
	
	if(shmid < 0)
	{
		perror("Sharing memory error");
		exit(1);
	}

	sharedMemory = shmat(shmid, NULL, 0);
	
	if(sharedMemory == NULL)
	{
		perror("Sharing memory segment error");
		exit(1);
	}

	for(i=0;;i++){
		printf("%c",sharedMemory[i%SHMSIZE]);
		
		if(sharedMemory[i%SHMSIZE] == sharedMemory[(i%SHMSIZE)-1]){
			sameCharacters++;
		}else{
			sameCharacters=1;
		}
		
		if(sameCharacters==5){
				gettimeofday(&stopTime,NULL);
				//sleep(1);
				timeMeasurement = (stopTime.tv_sec - startTime.tv_sec)*1000 + (stopTime.tv_usec - startTime.tv_usec)/1000;
				printf("\nDone! Found 5 similar characters.\nElapsed time: %.0f ms.", timeMeasurement);
				exit(1);
		}
	}
	//execlp("killall", "killall", NULL);

return EXIT_SUCCESS;
}
