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
    printf(RED"no account created on that date \n"RESET);
}
else{
    printf(GREEN"successfully deleted %i accounts \n "RESET,counter);
}
}



void delete_by_status(Account accounts[],int size){
    Date current_date;
    int i,flag=0;

    printf(YELLOW"enter current year: ");
    scanf("%i",&current_date.year);
    printf("enter current month: "RESET);
    scanf("%i",&current_date.month);

    
    
    for (i = 0; i<size;i++){
        if(accounts[i].status == 0 && accounts[i].balance == 0&&date_check(current_date,accounts[i].date_opened)){
            delete_account(accounts,size,accounts[i].account_number);
            flag = 1;
        }
}
if (flag ==0){
    printf(RED"no inactive accounts for more than 90 days with balance = 0  \n"RESET);
}

}


void delete_account(Account accounts[], int size,long long target) {

    int foundInd = -1;

    if (size == 0) {
        printf(RED"\nNo accounts available to delete.\n"RESET);
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

    printf(GREEN"\nAccount %lld successfully deleted.\n"RESET, target);
}

void delete_multiple(Account accounts[], int size){
    int option ;
    int flag = 1;
    do{
        if (flag == 0){
            printf(RED"invalid option \n"RESET);
        }
        printf(YELLOW"enter 1 for delete by date or 2 for delete by status"RESET);
        scanf("%i",&option);
        if (option !=1 && option != 2){
            flag = 0;
        }
        else{
            flag = 1;
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

int date_check(Date current_date,Date past_date){
    int current_date_in_months = current_date.month +(current_date.year)*12;
    int past_date_in_months = past_date.month +(past_date.year)*12;
    if((current_date_in_months - past_date_in_months) >3){
        return 1;
    }
    else {
        return 0;
    }


}
