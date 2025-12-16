#include "headers/Banksys.h"

FILE * loadacc(Account *accounts,int *numAccptr){

    *numAccptr=0;
    char statstr[10];
    FILE *file=fopen("accounts.txt","r");
    if(file==NULL){
        printf("Accounts Couldnt be loaded");
        return NULL;
    }

    char line[line_length];
    char *delim= ",-\n";
    int count=0,i=0;

    while(fgets(line,sizeof(line),file)!=NULL&&count<maxAccounts){
        
        accounts[count].account_number=atoll(strtok(line,delim));
        strcpy(accounts[count].firstname,strtok(NULL,delim));
        strcpy(accounts[count].lastname,strtok(NULL,delim));
        strcpy(accounts[count].address,strtok(NULL,delim));
        accounts[count].balance=atof(strtok(NULL,delim));
        strcpy(accounts[count].mobile,strtok(NULL,delim));
        accounts[count].date_opened.month=atoi(strtok(NULL,delim));
        accounts[count].date_opened.year=atoi(strtok(NULL,delim));
        strtok(NULL,delim);
        strcpy(statstr,strtok(NULL,delim));
        if(strcmp(statstr," active")==0){
            accounts[count].status=1;
        }
        else if(strcmp(statstr," inactive")==0){
            accounts[count].status=0;
        }
        count++;
    }

    *numAccptr=count;
    printf("Successfully Loaded %d accounts", count);
    while(i<count){
        printf("account number: %lld\n",accounts[i].account_number);
        printf("account first name: %s\n",accounts[i].firstname);
        printf("account last name: %s\n",accounts[i].lastname);
        printf("account address: %s\n",accounts[i].address);
        printf("account balance: %lf\n",accounts[i].balance);
        printf("account mobile number: %s\n",accounts[i].mobile);
        printf("account month opened: %d\n",accounts[i].date_opened.month);
        printf("account year opened: %d\n",accounts[i].date_opened.year);
        if(accounts[i].status){
            printf("account status: ACTIVE");
        }
        else if(accounts[i].status==0){
            printf("account status: INACTIVE");
        }
        i++;
    }
    return file;

}