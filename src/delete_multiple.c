#include "../headers/Banksys.h"


void delete_by_date(Account accounts[],int size){
int year,month,i;
int flag = 0;
int counter = 0;
printf("enter year: ");
scanf("%i",&year);
printf("enter month: ");
scanf("%i",&month);

for (i = 0; i<size;i++){
    if( accounts[i].date_opened.month ==month &&accounts[i].date_opened.year==year){
        delete_account(accounts,size,accounts[i].account_number);
        flag = 1;
        counter++;
    }
}
if (flag ==0){
    printf("no account created on that date \n");
}
else{
    printf("successfully deleted %i accounts \n ",counter);
}
}



void delete_by_status(Account accounts[],int size){
    
    int i,flag=0;
    
    
    for (i = 0; i<size;i++){
        if(accounts[i].status == 0 && accounts[i].balance == 0&&1){
            delete_account(accounts,size,accounts[i].account_number);
            flag = 1;
        }
}
if (flag ==0){
    printf("no inactive accounts for more than 90 days with balance = 0  \n");
}

}


void delete_account(Account accounts[], int size,long long target) {

    int foundInd = -1;

    if (size == 0) {
        printf("\nNo accounts available to delete.\n");
        return;
    }


    for (int i = 0; i < size; i++) {
        if (accounts[i].account_number == target) {
            foundInd = i;
            break;
        }
    }



    for (int j = foundInd; j < (size) - 1; j++) {
        accounts[j] = accounts[j + 1];
    }
    size--;

    printf("\nAccount %lld successfully deleted.\n", target);
}

void delete_multiple(Account accounts[], int size){
    int option ;
    int flag = 1;
    do{
        if (flag == 0){
            printf("invalid option \n");
        }
        printf("enter 1 for delete by date or 2 for delete by status");
        scanf("%i",&option);
        if (option !=1 && option != 2){
            flag = 0;
        }
    }
    while(flag ==0);
    if(option == 1){
        delete_by_date(accounts,size);
    }
    else{
        delete_by_status(accounts,size);
    }

}

