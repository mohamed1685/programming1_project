#ifndef Banksys
#define Banksys

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define RESET   "\033[0m"     
#define RED     "\033[1;31m"  
#define GREEN   "\033[1;32m"  
#define YELLOW  "\033[1;33m"  
#define BLUE    "\033[1;34m"  
#define PURPLE  "\033[1;35m"  
#define CYAN    "\033[1;36m"  
#define WHITE   "\033[1;37m"

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
void menu(Account *accounts,int *numAccptr,int loginstatus);
void deleteacc(Account *accounts, int *numAccptr) ;
void modifyacc(Account *accounts,int *numAccptr);
void changeStatus(Account *accounts,int *numAccptr);
void saveAccounts(Account *accounts, int *numAccptr);
void printaccdetails(Account *accounts, int *numAccptr);
void sortByStatus(Account *accounts, int n);
void sortByDate(Account *accounts, int n);
void sortByBalance(Account *accounts, int n);
void sortByName(Account *accounts, int n);
int digitVal(char s[]);
int mailVal(char s[]);
void quit();


#endif
