#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/resource.h>
#define MAX_PATH_BUF 200
#define MAX_COMMAND 200

int numberOfWords(char string[MAX_COMMAND])
{
    int nw = 0;
    char *temp = &(string[0]);
    while (*temp)
    {
        if (*(temp) == ' ' || *(temp) == '\n')
        {
            nw++;
        }
        temp++;
    }
    return nw;
}

int getVSZ(int pid){
    char* path = malloc(sizeof(char)*MAX_PATH_BUF);
    sprintf(path, "/proc/%d/statm", pid);
    FILE* fp = fopen(path, "r");
    if(fp == NULL){
        perror(path);
        return -1;
    }
    long int x;
    int c = fscanf(fp, "%ld", &x);

    return x*4;
}

char getStatusRunning(int pid){
    char c;
    char tempString[MAX_PATH_BUF];
    int tempInt;
    char* path = malloc(sizeof(char)*MAX_PATH_BUF);
    sprintf(path, "/proc/%d/stat", pid);
    FILE* fp = fopen(path, "r");
    if(fp == NULL){
        perror(path);
        return -1;
    }
    fscanf(fp, "%d %s %c", &tempInt, tempString, &c);
    return c;
}


void processPinfoCommand(char string[MAX_COMMAND])
{
    if (strlen(string) <= 7)
    {
        // PID
        struct rusage temp;
        getrusage(getpid(), &temp);
        printf("pid --%d\n", getpid());
        // Running Status
        printf("Process Status -- %c\n", getStatusRunning(getpid()));
        // VSZ
        printf("memory -- %d {Virtual Memory}\n", getVSZ(getpid()));
        // EXE PATH
        char buf[MAX_COMMAND];
        char buf_1[MAX_COMMAND];
        sprintf(buf, "/proc/%d/exe", getpid());
        int x = readlink(buf, buf_1, MAX_COMMAND);
        printf("executable file -- %s\n", buf_1);
        if (x < 0)
        {
            perror("PINFO ERROR");
        }
        // Write the code to print the current process info
        // Continue here.
        return;
    }
    (string) = &(string[6]);
    // Here, we shall write the code for a certain pid.
    if (numberOfWords(string) == 1)
    {
        int id = atoi(string);
        // Nowe have the ID of the process.
        //PID
        printf(("pid -- %d\n"), id);
        // Status
        printf("Process status -- %c\n", getStatusRunning(id));
        //Memory
        printf("memory -- %d {Virtual Memory}\n", getVSZ(id));
        //EXEC
        char buf[MAX_COMMAND];
        char buf_1[MAX_COMMAND];
        sprintf(buf, "/proc/%d/exe", id);
        int x = readlink(buf, buf_1, MAX_COMMAND);
        printf("executable file -- %s\n", buf_1);
        if (x < 0)
        {
            perror("PINFO ERROR");
        }
    }
    else
    {
        printf("Error: More than one processes requested.\n");
        return;
    }
}
