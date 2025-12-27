#include "Banksys.h"

#ifndef DELETE_MULTIPLE
#define DELETE_MULTIPLE


void delete_by_date(Account accounts[],int *num_account_ptr);


void delete_by_status(Account accounts[],int  *num_account_ptr);

void delete_account(Account accounts[], int size,long long target);

void delete_multiple(Account accounts[], int *num_account_ptr);

int date_check(Date current_date,Date past_date);



#endif