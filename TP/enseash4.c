#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void display_status(char *prompt, int status) {
    char exit_prompt[32];
    
    if (WIFEXITED(status)) {
        sprintf(exit_prompt, " [exit:%d] ", WEXITSTATUS(status));
        write(STDOUT_FILENO, prompt-2, strlen(prompt));
        write(STDOUT_FILENO, exit_prompt, strlen(exit_prompt));
        write(STDOUT_FILENO, " % ", 3);
    } 
    
    else if (WIFSIGNALED(status)) {
        sprintf(exit_prompt, " [sign:%d] ", WTERMSIG(status));
        write(STDOUT_FILENO, prompt-2, strlen(prompt));
        write(STDOUT_FILENO, exit_prompt, strlen(exit_prompt));
        write(STDOUT_FILENO, " % ", 3);
    }
}

int main(int argc, char *argv[]) {
    char buf[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    char prompt[] = "enseash % ";
    char clav[32];
    char date[] = "date";
    char bye[] = "Bye bye...\n";

    size_t size1 = strlen(buf);
    size_t size2 = strlen(prompt);

    if (write(STDOUT_FILENO, buf, size1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    
    if (write(STDOUT_FILENO, prompt, size2) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        
    while (1) {
        

        ssize_t bytesRead = read(STDIN_FILENO, clav, sizeof(clav));
        
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } 
        
        else if (bytesRead == 0) {
            write(STDOUT_FILENO, bye, sizeof(bye));
            exit(EXIT_SUCCESS);
        }
        
        clav[bytesRead - 1] = '\0';

        if (strcmp(clav, "exit") == 0) {
            write(STDOUT_FILENO, bye, sizeof(bye));
            exit(EXIT_SUCCESS);
        }

        int pid, status;
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid != 0) {
            wait(&status);
            display_status(prompt, status);
        } 
        
        else {
            if (strlen(clav) == 0) {
                execlp(date, date, (char *)NULL);
            } 
            
            else {
                execlp(clav, clav, (char *)NULL);
            }
            
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
