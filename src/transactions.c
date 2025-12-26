#include <stdio.h>
#include "../headers/Banksys.h"
#include "../headers/transactions.h"
#include <stdlib.h>
#include <string.h>

void report(){
    int i;
    long long account_number;
    printf(YELLOW "Enter a bank account number: " RESET);
    scanf("%lld",&account_number);

    char file_name[64];
    sprintf(file_name,"./transactions/%lld.txt",account_number);

    FILE * file_ptr = fopen(file_name,"r");
    
    if(file_ptr == NULL){
        printf(RED "Error: Failed to open file\n" RESET);
        exit(1);
    }

    char lines[5][50];
    int count = 0;

    while (fgets(lines[count % 5], 50, file_ptr)) {
        count++;
    }

    fclose(file_ptr);

    int start = (count > 5) ? count - 5 : 0;
    
    printf(BLUE "\n--- Last 5 Transactions ---\n" RESET);
    for ( i = start; i < count; i++) {
        printf(CYAN "%s" RESET, lines[i % 5]);
    }
    printf("\n");
}


void add_transfer_transaction(long long reciver_number,long long sender_number,float transfer_amount){
    
    char reciever_file_name[20] ;
    sprintf(reciever_file_name,"./transactions/%lld.txt",reciver_number);
    
    FILE * file_ptr = fopen(reciever_file_name,"a");
    if(file_ptr == NULL){
        printf(RED "Error: Failed to open file\n" RESET);
        return;
    }
    char new_line1[50];

    sprintf(new_line1,"\ntransfer_in,%f",transfer_amount);
    fprintf(file_ptr,"%s",new_line1);
    fclose(file_ptr);

    char sender_file_name[20];
    sprintf(sender_file_name,"./transactions/%lld.txt",sender_number);

    file_ptr = fopen(sender_file_name,"a");

    if(file_ptr == NULL){
        printf(RED "Error: Failed to open file\n" RESET);
        return;
    }

    char new_line2[50];

    sprintf(new_line2,"\ntransfer_out,%f",transfer_amount);
    fprintf(file_ptr,"%s",new_line2);
    fclose(file_ptr); 
}


void add_withdraw_transaction(long long account_number,float withdraw_amount){
    char file_name[64];
    sprintf(file_name,"./transactions/%lld.txt",account_number);

    FILE * file_ptr = fopen(file_name,"a");
    
    if(file_ptr == NULL){
        printf(RED "Error: Failed to open file\n" RESET);
        return;
    }
    char new_line[50];

    sprintf(new_line,"\nwithdraw,%f",withdraw_amount);
    fprintf(file_ptr,"%s",new_line);
    fclose(file_ptr);
}

void add_deposit_transaction(long long account_number, float deposit_amount) {
    char file_name[20];
    snprintf(file_name, sizeof(file_name), "./transactions/%lld.txt", account_number);

    FILE *file_ptr = fopen(file_name, "a");
    if (!file_ptr) {
        printf(RED "Error: Failed to open file\n" RESET);
        return;
    }

    fprintf(file_ptr, "\ndeposit,%.2f", deposit_amount);
    fclose(file_ptr);
}

void transfer(Account accounts[],int array_size){
    long long  sender_number,reciever_number;
    int sender_index,reciever_index;
    float transfer_amount;

    do{
        printf(YELLOW "Enter account number of sender: " RESET);
        scanf("%lld",&sender_number);
    }
    while (check_account(sender_number,accounts,array_size,&sender_index) !=1);

    do{
        printf(YELLOW "Enter account number of reciever: " RESET);
        scanf("%lld",&reciever_number);
    }
    while (check_account(reciever_number,accounts,array_size,&reciever_index) !=1);
    
    if (sender_number == reciever_number) {
        printf(RED "Error: Cannot transfer money to the same account.\n" RESET);
        return;
    }

    int flag;
    do {
        flag = 1;
        printf(YELLOW "Enter transfer amount: " RESET);
        scanf("%f",&transfer_amount);    
    

        if(transfer_amount > accounts[sender_index].balance){
            printf(RED "Error: Transfer amount larger then sender balance\n" RESET);
            flag = 0;
        }
        if (transfer_amount <= 0) {
            printf(RED "Error: Invalid amount\n" RESET);
            flag = 0;
        }
    }
    while (flag==0);

    accounts[sender_index].balance -= transfer_amount;
    accounts[reciever_index].balance += transfer_amount;
    
    printf(GREEN "Transfer successful!\n" RESET);
    add_transfer_transaction(reciever_number,sender_number,transfer_amount);
}

int check_account(long long sender_number,Account accounts[],int  array_size,int * index){
    int i ;
    for(i =0;i<array_size;i++){
        if (accounts[i].account_number == sender_number){
            if(accounts[i].status == 1){
                *index = i;
                return 1;
            }
            else{
                printf(RED "Error: Account is INACTIVE\n" RESET);
                return 0;
            }
        }
    }
    printf(RED "Error: Could not find account\n" RESET);
    return 0 ;
}

void withdraw(Account accounts[],int size){
    long long account_number;
    int account_index;
    float withdrawl_amount;
    do{
        printf(YELLOW "Enter account number: " RESET);
        scanf("%lld",&account_number);
    }
    while (check_account(account_number,accounts,size,&account_index) !=1);


    int flag =1;
    do {
        printf(YELLOW "Enter withdrawal amount: " RESET);
        scanf("%f",&withdrawl_amount);
        
        
        if(withdrawl_amount <= 0) {
            printf(RED "Error: Invalid amount\n" RESET);
            flag = 0;
            continue;
        }

        flag = dailly_limit(accounts,withdrawl_amount,account_index);

        if(withdrawl_amount > 10000.0){
            printf(RED "Error: Transaction can not exceed 10,000$\n" RESET);
            flag = 0;
        }
        
        
        if(withdrawl_amount > accounts[account_index].balance) {
             printf(RED "Error: Insufficient funds. Balance: %.2f\n" RESET, accounts[account_index].balance);
             flag = 0;
        }

    }
    while(flag != 1);

    accounts[account_index].balance -= withdrawl_amount;
    accounts[account_index].remianing_daily_limit -= withdrawl_amount;
    printf(GREEN "Withdrawal successful\n" RESET);
    add_withdraw_transaction(account_number,withdrawl_amount);
}


void deposit(Account accounts[],int size){
    long long account_number;
    int account_index;
    float deposit_amount;
    do{
        printf(YELLOW "Enter account number: " RESET);
        scanf("%lld",&account_number);
    }
    while (check_account(account_number,accounts,size,&account_index) !=1);

    do {
        printf(YELLOW "Enter deposit amount: " RESET);
        scanf("%f",&deposit_amount);
        
        if(deposit_amount <= 0) {
            printf(RED "Error: Invalid amount\n" RESET);
        }
    } while(deposit_amount <= 0);
        
    accounts[account_index].balance += deposit_amount;
    printf(GREEN "Deposit successful\n" RESET);

    add_deposit_transaction(account_number,deposit_amount);
}


int dailly_limit(Account accounts[],float withdrawl_amount,int account_index){
    if(withdrawl_amount > accounts[account_index].remianing_daily_limit){
        printf(RED "Error: This transaction exceeds daily limit\n" RESET);
        return 0 ;
    }
    else return 1;
}