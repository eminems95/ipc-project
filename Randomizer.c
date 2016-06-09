#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 20


char RandomizeCharacter(){
	char randomCharacter;
	randomCharacter = (rand()%50)+65;
	return randomCharacter;
}


int main(){
	srand(time(NULL));
	key_t key = 2137;
	int sharedMemoryID;
	char *sharedMemory;
	int i,index;

	sharedMemoryID = shmget(key, SHMSIZE*sizeof(char), IPC_CREAT | 0666);
	
	if(sharedMemoryID < 0)
	{
		perror("Sharing memory error");
		exit(1);
	}

	sharedMemory = shmat(sharedMemoryID, NULL, 0);
	
	if(sharedMemory == NULL)
	{
		perror("Sharing memory segment error");
		exit(1);
	}

	for(i=0;;i++){
		index = i%SHMSIZE;
		sharedMemory[index]=RandomizeCharacter();
	}
	

	return EXIT_SUCCESS;
}
