#include "../headers/Banksys.h"
#include "../headers/delete_multiple.h"

/*delete_multiple has 2 options delete_by_date and delete_by_status
 each one  is implemented as a function and each one is called inside the delete_multiple function
 depending on what the user selects  */



 //prompts user for a date and deletes all accounts created on that date
void delete_by_date(Account accounts[],int* num_accounts_ptr){
int year,month,i;
int flag = 0;
int counter = 0;
int valid = 1;


do{
printf("enter year: ");
scanf("%i",&year);
while(getchar() != '\n');
}
while(year<0);

do{
printf("enter month: ");

if(scanf("%i",&month)!=1 || month<0 ||month >12){
    printf( RED " invalid " RESET);
    while (getchar() != '\n');
    valid  = 0;
}
else{
    valid = 1;
}

}
while(!valid);

for (i = 0; i<*num_accounts_ptr;i++){
    if( accounts[i].date_opened.month ==month &&accounts[i].date_opened.year==year){
        delete_account(accounts,*num_accounts_ptr,accounts[i].account_number);
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
*num_accounts_ptr -= counter;
}


//deletes all inactive accounts for more than 90 days with balance = 0

void delete_by_status(Account accounts[],int* num_accounts_ptr){
    Date current_date;
    int i,flag=0;
    int counter = 0;
    printf(YELLOW"enter current year: ");
    scanf("%i",&current_date.year);
    printf("enter current month: "RESET);
    scanf("%i",&current_date.month);

    
    
    for (i = 0; i<*num_accounts_ptr;i++){
        if(accounts[i].status == 0 && accounts[i].balance == 0&&date_check(current_date,accounts[i].date_opened)){
            delete_account(accounts,*num_accounts_ptr,accounts[i].account_number);
            flag = 1;
            counter++;
            i--;
        }
    *num_accounts_ptr -= counter; 

}
if (flag ==0){
    printf(RED"no inactive accounts for more than 90 days with balance = 0  \n"RESET);
}
else{
    printf(GREEN"successfully deleted %i accounts \n "RESET,counter);
}

}

//helper function to delete an account given an account number
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


    printf(GREEN"\nAccount %lld successfully deleted.\n"RESET, target);
}

void delete_multiple(Account accounts[], int * num_accounts_ptr){
    int option ;

    do{

        printf(YELLOW"enter 1 for delete by date or 2 for delete by status: "RESET);
        scanf("%i",&option);

    }
    while(option != 1 && option !=2);
    if(option == 1){
        delete_by_date(accounts,num_accounts_ptr);
    }
    else{
        delete_by_status(accounts,num_accounts_ptr);
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
