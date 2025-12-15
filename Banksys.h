#ifndef Banksys
#define Banksys

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define loginSuccess 1
#define loginFail 0
#define line_length 256
#define maxAccounts 100
#define maxUsers 20
#define Max_input_length 50

typedef struct {
    char username[Max_input_length];
    char password[Max_input_length];
} User;

void loadUsers(User *users, int *numUsersPtr);
int login(User *users, int numUsers);





typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    int   account_number;              
    char  name[100];               
    char  address[100];            
    float balance;                     
    char  mobile[20];            
    Date  date_opened;         
    char  status[20]   ;        
} Account;



#endif
