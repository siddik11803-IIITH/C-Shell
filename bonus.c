#include<stdio.h>
#include <string.h>
#define MAX_PATH_BUF 200
#define MAX_COMMAND 200

void processHistory(char string[MAX_COMMAND], char array[20][MAX_COMMAND], int num){
    if(num <= 20){
        for(int i = 0; i < num; i++){
           printf("%s", array[i]);
        }
    }else{
        for(int i = 0; i < 20; i++){
            printf("%s", array[i]);
        }
    }
}

void addToHistory(char string[MAX_COMMAND], char array[20][MAX_COMMAND], int num){
    if(num < 20){
        strcpy(array[num], string);
    }else{
        for(int i = 0; i < 20; i++){
            strcpy(array[i], array[i + 1]);
        }
        strcpy(array[19], string);
    }
}