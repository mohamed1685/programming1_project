#include "../headers/Banksys.h"
#include <stdio.h> 


int main() {
    Account accounts[maxAccounts];
    int numAccptr;
    FILE *fileptr = NULL;
    loadacc(accounts,&numAccptr,&fileptr);
    addacc(accounts,&numAccptr);
    printaccdetails(accounts,&numAccptr);
    return 0;
}