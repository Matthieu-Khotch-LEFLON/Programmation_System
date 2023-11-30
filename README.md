### Programmation_System ###

Question 1:
```ruby
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char buf[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	size_t size1 = strlen(buf);
	write(STDOUT_FILENO,buf,size1);
}

![Screenshot](Assets/TerminalQuestion1.PNG)


Question 2
```ruby
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	char buf[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	char prompt[] = "enseash % ";
	char clav[32];
	char date[] = "date";
	size_t size1 = strlen(buf);
	size_t size2 = strlen(prompt);
	
	if(write(STDOUT_FILENO, buf,size1) == -1){
        perror("write");
		    exit(EXIT_FAILURE);
	}
	
	while(1){
		
  	if(write(STDOUT_FILENO, prompt,size2) == -1){
          perror("write");
  		    exit(EXIT_FAILURE);
  	}
  	
  	ssize_t bytesRead = read(STDIN_FILENO, clav, sizeof(clav));
    if (bytesRead == -1) {
          perror("read");
          exit(EXIT_FAILURE);
    }
  
    clav[bytesRead - 1] = '\0';
  	
    int pid, status;
  	pid = fork();
  	
  	if (pid != 0){
  		    wait(&status);
  	}
  	
  	else{
  		  if (strlen(clav) == 0) {
                execlp(date, date, (char *)NULL);
        }
  		  else{
                execlp(clav, clav,(char *)NULL);
  		  }
  	 }
   }
  }
