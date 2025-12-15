#include "Banksys.h"
#include <ctype.h> 

void loadUsers(User *users, int *numUsersPtr){
    FILE *file=fopen("users.txt","r");
    if(file==NULL){
        printf("Users File cant be loaded");
        *numUsersPtr=0;
        return;
    }

    char line[line_length];
    char *delim=" \t\n";
    int count=0;

    while((fgets(line,sizeof(line),file)!=NULL)&&count<maxUsers)
    {
        char *fileUser;
        char *filePass;

        fileUser=strtok(line,delim);
        filePass=strtok(NULL,delim);

        if(fileUser!=NULL && filePass!=NULL){
            strcpy(users[count].username,fileUser);
            strcpy(users[count].password,filePass);
            count++;
        }

    }
    fclose(file);
    *numUsersPtr=count;
    printf("successfully loaded %d users",count);



}
int login(User *users, int numUsers){
    char userIn[Max_input_length];
    char passIn[Max_input_length];
    int i;

    printf("**********  Bank Log-in  **********\n");
    printf("Enter your username: ");
    
    if(scanf("%49s",userIn)!=1)
        return loginFail;

    printf("\nEnter your password: ");
    
    if(scanf("%49s",passIn)!=1)
        return loginFail;

    for(i=0;i<numUsers;i++){
        if(strcmp(userIn,users[i].username)==0){
            if(strcmp(passIn,users[i].password)==0){
                printf("\nLogin Successful");
                return loginSuccess;
            }
        }
    }


printf("\nLogin failed. Invalid Username or Password.");
return loginFail;
    
}   