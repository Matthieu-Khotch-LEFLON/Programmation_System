### Programmation_System ###

Question 1:
```ruby
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* Inclusion of all libraries needed */

int main(int argc, char *argv[]){
	char buf[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	size_t size1 = strlen(buf);
	write(STDOUT_FILENO,buf,size1);
}

```
![Screenshot](Assets/TerminalQuestion1.png)

=> For this first program, we have created a mini shell, with a display of a simple welcoming message.

Question 2:
```ruby
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>	/* Inclusion of all libraries needed */

int main(int argc, char *argv[]){
	
	char buf[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
	char prompt[] = "enseash % ";
	char clav[32];		/* Character strings for the command entered with the keyboard in the console */
	char date[] = "date";
	size_t size1 = strlen(buf);
	size_t size2 = strlen(prompt);		/* Here we have all character strings and size that we need */
	
	if(write(STDOUT_FILENO, buf,size1) == -1){
        perror("write");
		    exit(EXIT_FAILURE);
	}
	
	while(1){						/* Infinite loop */
		
  	if(write(STDOUT_FILENO, prompt,size2) == -1){		/* Display of prompt line */
          perror("write");
  		    exit(EXIT_FAILURE);
  	}
  	
  	ssize_t bytesRead = read(STDIN_FILENO, clav, sizeof(clav));		/* Reading of the command */
    	if (bytesRead == -1) {
          	perror("read");
          	exit(EXIT_FAILURE);
    }
  
    clav[bytesRead - 1] = '\0';		/* We delete the last element of the character strings */
  	
    int pid, status;
  	pid = fork();
  	
  	if (pid != 0){			/* Father's code */
  		    wait(&status);
  	}
  	
  	else{						/* Child's code */
  		  if (strlen(clav) == 0) {		/* Test if we just do "Enter" */
                execlp(date, date, (char *)NULL);
        }
  		  else{					/* If not, we launch the command that the user sent */
                execlp(clav, clav,(char *)NULL);
  		  }
  	 }
   }
  }
```
![Screenshot](Assets/TerminalQuestion2.png)

=> For this second part, we did an infinite loop where the user can enter a command of his choice and launch it, or if he don't enter anything, we display the date.

Question 3:
```ruby
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    	char buf[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    	char prompt[] = "enseash % ";
	char clav[32];
    	char date[] = "date";
    	char bye[] = "Bye bye...\n";

    	size_t size1 = strlen(buf);
    	size_t size2 = strlen(prompt);

	int pid, status;
	pid = fork();
    
    	if (write(STDOUT_FILENO, buf, size1) == -1) {
        	perror("write");
        	exit(EXIT_FAILURE);
    	}

    	while (1) {
		if (write(STDOUT_FILENO, prompt, size2) == -1) {
            		perror("write");
            		exit(EXIT_FAILURE);
        	}
        
		ssize_t bytesRead = read(STDIN_FILENO, clav, sizeof(clav));
    		if (bytesRead == -1) {
        		perror("read");
        		exit(EXIT_FAILURE);
       	 	} 
   	 	else if (bytesRead == 0) {				/* We test here if the user type <crtl> + d, and if the test is verified, we go out of the shell */
			write(STDOUT_FILENO, bye, sizeof(bye));
            		exit(EXIT_SUCCESS);
        	}

        	clav[bytesRead - 1] = '\0';
    
     		if (strcmp(clav, "exit") == 0) {			/* We test if the user typed "exit", and if yes, we go out of the code as well without making a fork */
            		write(STDOUT_FILENO, bye, sizeof(bye));
            		exit(EXIT_SUCCESS);
        	}

		if (pid != 0) {
            		wait(&status);
        	}
		else {
            		if (strlen(clav) == 0) {
                		execlp(date, date, (char *)NULL);
            		}
            		else {
                		execlp(clav, clav, (char *)NULL);
            		}
        	}
       }
	return 0;
}
```
![Screenshot](Assets/TerminalQuestion3.png)

=> Here, we have upgraded a little bit our previous code to have more tests on what the user type in the prompt.
