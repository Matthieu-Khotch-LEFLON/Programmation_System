#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int compteur = 0;
	while(1){
		int status = fork();
		
		if(status == 0){
			sleep(13000000);
			exit(EXIT_SUCCESS);
		}
		else{
			compteur++;
			printf("Je suis l'heureux papa de %d processus \n",compteur);
		}
	}
	exit(EXIT_SUCCESS);
}
