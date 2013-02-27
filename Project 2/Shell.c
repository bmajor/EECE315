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

void changeDir(const char *newDir) {
	int ret; // if fail to change dir, ret should eq to -1 but the current working dir shall remain unchanged
	ret = chdir(newDir);
}

int main () {

	struct command_t *command = malloc(sizeof *command); // Shell initialization

	char CompName[MAXHOSTNAMELEN+1];
	gethostname(CompName, MAXHOSTNAMELEN);

	char PathName [PATH_MAX+1];	
	getcwd(PathName, PATH_MAX);

	char CommandLine[PATH_MAX*2];

	//while(1) //Continuously run the command line UNLESS exit is called.
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
		char* Args;
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

		// Find the full pathname for the file

		realpath(shortPath,Path);

		// Change the directory if the first argument is cd
		if (strcmp(command->argv[0],"cd") == 0 ){
			if ( command->argc < 2 ) {
				changeDir(getenv("HOME"));
			} else {
				changeDir(command->argv[1]);
			}
		} else if (strcmp(command->argv[0],"[something]") == 0 ){
		
		} else {
			// Create a process to execute the command
			/*	
			pid_t childPID;		
			childPID = fork();
			if(childPID >= 0){
				execv(path, command.argv);
			}
			else{
			printf("\nCould not fork process");
			}
			*/
			// Parent waits until child finishes executing command }
	}	
	printf("\nPress Enter to exit\n");
	while(getchar() != '\n');

	return 0;
	}
}
