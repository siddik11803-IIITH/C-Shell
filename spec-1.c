#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#define MAX_PATH_BUF 200
#define MAX_COMMAND 200

void processCommand(char inputString[MAX_PATH_BUF])
{
    int readIndex = 0, writeIndex;
    char outputArray[MAX_PATH_BUF];
    while (inputString[readIndex] == ' ' || inputString[readIndex] == '\t')
    {
        readIndex++;
    }

    for (writeIndex = 0; inputString[readIndex] != '\0'; readIndex++)
    {
        if (inputString[readIndex] == ' ' && inputString[readIndex - 1] == ' ')
        {
            continue;
        }
        outputArray[writeIndex] = inputString[readIndex];
        writeIndex++;
    }
    outputArray[writeIndex] = '\0';
    strcpy(inputString, outputArray);
}


void userName(char string[_SC_LOGIN_NAME_MAX]){
    char login_name[_SC_LOGIN_NAME_MAX];
    int check = getlogin_r(login_name, _SC_LOGIN_NAME_MAX);
    if (check)
    {
        perror("Login Name error\n"); 
    }
    strcpy(string, login_name);
}

void hostName(char string[_SC_HOST_NAME_MAX]){
    char host_name[_SC_HOST_NAME_MAX];
    int check = gethostname(host_name, _SC_HOST_NAME_MAX);
    if (check)
    {
        perror("Host name Error\n");
    }
    strcpy(string, host_name);
}

void directory(char string[MAX_PATH_BUF]){
    char dir[MAX_PATH_BUF];
    getcwd(dir, MAX_PATH_BUF);
    strcpy(string, dir);
    // no need of error checking.
}