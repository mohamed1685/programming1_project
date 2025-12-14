#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void login();


int main(){


    return 0;
}

int login(){
    char userIn[100];
    char passIn[100];

    printf("**********  Bank Log-in  **********");
    printf("Enter your username: ");
    
    if(scanf("%s",userIn)!=1)
        return 0;

    printf("\nEnter your password: ");
    
    if(scanf("%s",passIn)!=1)
        return 0;

    FILE *file=fopen("users.txt","r");
    if(file==NULL){
        printf("Users File cant be loaded");
        return 0;
    }

    char line[100];
    char *delim=" \t\n";

    while(fgets(line,sizeof(line),file)!=NULL)
    {
        char *fileUser;
        char *filePass;

        fileuser=strtok(line,delim);
        filePass=strtok(NULL,delim);

        if((strcmp(userIn,fileUser)==0)&&(strcmp(passIn,filePass)==0)){
            fclose(file);
            printf("login successful");
            return 1;
        }

    }
}