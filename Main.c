#include "headers/Banksys.h"
#include <stdio.h> 

// --- Function Prototypes ---
// These prototypes MUST be included so the compiler knows how loadacc is structured.
FILE * loadacc(Account *accounts, int *numAccptr);
// If you implement other functions, their prototypes go here too (e.g., saveAccounts).

int main() {
    // We assume maxAccounts is defined in Banksys.h
    Account accountArray[maxAccounts];
    int accountCount = 0; 
    
    // --- 1. Load Data ---
    // The account data is loaded into accountArray, and accountCount is updated.
    FILE *accountFileHandle = loadacc(accountArray, &accountCount); 
    
    // Check if the file was opened successfully
    

    // --- 2. Program Execution ---
    printf("\n--- Account Data Loaded Successfully ---\n");
    printf("Successfully loaded %d accounts into memory.\n", accountCount);
    
    // The main banking logic (menu, searches, transactions) would go here.
    
    // --- 3. Cleanup ---
    // We close the file handle that was opened by loadacc.
    if (accountFileHandle != NULL) {
        fclose(accountFileHandle); 
    }

    return 0;
}