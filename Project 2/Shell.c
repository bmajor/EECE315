#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>

struct command_t { 
	char *name;
	int argc;
	char *argv[];
};

int main () {

	struct command_t* command = malloc(sizeof (struct command_t)); // Shell initialization
	
	char CompName[MAXHOSTNAMELEN+1];
	gethostname(CompName, MAXHOSTNAMELEN);
	
	char PathName [PATH_MAX+1];	
	getcwd(PathName, PATH_MAX);
	
	char CommandLine[PATH_MAX*2];
	pid_t childPID;
	
	char* Args = malloc(PATH_MAX+1);
	char* shortPath = malloc(PATH_MAX+3);
	command->name = malloc(NAME_MAX+1);
	
	
	while(1) //Continuously run the command line unless "exit" is entered.
	{	
		int k=0;
		// Read the command line and parse it
		
		strcpy(shortPath, "./");
		char Path [PATH_MAX];
		
		do{			
			//Print the prompt String
			printf("%s:~",CompName);
			if (getcwd(PathName, PATH_MAX) == NULL){
				perror("getcwd() error");
			}
			else {	
				printf("%s$ ",PathName);
			}	
		
			gets(CommandLine);
			Args = strtok (CommandLine, " ");
						
		}while(Args == NULL);		
		
		
		
		//Parsing the initial command
		if(strrchr(Args, '/') == NULL){			
			strcpy(command->name, Args);
		}
		else{
			char* last = strrchr(Args, '/');
			if(strstr(Args,"./")==Args){				
				strcpy(shortPath, Args);				
			}
			else{
				shortPath = strcat(shortPath, Args); 		
			}
			strcpy(command->name, last+1);
			Args = command->name;
		}
		
		
		//Parsing arguments		
		while(Args != NULL){
			command->argv[k] = malloc(PATH_MAX+1);
			strcpy(command->argv[k], Args);
			command->argc = k+1;
			Args = strtok (NULL, " ");
			k++;		
		}
		
		//commands that run on the parent thread
		if(strcmp(command->argv[0],"")==0);
		
		else if (strcmp(command->argv[0],"exit") == 0 ){
			
			free(command->argv[0]);
			break;
		}
		
		
		else if (strcmp(command->argv[0],"cd") == 0 ){
			
			int ret;
			if(command->argc < 2) {
				chdir(getenv("HOME"));
			}
			else{
				ret = chdir(command->argv[1]);	
				if(ret<0){
					printf("No such file or directory found\n");
				}	
			}
			
		}
		
		else if (strcmp(command->argv[0],"set") == 0){
		
		}
		
		//If it is not an instruction to be run by the parent, fork a child
		else {
			childPID = fork();
		
		
			if(childPID == 0){
				
			
						
				if (strcmp(command->argv[0],"printenv") == 0 ){
					printf("The environment variables are:\n%s\n", getenv("PATH"));
				}
			
				else if (strcmp(command->argv[0],"set") == 0 ){
					setenv(command->argv[1],command->argv[2],1); //sets environmental variables in 
				}						     //arg[1] to arg[2]
			
				else{
					if(realpath(shortPath,Path) != NULL){
						execv(Path, command->argv);
					}
					else{
						printf("The file could not be found or run\n");
					}
				}
				
				return 0;
			}
			else if (childPID == -1){
				printf("\nCould not fork process");
			}
		
			// Parent waits until child finishes executing command }
		
			else{
				wait();
			}	
		}
		
		
		for(k=0;k<(command->argc);k++){
			free(command->argv[k]);
		}	
		
	}

	free(Args);
	free(shortPath);
	free(command->name);
	free(command);
	return 0;	
}
