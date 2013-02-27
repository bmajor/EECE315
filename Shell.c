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

	struct command_t *command = malloc(sizeof *command); // Shell initialization
	
	char CompName[MAXHOSTNAMELEN+1];
	gethostname(CompName, MAXHOSTNAMELEN);
	
	char PathName [PATH_MAX+1];	
	getcwd(PathName, PATH_MAX);
	
	char CommandLine[PATH_MAX*2];
	
	while(1) //Continuously run the command line UNLESS exit is called.
	{
		
		int k=0;
		//Print the prompt String
		printf("%s:~",CompName);
		if (getcwd(PathName, PATH_MAX) == NULL){
			perror("getcwd() error");
		}
		else {	
			printf("%s$ ",PathName);
		}

		// Read the command line and parse it
		char* Args = malloc(PATH_MAX);
		char shortPath [PATH_MAX];
		char Path [PATH_MAX];
		
		gets(CommandLine);
		Args = strtok (CommandLine, " ");
		command->name = malloc(NAME_MAX+1);
		
		if(strrchr(Args, '/') == NULL){			
			command->name = Args;
		}
		else{
			char* last = strrchr(Args, '/');
			strcpy(shortPath, Args);
			strcpy(command->name, last+1);
			Args = command->name;
		}
				
		while(Args != NULL){
			command->argv[k] = malloc(PATH_MAX);
			strcpy(command->argv[k], Args);
			command->argc += 1;
			Args = strtok (NULL, " ");
			k++;		
		}
		
		command -> argv[k] = NULL;
		
		if (strcmp(command->argv[0],"exit") == 0 ){
			return 0;
		}
		
		pid_t childPID;
		childPID = fork();
		//Fork a child here and run all following instructions as child
		if(childPID == 0){
				
			// Change the directory if the first argument is cd
			if (strcmp(command->argv[0],"cd") == 0 ){

				if(command->argc <2) {
					chdir(getenv("HOME"));
				}
				else{
					chdir(command->argv[1]);
				}
			}
			
			else if (strcmp(command->argv[0],"exit") == 0 ){
				return 0;
			}
			
			else if (strcmp(command->argv[0],"printenv") == 0 ){
				printf("%s", getenv("PATH"));
			}
			
			else{
			//	realpath(shortPath,Path);
			//	execv(Path, command.argv);
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

	return 0;
}
