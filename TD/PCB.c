#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void print_PCB()
{
	printf("|PID: \t %d|\n",getpid());
	printf("|PPID: \t %d|\n", getppid());
	printf("|UID: \t %d|\n", getuid());
	printf("|GID: \t %d|\n", getgid());
}

int main()
{
	pid_t ret = fork();
	if(ret==0){
		printf("Nooooooon \n");
	}
	else{
		printf("PID %d, je suis ton père \n", ret);
	}
	
	//printf("fork() has returned: %d\n", ret);
	print_PCB();
	exit(EXIT_SUCCESS);
}
