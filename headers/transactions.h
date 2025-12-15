#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H


void report(void);


void add_transfer_transaction(int receiver_number,int sender_number, float transfer_amount);


void add_withdraw_transaction(int account_number, float withdraw_amount);


void add_deposit_transaction(int account_number,float deposit_amount);

#endif 
