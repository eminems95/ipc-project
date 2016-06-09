#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
int status = 0;
pid_t senderPID, receiverPID;


	senderPID = fork();
	if(senderPID == 0)
	{
		execl("./Randomizer",0);
		printf("execl sender failure\n");
		exit(EXIT_FAILURE);
	}
	
	else
		if(senderPID == -1)
		{
			perror("Can't open Randomizer");
			exit(EXIT_FAILURE);
		}
	
	receiverPID = fork();
	if(receiverPID == 0)
	{		
		execl("./Selector",0);
		printf("Can't open Selector \n");
		exit(EXIT_FAILURE);
	}

	else
		if(receiverPID == -1)
		{
			perror("fork receiver failure");
			exit(EXIT_FAILURE);
		}

	if(wait(&status) == -1)
		printf("Error! Wait()\n");
	else
	{
		if(WIFEXITED(status))
					if(WEXITSTATUS(status) == 3)
						kill(receiverPID, SIGTERM);
	}


	exit(0);
}
