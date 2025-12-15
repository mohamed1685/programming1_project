#include "../Banksys.h"

FILE * loadacc(Account *accounts,int *numAccptr){

    *numAccptr=0;

    FILE *file=fopen("accounts.txt","r");
    if(file==NULL){
        printf("Accounts Couldnt be loaded");
        return NULL;
    }

    char line[line_length];
    char *delim= ",-\n";
    int count=0;

    while(fgets(line,sizeof(line),file)!=NULL&&count<maxAccounts){
        
        accounts[count].account_number=atoll(strtok(line,delim));
        strcpy(accounts[count].name,strtok(NULL,delim));
        strcpy(accounts[count].address,strtok(NULL,delim));
        accounts[count].balance=atof(strtok(NULL,delim));
        strcpy(accounts[count].mobile,strtok(NULL,delim));
        accounts[count].date_opened.month=atoi(strtok(NULL,delim));
        accounts[count].date_opened.year=atoi(strtok(NULL,delim));
        
        count++;
    }

    *numAccptr=count;
    printf("Successfully Loaded %d accounts", count);
    return file;

}