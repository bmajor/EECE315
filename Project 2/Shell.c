#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>
#include <linux/limits.h>

struct command_t { 
	char *name;
	int argc;
	char *argv[];
};


int main () {

	struct command_t *command; // Shell initialization
	
	char CompName[MAXHOSTNAMELEN+1];
	gethostname(CompName, MAXHOSTNAMELEN);
	
	char PathName [PATH_MAX+1];	
	getcwd(PathName, PATH_MAX);
	
	char CommandLine[4092];
	
	//while(1) //Continuously run the command line UNLESS exit is called.
	{
		//Print the prompt String
		printf("%s",CompName);		
		printf(":~");		
		if (getcwd(PathName, PATH_MAX) == NULL){
			perror("getcwd() error");
		}
		else {	
			printf("%s",PathName);
		}		
		printf("$ ");		

		// Read the command line and parse it
		char* Args;
		
		scanf("%s", CommandLine);
		Args = strtok (CommandLine, " ");
		while(Args != NULL){
			printf("%s", Args);		
			break;
		}
		
		// Find the full pathname for the file
		// Create a process to execute the command
		// Parent waits until child finishes executing command }
		printf("\nPress Enter to exit\n");
		while(getchar() != '\n');
	}

	return 0;
}
