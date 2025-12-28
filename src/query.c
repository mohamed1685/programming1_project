#include "../headers/Banksys.h"
#include <string.h>
#include "../headers/query.h"
#include "../headers/transactions.h"





void advSearch(Account accounts[],int size){
    int i;
    int flag = 0;
    char keyword[25];
    printf(YELLOW"enter a keyword: "RESET);
    gets(keyword);
    printf("Search results: \n\n");
    for (i =0;i<size;i++){
        char full_name[250];
        sprintf(full_name,"%s %s",accounts[i].firstname,accounts[i].lastname);
        if(strstr(accounts[i].address,keyword) != NULL||strstr(full_name,keyword) != NULL){
            flag = 1;
            printacc(accounts,i);
        }
    }
    if (flag ==0){
        printf(RED"no search results found"RESET);
        return;
    }
}

void search(Account accounts[],int *numAccptr){
    int i=0,foundind=-1;
    long long useracc;
    useracc = get_account_number(YELLOW "Enter account number: " RESET);
    while(i<(*numAccptr)){
        if(useracc==accounts[i].account_number){
            foundind=i;
        }
        i++;
    }
    
    if(foundind==-1){
        printf(RED"account not found"RESET);
        return;
    }

    printacc(accounts,foundind);
}



void printacc(Account accounts[],int i){

        printf("account number: %lld\n",accounts[i].account_number);
        printf("account first name: %s\n",accounts[i].firstname);
        printf("account last name: %s\n",accounts[i].lastname);
        printf("account address: %s\n",accounts[i].address);
        printf("account balance: %.2lf\n",accounts[i].balance);
        printf("account mobile number: %s\n",accounts[i].mobile);
        printf("account month opened: %d\n",accounts[i].date_opened.month);
        printf("account year opened: %d\n",accounts[i].date_opened.year);
        if(accounts[i].status){
            printf("account status: " GREEN"ACTIVE\n\n"RESET);
        }
        else if(accounts[i].status==0){
            printf("account status: "RED"INACTIVE\n\n"RESET);
        }



}