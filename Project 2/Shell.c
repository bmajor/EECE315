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
		
		for(k=0;command->argv[k]!=NULL;k++){
		printf("%d%s%d%s\n",k,command->name,command->argc,command->argv[k]);
		}
		//commands that run on the parent thread
		if(strcmp(command->argv[0],"")==0);
		
		else if (strcmp(command->argv[0],"exit") == 0 ){
			
			free(command->argv[0]);
			break;
		}
		
		
		
		else if (strcmp(command->argv[0],"cd") == 0 ){
			
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
		
		
		// Rename a file. Ex: mv ./folder/oldname.txt ./folder/newname.txt
		else if (strcmp(command->argv[0],"mv") == 0){
			rename(command->argv[1], command->argv[2]);
		}
		
		//If it is not an instruction to be run by the parent, fork a child
		else {
			
			childPID = fork();
			if(childPID == 0){
				
				printf("forked");
				char* temp =getenv("PATH");
				printf("hereoeajifejowfw%s", temp);
				char storage[PATH_MAX];		
				
				if(temp == NULL){				
					printf("env vars are nonexistant");
				
				}
				else strcpy(storage, temp);
				printf("here");
				temp = strcpy(storage, temp);
				temp = strtok(storage, ":");
				while(temp != NULL){
					strcat(temp,shortPath);;
					execv(temp, command->argv); 
					temp = strtok(NULL,":");
					
				}	
				
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
