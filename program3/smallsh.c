#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
int ID;
int last_exit=-100;
int endID=0;
//char command[2048]; //input string 

char **args;	//parsed data for arguments
char *program;	//program to be run
int buffersize=2048;//max input size
int position=0; 	//used for checking position of string
int status=1;	//status of shell
int bg=0;
int pro_run=0;
int running[1000];
void sigHandler(int x)
{
	//printf("\nYou cant kill me!!!\n:");
	//fflush(NULL);
	//kill(spawnpid,SIGKILL);
}


int main(int argc, char *argv[])
{
	signal(SIGINT,sigHandler);
	int index=0;
	printf("Starting Shell\n");
	ID=getpid();
	printf("Process ID: %d\n\n\n",ID);
	for(index=0;index<1000;index++)
	{
		running[index]=0;
	}
while(status!=0)
{
	
	//fflush(NULL);
	//sleep(.75);
	bg=0;
	for(index=0;index<pro_run;index++)
	{
		if(running[index]!=0)
		{
			endID = waitpid(running[index], &last_exit, WNOHANG|WUNTRACED);
			if(endID==0){continue;}
			if(endID==running[index]){printf("[-] %d Status: %d",endID,last_exit);running[index]=0;}
		}
		
	}
	printf(":");//Shell prompt
	fflush(NULL);
	
	
	
	char *command=NULL;
	ssize_t buf=0;
	status=getline(&command,&buf,stdin);
	if(status==1){continue;}
	status=1;
	char **tokens=malloc(512 *sizeof(char*));
	char *token;
	position=0;	//reset position to 0
	if(!tokens){fprintf(stderr,"Allocation Error!!\n");exit(-1);}
	
	token= strtok(command, " \t\r\n\a");
	while(token !=NULL)
	{
		tokens[position]=token;
		position++;
		token= strtok(NULL," \t\r\n\a");
	}
	tokens[position]=NULL;

	if(strcmp(tokens[0],"#")==0)
	{//'Status' will give info on last forground process to end, no arguments
		continue;	
	}
	

	//check for exit command
	if(strcmp(tokens[0],"exit")==0)
	{//'Status' will give info on last forground process to end, no arguments
		status=0;
		continue;	
	}
	
	//check for built in commands
	if(strcmp(tokens[0],"status")==0)
	{//'Status' will give info on last forground process to end, no arguments
		printf("Last Exit: %d\n",last_exit);fflush(NULL);
		continue;	
	}
	if(strcmp(tokens[0],"cd")==0)//change to look at first word
	{//'cd' changes working directory,  with no argument goes to HOME,
		//:printf("cd command issued....\n");fflush(NULL);
		//printf("Position: %d",position);
		//if(position==1){chdir(HOME);}
		if(position==2){chdir(tokens[1]);}
		continue;
	}
	if(strcmp(tokens[position-1],"&")==0){bg=1;}
	
	
	int input_file=-1;
	int output_file=-1;
	for(index=0;index<position;index++)
	{
		if(strcmp(tokens[index],"<")==0)//redirect input
		{
			//printf("INPUT REDIRECT");fflush(NULL);
			int spawnpid=fork();
			switch(spawnpid)
			{
				case -1:	perror("Fork Failed....");
							exit(1);
							break;
				case 0:		//Child
							input_file=open(tokens[index+1],O_RDONLY);
							int re_input=dup2(input_file,0);
							tokens[index]=NULL;
							execvp(tokens[0],tokens);
							perror("exec");//wont run unless error
							return(1);
				default:	waitpid(spawnpid,last_exit);break;//Original (parent)
			}
			break;	
		}


		if(strcmp(tokens[index],">")==0)//redirect output
		{
			
			int spawnpid=fork();
			switch(spawnpid)
			{
				case -1:	perror("Fork Failed....");
							exit(1);
							break;
				case 0:		//Child
							//printf("OUTPUT REDIRECT");fflush(NULL);
							output_file=open(tokens[index+1],O_WRONLY|O_CREAT, 0644);
							int re_input=dup2(output_file,1);
							tokens[index]=NULL;
							execvp(tokens[0],tokens);
							perror("exec");//wont run unless error
							return(1);
				default:	waitpid(spawnpid,last_exit);break;//Original (parent)
			}	
			break;	
		}
		
		if(index==position-1)//no redirect
		{
			//printf("NO REDIRECT");fflush(NULL);
			int spawnpid=fork();
			switch(spawnpid)
			{
				case -1:	perror("Fork Failed....");
							exit(1);
							break;
				case 0:		//Child
							//output_file=open(tokens[index+1],O_WRONLY);
							//int re_input=dup2(input_file,0);
							//tokens[index]=NULL;
							if(bg==1){
								int devNull = open("/dev/null", O_WRONLY);
								int re_input=dup2(devNull,1);
								
								}
							execvp(tokens[0],tokens);
							perror("exec");//wont run unless error
							return(1);
				default:	if(bg==0){waitpid(spawnpid,&last_exit,WUNTRACED);break;}//Original (parent)
							printf("[+] %d\n",spawnpid);
							running[pro_run]=spawnpid;//adds into array of running
							pro_run++;
						    
			}				
		
			break;	
		}
	}
	
	
	free(tokens);
}//end 'main' while loop

printf("Exiting Shell....\n\n\n");

return 0;
}//end main
