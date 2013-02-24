#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

struct command_t { 
	char *name;
	int argc;
	char *argv[];
};


int main () {

	struct command_t *command; // Shell initialization
	wchar_t CompName [MAX_COMPUTERNAME_LENGTH + 1];
	DWORD CNameSize = sizeof ( CompName);
	GetComputerName( &CompName[0], &CNameSize);

	while(1)
	{
		int i;
		for(i=0;i<MAX_COMPUTERNAME_LENGTH-1;i++){
			printf("%c", CompName[i]);
		}
		printf("$");



		// Print the prompt string
		// Read the command line and parse it 
		// Find the full pathname for the file
		// Create a process to execute the command
		// Parent waits until child finishes executing command }
		system ("Pause");
	}

	return 0;
}
