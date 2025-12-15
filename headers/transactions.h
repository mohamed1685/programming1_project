#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "Banksys.h"

//Show last 5 transactions for an account 
void report(void);

// Transaction record helpers 
void add_transfer_transaction(int receiver_number,
                              int sender_number,
                              float transfer_amount);

void add_withdraw_transaction(int account_number,
                              float withdraw_amount);

void add_deposit_transaction(int account_number,
                             float deposit_amount);




int check_account(int account_number,
                  Account accounts[],
                  int array_size,
                  int *index);

#endif 
