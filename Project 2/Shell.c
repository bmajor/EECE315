#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

struct command_t { 
	char *name;
	int argc;
	char *argv[];
};


int main () {

	struct command_t *command; // Shell initialization
	
	char CompName[MAXHOSTNAMELEN+1];
	size_t CompNameLen = MAXHOSTNAMELEN;
	gethostname(CompName, CompNameLen);

	
	//while(1)
	{
		int i;
		for(i=0;CompName[i] != '\0';i++){		
		printf("%c",CompName[i]);
		}
		printf("$~$");

		// Print the prompt string
		// Read the command line and parse it 
		// Find the full pathname for the file
		// Create a process to execute the command
		// Parent waits until child finishes executing command }
		printf("\nPress Enter to exit");
		while(getchar() != '\n');
	}

	return 0;
}
