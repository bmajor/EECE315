#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <sys/utsname.h> // include this to use uname();

struct command_t { 
	char *name;
	int argc;
	char *argv[];
};

struct utsname unameData;

int main () {

	struct command_t *command; // Shell initialization
	wchar_t CompName [MAX_COMPUTERNAME_LENGTH + 1];
	DWORD CNameSize = sizeof ( CompName);
	GetComputerName( &CompName[0], &CNameSize);
	
	// Or could try this; to get comp name;
	if ( uname(&unameData) == 0) {
//	printf("%s\n%s\n%s\n%s\n%s\n", unameData.sysname, unameData.nodename, unameData.release, unameData.version, unameData.machine);
	int i = 0;
	for (i; i < 8; i++) // arbitrary size
		if (  unameData.nodename[i] != '\0')
			printf("unameData.nodename[i] = %c \n", unameData.nodename[i]);
	} else
		printf("uname() failure\n");
	}
	
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
