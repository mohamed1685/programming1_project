#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/Banksys.h"

int digitVal(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] < '0' || s[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

int mailVal(char s[]) {
    int i = 0;
    int atInd = -1;
    int dotInd = -1;

    while (s[i] != '\0') {
        if (s[i] == '@') {
            atInd = i; 
        }
        else if (s[i] == '.') {
            dotInd = i; 
        }
        i++;
    }

    if (atInd != -1 && dotInd != -1 && atInd < dotInd) {
        return 1;
    }
    return 0;
}

void loadacc(Account *accounts,int *numAccptr, FILE **filePtr){
    *numAccptr=0;
    char statstr[20];
    FILE *file=fopen("accounts.txt","r");
    *filePtr = file;
    if(file==NULL){
        printf(RED "Accounts Couldnt be loaded" RESET);
        return;
    }
    
    char line[line_length];
    char *delim= " ,-\n\r";
    int count=0;

    while(fgets(line,sizeof(line),file)!=NULL && count<maxAccounts){
        
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
}

void addacc(Account *accounts, int *numAccptr) {
    char input[100];
    int valid = 0;

    if (*numAccptr >= maxAccounts) {
        printf(RED "\nError: Cannot add account, Max limit reached\n" RESET);
        return;
    }

    do {
        printf(YELLOW "Enter Account number (10 digits): " RESET);
        scanf("%s", input);
        if (strlen(input) == 10 && digitVal(input)) {
            accounts[*numAccptr].account_number = atoll(input);
            valid = 1;
        } else {
            printf(RED "Error: Account number must be exactly 10 digits.\n" RESET);
            valid = 0;
        }
    } while (!valid);
    
    
    int isDuplicate = 0;
    for(int j = 0; j < *numAccptr; j++) {
        if(accounts[j].account_number == accounts[*numAccptr].account_number) {
            isDuplicate = 1;
            break;
        }
    }
    if(isDuplicate) {
        printf(RED "Error: This account number already exists in the system.\n" RESET);
        return; 
    }

    while (getchar() != '\n'); 

    printf(YELLOW "\nEnter Account firstname: " RESET);
    gets(accounts[*numAccptr].firstname);
    
    printf(YELLOW "\nEnter Account last name: " RESET);
    gets(accounts[*numAccptr].lastname);

    do {
        printf(YELLOW "\nEnter Email Address: " RESET);
        gets(accounts[*numAccptr].address);
        if (mailVal(accounts[*numAccptr].address)) {
            valid = 1;
        } else {
            printf(RED "Error: Invalid email format. Must contain '@' and '.'\n" RESET);
            valid = 0;
        }
    } while (!valid);

    do {
        printf(YELLOW "\nEnter Account balance: " RESET);
        if (scanf("%lf", &accounts[*numAccptr].balance) == 1 && accounts[*numAccptr].balance >= 0) {
            valid = 1;
        } else {
            printf(RED "Error: Invalid balance. Please enter a positive number.\n" RESET);
            while (getchar() != '\n'); 
            valid = 0;
        }
    } while (!valid);

    while (getchar() != '\n'); 

    do {
        printf(YELLOW "\nEnter Account mobile number: " RESET);
        gets(accounts[*numAccptr].mobile);
        if (digitVal(accounts[*numAccptr].mobile) && strlen(accounts[*numAccptr].mobile) > 0) {
            valid = 1;
        } else {
            printf(RED "Error: Mobile number must contain digits only.\n" RESET);
            valid = 0;
        }
    } while (!valid);

    do {
        printf(YELLOW "\nEnter Account creation month (1-12): " RESET);
        if (scanf("%d", &accounts[*numAccptr].date_opened.month) == 1 && 
            accounts[*numAccptr].date_opened.month >= 1 && 
            accounts[*numAccptr].date_opened.month <= 12) {
            valid = 1;
        } else {
            printf(RED "Error: Invalid month. Enter 1-12.\n" RESET);
            while (getchar() != '\n');
            valid = 0;
        }
    } while (!valid);

    do {
        printf(YELLOW "\nEnter Account creation year: " RESET);
        if (scanf("%d", &accounts[*numAccptr].date_opened.year) == 1 && accounts[*numAccptr].date_opened.year > 1900) {
            valid = 1;
        } else {
            printf(RED "Error: Invalid year.\n" RESET);
            while (getchar() != '\n');
            valid = 0;
        }
    } while (!valid);

    accounts[*numAccptr].status = 1;
    accounts[*numAccptr].remianing_daily_limit = 50000.00;
    (*numAccptr)++;

    printf(GREEN "\nSuccess, new account added with index %d\n" RESET, ((*numAccptr) - 1));
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
    if (count == 0) { 
        printf(RED "No accounts to print.\n" RESET); 
        return; 
    }
    
    printf(BLUE "\n--- Sort Options ---\n" RESET);
    printf(CYAN "1. Name\n2. Balance\n3. Date\n4. Status\n5. None\n" RESET);
    printf(YELLOW "Sort by: " RESET);
    scanf("%d", &choice);

    if (choice == 1) sortByName(accounts, count);
    else if (choice == 2) sortByBalance(accounts, count);
    else if (choice == 3) sortByDate(accounts, count);
    else if (choice == 4) sortByStatus(accounts, count);

    printf(BLUE "\n--- All Accounts List ---\n" RESET);
    for (int i = 0; i < count; i++) {
        printf(BLUE "\n------------------------------\n" RESET);
        printf(CYAN "Account Number: " RESET PURPLE "%lld\n" RESET, accounts[i].account_number);
        printf(CYAN "Name:           " RESET "%s %s\n", accounts[i].firstname, accounts[i].lastname);
        printf(CYAN "Address:        " RESET "%s\n", accounts[i].address);
        printf(CYAN "Balance:        " RESET YELLOW "%.2lf\n" RESET, accounts[i].balance);
        printf(CYAN "Mobile:         " RESET "%s\n", accounts[i].mobile);
        printf(CYAN "Opened:         " RESET "%d/%d\n", accounts[i].date_opened.month, accounts[i].date_opened.year);
        
        if (accounts[i].status) {
            printf(CYAN "Status:         " RESET GREEN "ACTIVE" RESET "\n");
        } else {
            printf(CYAN "Status:         " RESET RED "INACTIVE" RESET "\n");
        }
    }
    printf(BLUE "------------------------------\n" RESET);
    printf(BLUE "Total Accounts: %d\n" RESET, count);
}

void deleteacc(Account *accounts, int *numAccptr) {
    long long target;
    int foundInd = -1;
    if (*numAccptr == 0) {
        printf(RED "\nNo accounts available to delete.\n" RESET);
        return;
    }
    printf(YELLOW "Enter Account Number to delete: " RESET);
    scanf("%lld", &target);
    for (int i = 0; i < *numAccptr; i++) {
        if (accounts[i].account_number == target) {
            foundInd = i;
            break;
        }
    }
    if (foundInd == -1) {
        printf(RED "\nAccount not found.\n" RESET);
        return;
    }
    for (int j = foundInd; j < (*numAccptr) - 1; j++) {
        accounts[j] = accounts[j + 1];
    }
    (*numAccptr)--;
    printf(GREEN "\nAccount %lld successfully deleted.\n" RESET, target);
}

void modifyacc(Account *accounts, int *numAccptr) {
    int i = 0, foundind = -1, choice, valid = 0;
    long long useracc;
    char userin[100]; 
    
    printf(YELLOW "Enter account number to modify: " RESET);
    scanf("%lld", &useracc);
    while (i < (*numAccptr)) {
        if (useracc == accounts[i].account_number) {
            foundind = i;
            break;
        }
        i++;
    }
    if (foundind == -1) {
        printf(RED "Error: Account not found.\n" RESET);
        return;
    }
    
    printf(YELLOW "What would you like to modify?\n" RESET);
    printf(CYAN "1- Name\n" RESET);
    printf(CYAN "2- Mobile Number\n" RESET);
    printf(CYAN "3- Email Address\n" RESET);
    printf(YELLOW "Enter your choice (1-3): " RESET);
    scanf("%d", &choice);
    
    while (choice < 1 || choice > 3) {
        printf(RED "Error: Invalid choice, please re-enter (1-3): " RESET);
        scanf("%d", &choice);
    }
    while (getchar() != '\n');
    
    switch (choice) {
    case 1:
        printf(YELLOW "Enter first name: " RESET);
        gets(accounts[foundind].firstname);
        printf(YELLOW "Enter last name: " RESET);
        gets(accounts[foundind].lastname);
        printf(GREEN "Name updated successfully.\n" RESET);
        break;
    case 2:
        do {
            printf(YELLOW "Enter new mobile number: " RESET);
            gets(userin); 
            if (digitVal(userin) && strlen(userin) > 0) {
                strcpy(accounts[foundind].mobile, userin);
                valid = 1;
            } else {
                printf(RED "Error: Mobile number must contain digits only.\n" RESET);
                valid = 0;
            }
        } while (!valid);
        printf(GREEN "Mobile number updated successfully.\n" RESET);
        break;
    case 3:
        do {
            printf(YELLOW "Enter new email address: " RESET);
            gets(userin); 
            if (mailVal(userin)) {
                strcpy(accounts[foundind].address, userin);
                valid = 1;
            } else {
                printf(RED "Error: Invalid email format. Must contain '@' and '.'\n" RESET);
                valid = 0;
            }
        } while (!valid);
        printf(GREEN "Email address updated successfully.\n" RESET);
        break;
    }
}

void changeStatus(Account *accounts,int *numAccptr){
    int i=0,foundind=-1,newStatus;
    long long useracc;
    
    printf(YELLOW "enter account number: " RESET);
    scanf("%lld",&useracc);
    while(i<(*numAccptr)){
        if(useracc==accounts[i].account_number){
            foundind=i;
            break;
        }
        i++;
    }
    
    if(foundind==-1){
        printf(RED "account not found" RESET);
        return;
    }

    printf("current status is %s\n", accounts[foundind].status ? GREEN "ACTIVE" RESET : RED "INACTIVE" RESET);
    printf(YELLOW "enter new status (1 for active, 0 for inactive): " RESET);
    scanf("%d", &newStatus);

    if(newStatus == accounts[foundind].status){
        printf(YELLOW "ATTENTION: you wish to change your current account status back to the same one\n" RESET);
    }
    else if(newStatus == 0 || newStatus == 1){
        accounts[foundind].status = newStatus;
        printf(GREEN "status changed successfully\n" RESET);
    }
    else{
        printf(RED "invalid status\n" RESET);
    }
}

void saveAccounts(Account *accounts, int *numAccptr) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf(RED "Error: Could not open file for saving.\n" RESET);
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
    printf(GREEN "All changes saved successfully to accounts.txt\n" RESET);
}

void quit(){
        printf(GREEN "Succesfully exited system, Goodbye\n" RESET);

}