#include <stdio.h>

#include <stdlib.h>
#include "spec-1.c"
#include "spec-2.c"
#include "spec-3.c"
#include "spec-5.c"
#include "spec-7.c"
#include "bonus.c"

int main()
{
    char host_name[_SC_HOST_NAME_MAX];
    hostName(host_name);
    char login_name[_SC_LOGIN_NAME_MAX];
    userName(login_name);
    char root_dir[MAX_PATH_BUF];
    char current_dir[MAX_PATH_BUF];
    directory(root_dir);
    strcpy(current_dir, "~");
    char command[MAX_COMMAND];
    char function_command[MAX_COMMAND];
    // Array of Commands for bonus
    char history[20][MAX_COMMAND];
    int num = 0;
    while (1)
    {
        printf("<%s@%s:%s> ", login_name, host_name, current_dir); // This makes the basic structure to be ready;
        fgets(command, MAX_COMMAND, stdin);
        processCommand(command);
        addToHistory(command, history, num);
        num++;
        
        repeat: // This is the place where the command comes in the case of repeat.
        // Now we have the formatted command with the flags attached to it. (Work on 090921)
        // We have to seperate the first word of the scentence now.
        // Work resumed on 11th spetember
        strcpy(function_command, checkCommand(command));
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
        else if(strcmp(function_command, "repeat") == 0)
        {
            if(numberOfWords(command) >= 3){
                processRepeatCommand(command, current_dir, root_dir);

            }

        }
        else if(strcmp(function_command, "sleep") == 0)
        {
            system(command);
        }
        else if(strcmp(function_command, "history") == 0){
            processHistory(command, history, num);

        }
        else
        {
            num--;
            printf("%s:Command not found\n", function_command); // Error Handling.
        }
    }

    return 0;
}