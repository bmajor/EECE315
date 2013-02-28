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
	
	
	char* Args;
	char* shortPath = (char*)malloc(PATH_MAX+3);
	command->name = malloc(NAME_MAX+1);
	
	
	while(1) //Continuously run the command line unless "exit" is entered.
	{	
		int k=0;
		// Read the command line and parse it
		
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
			
		}while(strcmp(CommandLine, "")==0);
		
		Args = strtok (CommandLine, " ");
		//Parsing the initial command
		if(strrchr(Args, '/') == NULL){			
			strcpy(command->name, Args);
			strcpy(shortPath, Args);
		}
		else{
			char* last = strrchr(Args, '/');
			strcpy(shortPath, Args);
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
		command->argv[k] = NULL;
		command->argc = k;
		
		
		//commands that run on the parent thread
		if(strcmp(command->name,"")==0){
			
		}
		
		else if (strcmp(command->name,"exit") == 0 ){
			
			free(command->argv[0]);
			break;
		}
		
		
		
		else if (strcmp(command->name,"cd") == 0 ){
			
			int ret;
			if(command->argc < 3) {
				chdir(getenv("HOME"));
			}
			else{
				ret = chdir(command->argv[1]);	
				if(ret<0){
					printf("No such file or directory found\n");
				}	
			}
			
		}
		
		
		//If it is not an instruction to be run by the parent, fork a child
		else {
		
			for(k=0;command->argv[k]!=NULL;k++){
				printf("%d%s%d%s\n",k,command->name,command->argc,command->argv[k]);
			}
			
			childPID = fork();
			
			if(childPID == 0){
				
				
				char* temp =getenv("PATH");
				char temparr[PATH_MAX];
				char* temp2 = &temparr[0];
				char storage[PATH_MAX];	
				
				if(temp == NULL){				
					printf("env vars are nonexistant");
				
				}
				else strcpy(storage, temp);
				
				temp = strcpy(storage, temp);
				temp2 = strcpy(temp2, temp);
				
				temp = strtok(storage, ":");
				
				strcat(temp2, shortPath);
				
				while(1){
					if(access(temp2,F_OK) == 0){
						printf("file found");
						execv(temp2, command->argv);
					}
					else if(access(temp2,F_OK) == 0){
					 	
					 }
					temp = strtok(NULL, ":");
					
					if(temp == NULL){
						break;
					}
					strcpy(temp2, temp);
					strcat(temp2,shortPath);
					printf("searching %s\n", temp2);
				}
					
			
				printf("\nFile not found");
				for(k=0;k<(command->argc);k++){
					free(command->argv[k]);
				}
				free(command->name);
				return 0;
				
			}
			else if (childPID == -1){
				printf("\nCould not fork process");
			}	
		
			// Parent waits until child finishes executing command if a & is not found at end of command
		
			else{
				//if(!(strcmp(command->argv[(command->argc)-1], "&"))){
					wait();
				//}
			}	
		}
		
		
		for(k=0;k<(command->argc);k++){
			free(command->argv[k]);
		}	
		
	}//end of the while loop
	
	free(command->name);
	return 0;	
}
