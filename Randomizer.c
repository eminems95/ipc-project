#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 30



int main(){
	srand(time(NULL));
	key_t key = 2137;
	int sharedMemoryID;
	int *sharedMemory;
	int i;
	int a=1;
	int q=2;

	sharedMemoryID = shmget(key, SHMSIZE, IPC_CREAT | 0666);
	
	if(sharedMemoryID < 0)
	{
		perror("Sharing memory error");
		exit(1);
	}

	sharedMemory = (int*)shmat(sharedMemoryID, NULL, 0);
	
	if(sharedMemory == NULL)
	{
		perror("Sharing memory segment error");
		exit(1);
	}

	for(i=0;i<SHMSIZE;i++){
		a*=q;
		sharedMemory[i]=a;
	}
	

	return EXIT_SUCCESS;
}
