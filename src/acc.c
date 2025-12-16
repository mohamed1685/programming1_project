#include "../headers/Banksys.h"

void loadacc(Account *accounts,int *numAccptr, FILE **filePtr){
    *numAccptr=0;
    char statstr[20];
    FILE *file=fopen("accounts.txt","r");
    *filePtr = file;
    if(file==NULL){
        printf("Accounts Couldnt be loaded");
        return;
    }
    printf("test");
    char line[line_length];
    char *delim= " ,-\n";
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
        strcpy(statstr,strtok(NULL,delim));
        if(strcmp(statstr,"active")==0){
            accounts[count].status=1;
        }
        else if(strcmp(statstr,"inactive")==0){
            accounts[count].status= 0;
        }
        count++;
    }
    *numAccptr=count;
    printf("Successfully Loaded %d accounts", count);
    while(i<count){
        printf("account #%d\n",i+1);
        printf("account number: %lld\n",accounts[i].account_number);
        printf("account first name: %s\n",accounts[i].firstname);
        printf("account last name: %s\n",accounts[i].lastname);
        printf("account address: %s\n",accounts[i].address);
        printf("account balance: %.2lf\n",accounts[i].balance);
        printf("account mobile number: %s\n",accounts[i].mobile);
        printf("account month opened: %d\n",accounts[i].date_opened.month);
        printf("account year opened: %d\n",accounts[i].date_opened.year);
        if(accounts[i].status){
            printf("account status: ACTIVE\n\n\n\n\n");
        }
        else if(accounts[i].status==0){
            printf("account status: INACTIVE\n\n\n\n\n");
        }
        i++;
    }
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
    printf("\nenter Account firstname: ");
    gets(accounts[*numAccptr].firstname);
    printf("\nenter Account last name: ");
    gets(accounts[*numAccptr].lastname);
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

    accounts[*numAccptr].status=1;

    (*numAccptr)++;

    printf("\nSuccess, new account added with index %d\n\n",((*numAccptr)-1));
    printf("account name:%s %s   account number: %lld\n\n",accounts[(*numAccptr)-1].firstname,accounts[(*numAccptr)-1].lastname,accounts[(*numAccptr)-1].account_number );

}

void printaccdetails(Account *accounts,int *numAccptr){
    int i=0;
    int count= *numAccptr;
    printf("Successfully Loaded %d accounts", count);
    while(i<count){
        printf("account #%d\n",i+1);
        printf("account number: %lld\n",accounts[i].account_number);
        printf("account first name: %s\n",accounts[i].firstname);
        printf("account last name: %s\n",accounts[i].lastname);
        printf("account address: %s\n",accounts[i].address);
        printf("account balance: %.2lf\n",accounts[i].balance);
        printf("account mobile number: %s\n",accounts[i].mobile);
        printf("account month opened: %d\n",accounts[i].date_opened.month);
        printf("account year opened: %d\n",accounts[i].date_opened.year);
        if(accounts[i].status){
            printf("account status: ACTIVE\n\n\n\n\n");
        }
        else if(accounts[i].status==0){
            printf("account status: INACTIVE\n\n\n\n\n");
        }
        i++;

}
}