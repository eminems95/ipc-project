#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 20

int main(){
srand(time(NULL));
	key_t key = 2137;
	int shmid;
	char *sharedMemory;
	char *text;
	int sameCharacter=0;
	int i;

	shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
	
	if(shmid < 0)
	{
		perror("Sharing memory error");
		exit(1);
	}

	sharedMemory = shmat(shmid, NULL, 0);
	
	if(sharedMemory == (char *) -1)
	{
		perror("Sharing memory segment error");
		exit(1);
	}

	for(i=0;;i++){
		printf("%c",sharedMemory[i%SHMSIZE]);
		
		if(sharedMemory[i%SHMSIZE] == sharedMemory[i%SHMSIZE-1]){
			sameCharacter++;
		}else{
			sameCharacter=0;
		}
		
		if(sameCharacter==5){
				
		}
	}

return 0;
}
