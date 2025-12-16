#include "../headers/Banksys.h"
#include <stdio.h> 


int main() {
    Account accounts[maxAccounts];
    int numAccptr;
    loadacc(accounts,&numAccptr);
    addacc(accounts,&numAccptr);
    printaccdetails(accounts,&numAccptr);
    return 0;
}