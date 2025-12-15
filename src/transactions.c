#include <stdio.h>
#include "../headers/Banksys.h"
#include "../headers/transactions.h"



void report(){

    int i;
    int account_number;
    printf("Enter a bank account number: ");
    scanf("%d",&account_number);

    char file_name[20];
    sprintf(file_name,"./transactions/%d.txt",account_number);

    FILE * file_ptr = fopen(file_name,"r");
    
    if(file_ptr == NULL){
        printf("failed to open file\n");
        exit(1);
    }


    char lines[5][50];
    int count = 0;

     while (fgets(lines[count % 5], 50, file_ptr)) {
        count++;
    }

    fclose(file_ptr);

    int start = (count > 5) ? count - 5 : 0;

    for ( i = start; i < count; i++) {
        printf("%s", lines[i % 5]);
    }

}


void add_transfer_transaction(int reciver_number,int sender_number,float transfer_amount){
    
    char reciever_file_name[20] ;
    sprintf(reciever_file_name,"./transactions/%d.txt",reciver_number);
    
    FILE * file_ptr = fopen(reciever_file_name,"a");
    if(file_ptr == NULL){
        printf("failed to open file\n");
                return;
    }
    char new_line1[50];

    sprintf(new_line1,"\ntransfer_in,%f",transfer_amount);
    fprintf(file_ptr,"%s",new_line1);
    fclose(file_ptr);

    char sender_file_name[20];
    sprintf(sender_file_name,"./transactions/%d.txt",sender_number);

    file_ptr = fopen(sender_file_name,"a");

    if(file_ptr == NULL){
        printf("failed to open file\n");
                return;
    }

    char new_line2[50];

    sprintf(new_line2,"\ntransfer_out,%f",transfer_amount);
    fprintf(file_ptr,"%s",new_line2);
    fclose(file_ptr); 

}


void add_withdraw_transaction(int account_number,float withdraw_amount){
    char file_name[20];
    sprintf(file_name,"./transactions/%d.txt",account_number);

    FILE * file_ptr = fopen(file_name,"a");
    
    if(file_ptr == NULL){
        printf("failed to open file\n");
        return;
    }
    char new_line[50];

    sprintf(new_line,"\nwithdraw,%f",withdraw_amount);
    fprintf(file_ptr,"%s",new_line);
    fclose(file_ptr);

}

void add_deposit_transaction(int account_number, float deposit_amount) {
    char file_name[20];
    snprintf(file_name, sizeof(file_name), "./transactions/%d.txt", account_number);

    FILE *file_ptr = fopen(file_name, "a");
    if (!file_ptr) {
        printf("failed to open file\n");
        return;
    }

    fprintf(file_ptr, "\ndeposit,%.2f", deposit_amount);
    fclose(file_ptr);
}

void transfer(Account accounts[],int array_size){
    int  sender_number,reciever_number;
    int sender_index,reciever_index;
    float transfer_amount;


    do{
    printf("Enter account number of sender: ");
    scanf("%i",&sender_number);
    }
    while (check_account(sender_number,accounts,array_size,&sender_index) !=1);

    do{
    printf("Enter account number of reciever: ");
    scanf("%i",&reciever_number);
    }
    while (check_account(reciever_number,accounts,array_size,&reciever_index) !=1);

    int flag;
    do {
    flag =1;
    printf("Enter transfer amount: ");
    scanf("%f",&transfer_amount);    
    

    if(transfer_amount >accounts[sender_index].balance){
        printf("transfer amount larger then sender balance\n");
        flag = 0;
    }
}
    while (flag==0);

    accounts[sender_index].balance -= transfer_amount;
    accounts[reciever_index].balance += transfer_amount;
    
    add_transfer_transaction(reciever_number,sender_number,transfer_amount);

}

int check_account(int sender_number,Account accounts[],int  array_size,int * index){
    int i ;
    for(i =0;i<array_size;i++){
        if (accounts[i].account_number == sender_number){
            if(accounts[i].status == 1){
                *index = i;
                return 1;

            }
            else{
                printf("account is inactive\n");
                return 0;
            }
        }
    }
    printf("couldnt find account\n");
    return 0 ;

}

void withdraw(Account accounts[],int size){
    int account_number,account_index;
    float withdrawl_amount;
    do{
    printf("Enter account number: ");
    scanf("%i",&account_number);
    }
    while (check_account(account_number,accounts,size,&account_index) !=1);


    int flag =1;
    do {
        printf("Enter withdrawl ammount: ");
        scanf("%f",&withdrawl_amount);
        if(withdrawl_amount > accounts[account_index].remianing_daily_limit){
            printf("this transaction exceededs daily limit\n");
            flag = 0;
        }
        if(withdrawl_amount >10000.0){
            printf(" transaction can not exceed 10,000$\n");
            flag = 0;
        }
    }
    while(flag != 1);

    accounts[account_index].balance -= withdrawl_amount;
    accounts[account_index].remianing_daily_limit -= withdrawl_amount;
    printf("withdrawl successful\n");
    add_withdraw_transaction(account_number,withdrawl_amount);


}


void deposit(Account accounts[],int size){
    int account_number,account_index;
    float deposit_amount;
    do{
    printf("Enter account number: ");
    scanf("%i",&account_number);
    }
    while (check_account(account_number,accounts,size,&account_index) !=1);

        printf("Enter deposit ammount");
        scanf("%f",&deposit_amount);
        
        accounts[account_index].balance += deposit_amount;

        add_deposit_transaction(account_number,deposit_amount);
}
