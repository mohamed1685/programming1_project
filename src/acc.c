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
    char *delim= " ,-\n\r";
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
        accounts[count].remianing_daily_limit= 50000.00;
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
    accounts[*numAccptr].remianing_daily_limit= 50000.00;
    (*numAccptr)++;

    printf("\nSuccess, new account added with index %d\n\n",((*numAccptr)-1));
    printf("account name:%s %s   account number: %lld\n\n",accounts[(*numAccptr)-1].firstname,accounts[(*numAccptr)-1].lastname,accounts[(*numAccptr)-1].account_number );

}

void swap(Account *a, Account *b) {
    Account t = *a; *a = *b; *b = t;
}

void sortByName(Account *accounts, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(accounts[j].firstname, accounts[j + 1].firstname) > 0)
                swap(&accounts[j], &accounts[j + 1]);
        }
    }
}

void sortByBalance(Account *accounts, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (accounts[j].balance > accounts[j + 1].balance)
                swap(&accounts[j], &accounts[j + 1]);
        }
    }
}

void sortByDate(Account *accounts, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (accounts[j].date_opened.year > accounts[j + 1].date_opened.year || (accounts[j].date_opened.year == accounts[j + 1].date_opened.year && accounts[j].date_opened.month > accounts[j + 1].date_opened.month))
                swap(&accounts[j], &accounts[j + 1]);
        }
    }
}

void sortByStatus(Account *accounts, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (accounts[j].status < accounts[j + 1].status)
                swap(&accounts[j], &accounts[j + 1]);
        }
    }
}

void printaccdetails(Account *accounts, int *numAccptr) {
    int count = *numAccptr, choice;
    if (count == 0) { printf("No accounts to print.\n"); return; }

    printf("\n1.Name 2.Balance 3.Date 4.Status 5.None\nSort by: ");
    scanf("%d", &choice);

    if (choice == 1) sortByName(accounts, count);
    else if (choice == 2) sortByBalance(accounts, count);
    else if (choice == 3) sortByDate(accounts, count);
    else if (choice == 4) sortByStatus(accounts, count);

    printf("\n--- All Accounts List ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nAccount Number: %lld\n", accounts[i].account_number);
        printf("Name: %s %s\n", accounts[i].firstname, accounts[i].lastname);
        printf("Address: %s\n", accounts[i].address);
        printf("Balance: %.2lf\n", accounts[i].balance);
        printf("Mobile: %s\n", accounts[i].mobile);
        printf("Opened: %d/%d\n", accounts[i].date_opened.month, accounts[i].date_opened.year);
        printf("Status: %s\n", accounts[i].status ? "ACTIVE" : "INACTIVE");
    }
    printf("\nTotal Accounts: %d\n", count);
}
void deleteacc(Account *accounts, int *numAccptr) {
    long long target;
    int foundInd = -1;

    if (*numAccptr == 0) {
        printf("\nNo accounts available to delete.\n");
        return;
    }

    printf("Enter Account Number to delete: ");
    scanf("%lld", &target);


    for (int i = 0; i < *numAccptr; i++) {
        if (accounts[i].account_number == target) {
            foundInd = i;
            break;
        }
    }

    if (foundInd == -1) {
        printf("\nAccount not found.\n");
        return;
    }

    for (int j = foundInd; j < (*numAccptr) - 1; j++) {
        accounts[j] = accounts[j + 1];
    }
    (*numAccptr)--;

    printf("\nAccount %lld successfully deleted.\n", target);
}

void modifyacc(Account *accounts,int *numAccptr){
    int i=0,foundind=-1,choice;
    long long useracc;
    printf("enter account number");
    scanf("%lld",&useracc);
    while(i<(*numAccptr)){
        if(useracc==accounts[i].account_number){
            foundind=i;
        }
        i++;
    }
    
    if(foundind==-1){
        printf("account not found");
        return;
    }

    printf("What would you like to modify");
    printf("1- Name");
    printf("2- Mobile Number");
    printf("3- email address");
    printf("enter your choice (1-3)");
    scanf("%d",&choice);
    while(choice<1||choice>3){
        printf("invalid choice, please re-enter your choice");
        scanf("%d",&choice);
    }
    while (getchar() != '\n');

    switch (choice)
    {
    case 1:
        printf("enter first name");
        char newFirst[15];
        gets(newFirst);
        char newLast[15];
        gets(newLast);
        strcpy(accounts[foundind].firstname,newFirst);
        strcpy(accounts[foundind].lastname,newLast);
        break;
    case 2:
        printf("enter mobile number");
        char newNum[20];
        gets(newNum);
        strcpy(accounts[foundind].mobile,newNum);
        break;
    case 3:
        printf("enter email address");
        char newAdd[20];
        gets(newAdd);
        strcpy(accounts[foundind].address,newAdd);
        break;
    
    
    }

}
void changeStatus(Account *accounts,int *numAccptr){
    int i=0,foundind=-1,newStatus;
    long long useracc;
    printf("enter account number: ");
    scanf("%lld",&useracc);
    while(i<(*numAccptr)){
        if(useracc==accounts[i].account_number){
            foundind=i;
            break;
        }
        i++;
    }
    
    if(foundind==-1){
        printf("account not found");
        return;
    }

    printf("current status is %s\n", accounts[foundind].status ? "ACTIVE" : "INACTIVE");
    printf("enter new status (1 for active, 0 for inactive): ");
    scanf("%d", &newStatus);

    if(newStatus == accounts[foundind].status){
        printf("ATTENTION: you wish to change your current account status back to the same one\n");
    }
    else if(newStatus == 0 || newStatus == 1){
        accounts[foundind].status = newStatus;
        printf("status changed successfully\n");
    }
    else{
        printf("invalid status\n");
    }
}

void saveAccounts(Account *accounts, int *numAccptr) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < *numAccptr; i++) {
        fprintf(file, "%lld,%s,%s,%s,%.2lf,%s,%d,%d,%s\n",
                accounts[i].account_number,
                accounts[i].firstname,
                accounts[i].lastname,
                accounts[i].address,
                accounts[i].balance,
                accounts[i].mobile,
                accounts[i].date_opened.month,
                accounts[i].date_opened.year,
                accounts[i].status ? "active" : "inactive");
    }

    fclose(file);
    printf("All changes saved successfully to accounts.txt\n");
}