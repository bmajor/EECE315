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

void getPathName() {
	char PathName [PATH_MAX+1];	
	getcwd(PathName, PATH_MAX);

	if (getcwd(PathName, PATH_MAX) == NULL){
			perror("getcwd() error");
		}
		else {	
			printf("%s$ ",PathName); // Print full pathname + $
		}
}

void changeDir(const char *newDir) {
	int ret; // if fail to change dir, ret should eq to -1 but the current working dir shall remain unchanged
	ret = chdir(newDir);
	getPathName();
}

int main () {

	struct command_t *command = malloc(sizeof *command); // Shell initialization

	char CompName[MAXHOSTNAMELEN+1];
	gethostname(CompName, MAXHOSTNAMELEN);

	char CommandLine[PATH_MAX*2];

	//while(1) //Continuously run the command line UNLESS exit is called.
	{
		int k=0;
		//Print the prompt String
		printf("%s:~",CompName);
		getPathName();

		// Read the command line and parse it
		char* Args;

		gets(CommandLine);
		Args = strtok (CommandLine, " ");
		command->name = malloc(NAME_MAX+1);
		command->name = Args;
		printf("%s\n", command->name);

		while(Args != NULL){
			command->argv[k] = malloc(PATH_MAX);
			strcpy(command->argv[k], Args);
			command->argc += 1;
			Args = strtok (NULL, " ");
			k++;		
		}

		// Change the directory if the first argument is cd
		if ( strcmp(command->argv[0],"cd") == 0 )
			changeDir(command->argv[1]);

		// Find the full pathname for the file


		// Create a process to execute the command
		// Parent waits until child finishes executing command }
		printf("\nPress Enter to exit\n");
		while(getchar() != '\n');
	}	

	return 0;
}
