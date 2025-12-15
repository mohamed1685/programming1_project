
#include "../Banksys.h"

int check_account(int sender_number,Account accounts[],int  array_size,int * index);



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

    int flag = 1;
    do {
    printf("Enter transfer amount: ");
    scanf("%f",&transfer_amount);    
    

    if(transfer_amount >accounts[sender_index].balance){
        printf("transfer amount larger then sender balance");
        flag = 0;
    }
}
    while (flag==0);

    accounts[sender_index].balance -= transfer_amount;
    accounts[reciever_index].balance += transfer_amount;
    


}

int check_account(int sender_number,Account accounts[],int  array_size,int * index){
    int i ;
    for(i =0;i<array_size;i++){
        if (accounts[i].account_number == sender_number){
            if(strcmp(accounts[i].status,"active") == 0){
                return 1;
                *index = i;
            }
            else{
                printf("account is inactive");
                return 0;
            }
        }
    }
    printf("couldnt find account");
    return 0 ;

}

