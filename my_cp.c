#include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	if((argc != 2) && (argc != 3)){
		printf("Usage is: %s <file1> <file2> for a copy or %s <file1> for a display\n ",argv[0],argv[0]);
		exit(EXIT_FAILURE);
	}
	
	struct stat sbFile1;
	struct stat sbFile2;
	
	if(lstat(argv[1], &sbFile1) == -1){
		perror("File1 does not exist");
		exit(EXIT_FAILURE);
	}
	
	if(! S_ISREG(sbFile1.st_mode & S_IFMT)){
		perror("File1 is not a regular");
		exit(EXIT_FAILURE);
	}
		
	if((argc == 3) && (lstat(argv[2], &sbFile2)) != -1){
		perror("File2 does not exist");
		exit(EXIT_FAILURE);
	}
	
	int fd1 =open(argv[1],O_RDONLY);
	int fd2;
	if (argc == 3){
		creat(argv[2],S_IRWXO|S_IRWXG|S_IRWXU);
		}
	else {
		fd2 = STDOUT_FILENO;
	}
	
	char buffer[BUFSIZ] = {0};
	int size;
	do{
		size = read(fd1,buffer,BUFSIZ);
		write(fd2,buffer,size);
	}
	while(size==BUFSIZ);
	
	close(fd1);
	close(fd2);
	
	return 0;
}
	

