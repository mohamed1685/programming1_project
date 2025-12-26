#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "Banksys.h"


void report(void);


void add_transfer_transaction(long long receiver_number,
                              long long sender_number,
                              float transfer_amount);

void add_withdraw_transaction(long long account_number,
                              float withdraw_amount);

void add_deposit_transaction(long long account_number,
                             float deposit_amount);

void transfer(Account accounts[],int array_size);

void withdraw(Account accounts[],int size);

void deposit(Account accounts[],int size); 


int check_account(long long account_number,
                  Account accounts[],
                  int array_size,
                  int *index);

int dailly_limit(Account accounts[],float withdrawl_amount,int account_index);

void report();


#endif
