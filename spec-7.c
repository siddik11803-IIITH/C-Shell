#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH_BUF 200
#define MAX_COMMAND 200

void processRepeatCommand(char string[MAX_COMMAND], char current_dir[MAX_PATH_BUF], char root_dir[MAX_PATH_BUF]){
    char* command = malloc(sizeof(char)*MAX_COMMAND);
    (command) = &(string[7]);
    char *temp = command;
    char num[4];
    int i= 0;
    while(*temp != ' '){
        num[i] = *temp;
        i++;
        temp++;
    }
    num[i] = '\0';
    int number = atoi(num);
    // Continue
    (command) = &(command[2]);
    char function_command[MAX_COMMAND];
    strcpy(function_command, checkCommand(command));
    for(int i = 0; i < number; i++){
        // Now the function is obtained from the user.
        if (strcmp(function_command, "cd") == 0)
        {
            if (strlen(command) > 3)
            {                                                 // So that we wouldn't witness seg faults.
                cdCommand(command, current_dir, root_dir); // The 3rd parameter is the one where we check if it is the back.
            }
        }
        else if (strcmp(function_command, "echo") == 0)
        {
            if (strlen(command) > 5)
            {                         // OK
                echoCommand(command); 
            }
        }
        else if (strcmp(function_command, "pwd") == 0)
        {
            printf("%s\n", current_dir); // printing Current Directory.
        }
        else if (strcmp(function_command, "clear") == 0 || strcmp(function_command, "cls") == 0)
        {
            system("clear"); // Clearing the screen
        }
        else if (strcmp(function_command, "quit") == 0 || strcmp(function_command, "exit") == 0)
        {
            break; // Exitting the shell
        }
        else if(strcmp(function_command, "ls") == 0)
        {
            // code for ls
            processLsCommand(command);
        }
        else if(strcmp(function_command, "pinfo") == 0)
        {   
            processPinfoCommand(command);
        }
        else if(strcmp(function_command, "sleep") == 0)
        {
            system(command);
        }
        else
        {
            printf("%s:Command not found\n", function_command); // Error Handling.
        }
    }
}