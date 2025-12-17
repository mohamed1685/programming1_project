#include "../headers/Banksys.h"
#include <stdio.h> 


int main() {
    Account accounts[maxAccounts];
    User users[maxUsers];
    int numAccptr,numUsersptr;
    FILE *fileptr = NULL;
    loadUsers(users,&numUsersptr);
    int loginstatus=login(users,numUsersptr);
    loadacc(accounts,&numAccptr,&fileptr);
    menu(accounts,&numAccptr,loginstatus);
        return 0;
}