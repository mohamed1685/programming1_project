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







typedef struct {
    int year;
    int month;
} Date;

typedef struct {
    long long  account_number;              
    char  firstname[100];  
    char  lastname[100];             
    char  address[100];            
    double balance;                     
    char  mobile[20];            
    Date  date_opened;         
    int status;  
    float remianing_daily_limit;     
} Account;

void loadUsers(User *users, int *numUsersPtr);
int login(User *users, int numUsers);
void loadacc(Account *accounts,int *numAccptr, FILE **filePtr);
void addacc(Account *accounts,int *numAccptr);
void printaccdetails(Account *accounts,int *numAccptr);

#endif
