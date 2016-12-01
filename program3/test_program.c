
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int ID;
char command[2048];//Max size of input
int main()
{
	printf("\n\n\nStarting Test program\n");
	ID=getpid();
	printf("Process ID: %d\n\n\n",ID);
    sleep(5);
    printf("Test program finished....\n\n\n");

return 0;
}//end main