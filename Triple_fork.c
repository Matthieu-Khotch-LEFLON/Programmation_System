#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
fork();fork();fork();
printf("fork!\n");
exit(EXIT_SUCCESS);
}
