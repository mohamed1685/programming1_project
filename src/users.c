#include "../headers/Banksys.h"
#include "../headers/transactions.h"
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
    printf("successfully loaded %d users\n\n",count);



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

void menu(Account *accounts,int *numAccptr,int loginstatus){
    int userin=0;
    
    if(loginstatus){
        while(userin!=12){
            printf("*****************************************\n");
            printf("* Welcome to The Bank System       *\n");
            printf("*****************************************\n");
            printf("* Enter your choice (1-12):            *\n");
            printf("* *\n");
            printf("* 1. Add Account                       *\n");
            printf("* 2. Delete Account                    *\n");
            printf("* 3. Modify Account                    *\n");
            printf("* 4. Search                            *\n");
            printf("* 5. Advanced Search                   *\n");
            printf("* 6. Change Status                     *\n");
            printf("* 7. Withdraw                          *\n");
            printf("* 8. Deposit                           *\n");
            printf("* 9. Transfer                          *\n");
            printf("* 10. Report                           *\n");
            printf("* 11. Print                            *\n");
            printf("* 12. Quit                             *\n");
            printf("*****************************************\n");
            printf("Choice: ");
            
            // Check if scanf failed to read a number
            scanf("%d", &userin);
            
            // This clears the leftover '\n' so it doesn't mess up your next function
            getchar();
            switch(userin) {
                case 1:
            {
                addacc(accounts,numAccptr);
                break;
            }
                case 2:
            {
                
                break;
            }
                case 3:
            {
                
                break;
            }
                case 4:
            {
                
                break;
            }
                case 5:
            {
                
                break;
            }

                case 6:
            {
                
                break;
            }

                case 7:
            
            {
                withdraw(accounts,*numAccptr);
                break;
            }
                case 8:
            {
                deposit(accounts,*numAccptr);
                break;
            }
                case 9:
            {   transfer(accounts,*numAccptr);
                break;
            }
                case 10:
            {
                


                break;
            }
                case 11:
            {
                printaccdetails(accounts,numAccptr);
                break;
            };
                case 12:
            {
                printf("Succesfully exited system,Goodbye");
                break;
            }
            

            }
        }
    }
}

