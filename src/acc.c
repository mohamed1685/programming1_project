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

void addacc(Account *accounts,int *numAccptr)
{
    if(*numAccptr>=maxAccounts){
        printf("\n cant add account,Max limit reached");
        return;
    }


    printf("enter Account number: ");
    scanf("%lld",&accounts[*numAccptr].account_number);
    while (getc(stdin) != '\n');
    printf("\nenter Account name: ");
    gets(accounts[*numAccptr].name);
    printf("\nenter Account address: ");
    gets(accounts[*numAccptr].address);
    printf("\nenter Account balance: ");
    scanf("%lf",&accounts[*numAccptr].balance);
    while (getc(stdin) != '\n');
    printf("\nenter Account mobile number: ");
    gets(accounts[*numAccptr].mobile);
    printf("\nenter Account creation month(1-12): ");
    scanf("%d",&accounts[*numAccptr].date_opened.month);
    printf("\nenter Account creation year: ");
    scanf("%d",&accounts[*numAccptr].date_opened.year); 

    strcpy(accounts[*numAccptr].status,"ACTIVE");

    (*numAccptr)++;

    printf("Success, new account added with index %d",((*numAccptr)-1));
    printf("account name:%s   account number: %lld",accounts[(*numAccptr)-1].name,accounts[(*numAccptr)-1].account_number );

}