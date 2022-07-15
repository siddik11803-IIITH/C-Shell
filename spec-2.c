#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
#define MAX_PATH_BUF 200
#define MAX_COMMAND 200

char* checkCommand(char string[MAX_COMMAND]){
    char* commandString = malloc(sizeof(char)*(MAX_COMMAND));
    for(int i = 0; string[i]; i++){
        if(string[i] == ' ' || string[i] == '\n'){
            commandString[i] = '\0';
            break;
        }else{
            commandString[i] = string[i];
        }
    }
    return commandString;
}

void echoCommand(char string[MAX_COMMAND]){
    char* commandString = malloc(sizeof(char)*(MAX_COMMAND));
    (commandString) = &(string[5]);
    printf("%s", commandString);
}


void cdCommand(char string[MAX_COMMAND], char curr_dir[MAX_COMMAND],  char root_dir[MAX_COMMAND]){
    int back;
    char* directory = malloc(sizeof(char)*(MAX_COMMAND));
    (directory) = &(string[3]);
    directory[strlen(directory) - 1] = '\0';
    if(strcmp(directory, "~") == 0){
       int y = chdir(root_dir);
        strcpy(curr_dir, "~");
        return;
    }
    int x = chdir(directory);
    getcwd(directory, MAX_PATH_BUF);
    if(x < 0){
        perror("chdir error");
    }
    if(strlen(root_dir) <= strlen(directory)){
        back = 0;
    }else{
        back = 1;
    }
    if(back == 1){ // back ward (Not Complete)
        // Now we have to change the curr-dir    
        getcwd(curr_dir, MAX_PATH_BUF);
    }else if(back == 0){
        
        char* temp = malloc(sizeof(char)*(MAX_COMMAND));
        (temp) = &(directory[strlen(root_dir)]);
        char temp_1[MAX_COMMAND] = "~";
        strcat(temp_1, temp);
        strcpy(curr_dir, temp_1);
    }

    
}