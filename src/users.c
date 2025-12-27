#include "../headers/Banksys.h"
#include "../headers/transactions.h"
#include "../headers/query.h"
#include "../headers/delete_multiple.h"
#include <ctype.h> 

void loadUsers(User *users, int *numUsersPtr){
    FILE *file=fopen("users.txt","r");
    if(file==NULL){
        printf(RED "Error: Users File cant be loaded\n" RESET);
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
    printf(GREEN "Successfully loaded %d users\n\n" RESET, count);
}


int login(User *users, int numUsers){
    char userIn[Max_input_length];
    char passIn[Max_input_length];
    int i;

    printf(BLUE "**********" YELLOW "  Bank Log-in  " BLUE "**********\n" RESET);
    printf(YELLOW "Enter your username: " RESET);
    
    if(scanf("%49s",userIn)!=1)
        return loginFail;

    printf(YELLOW "\nEnter your password: " RESET);
    
    if(scanf("%49s",passIn)!=1)
        return loginFail;

    for(i=0;i<numUsers;i++){
        if(strcmp(userIn,users[i].username)==0){
            if(strcmp(passIn,users[i].password)==0){
                printf(GREEN "\nLogin Successful" RESET);
                return loginSuccess;
            }
        }
    }

    printf(RED "\nLogin failed. Invalid Username or Password.\n" RESET);
    return loginFail;
}

void menu(Account *accounts,int *numAccptr,int loginstatus){
    int userin=0;
    
    if(loginstatus){
        while(userin!=14){
            printf("\n");
            printf(BLUE "*****************************************\n" RESET);
            printf(BLUE "*" YELLOW "      Welcome to The Bank System       " BLUE "*\n" RESET);
            printf(BLUE "*****************************************\n" RESET);
            printf(BLUE "*" RESET " Enter your choice (1-14):             " BLUE "*\n" RESET);
            printf(BLUE "* *\n" RESET);
            printf(BLUE "*" CYAN " 1. Add Account                       " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 2. Delete Account                    " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 3. Modify Account                    " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 4. Search                            " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 5. Advanced Search                   " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 6. Change Status                     " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 7. Withdraw                          " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 8. Deposit                           " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 9. Transfer                          " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 10. Report                           " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 11. Print                            " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 12. Delete Multiple                  " BLUE "*\n" RESET);
            printf(BLUE "*" CYAN " 13. Save                             " BLUE "*\n" RESET);
            printf(BLUE "*" RED  " 14. Quit                             " BLUE "*\n" RESET);
            printf(BLUE "*****************************************\n" RESET);
            printf(YELLOW "Choice: " RESET);
            
            scanf("%d", &userin);
            
            getchar();
            switch(userin) {
                case 1:
                    addacc(accounts,numAccptr);
                    break;
                case 2:
                    deleteacc(accounts, numAccptr);
                    break;
                case 3:
                    modifyacc(accounts,numAccptr);
                    break;
                case 4:
                    search(accounts,numAccptr);
                    break;
                case 5:
                    
                    advSearch(accounts,*numAccptr);
                    break;
                case 6:
                    changeStatus(accounts,numAccptr);
                    break;
                case 7:
                    withdraw(accounts,*numAccptr);
                    break;
                case 8:
                    deposit(accounts,*numAccptr);
                    break;
                case 9:
                    transfer(accounts,*numAccptr);
                    break;
                case 10:
                    report();
                    break;
                case 11:
                    printaccdetails(accounts,numAccptr);
                    break;
                case 12:
                    delete_multiple(accounts,numAccptr);
                    break;
                case 13:
                    saveAccounts(accounts, numAccptr);
                    break;
                case 14:
                    quit();
                    break;
            }
        }
    }
}