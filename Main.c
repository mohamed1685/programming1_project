#include "Banksys.h"

// Note: Assumes essential headers and function prototypes are included via "Banksys.h"

int main() {
    
    // --- 1. DATA DECLARATION ---
    
    User userArray[maxUsers]; 
    int userCount = 0; 
    
    Account accountArray[maxAccounts]; 
    int accountCount = 0;
    
    // File Handle (We will NOT close this in this test version)
    FILE *accountFileHandle = NULL;
    
    // --- 2. LOAD DATA ---
    
    loadUsers(userArray, &userCount); 
    
    if (userCount == 0) {
        printf("FATAL: System cannot proceed without user data. Exiting.\n");
        return 1;
    }

    accountFileHandle = loadacc(accountArray, &accountCount); 
    
    if (accountCount == 0 || accountFileHandle == NULL) {
        printf("FATAL: System cannot proceed without account data. Exiting.\n");
        // We still check and close the file if an error occurred during loading
        if (accountFileHandle != NULL) {
            fclose(accountFileHandle); 
        }
        return 1;
    }

    // 🛑 VERIFICATION: Print loaded accounts list
    printf("\n--- VERIFICATION: Loaded Accounts List (%d total) ---\n", accountCount);
    for (int i = 0; i < accountCount; i++) {
        printf("Index %d: Account Number: %lld, Name: %s\n", 
               i, 
               accountArray[i].account_number, 
               accountArray[i].name);
    }
    printf("--------------------------------------------------\n");
    
    // --- 3. LOGIN LOOP ---
    
    int loggedInIndex = -1; 
    
    printf("\nWelcome to the Bank System. Please log in.\n");
    
    while (loggedInIndex == -1) { 
        loggedInIndex = login(userArray, userCount);
    }
    
    printf("Successfully authenticated. User index: %d\n", loggedInIndex);
    
    // --- 4. ADD ACCOUNT (TEST) ---
    // This is the core test: it updates the array and accountCount in memory.
    printf("\n*** TESTING addAccount FUNCTION ***\n");
    printf("Account count before: %d\n", accountCount);
    
    addacc(accountArray, &accountCount);
    
    printf("*** TESTING COMPLETE. Current account count: %d ***\n", accountCount);
    
    // --- 5. CLEANUP AND EXIT (MODIFIED) ---
    
    // NOTE: We are intentionally SKIPPING the saveAccounts call and the fclose()
    // to allow you to test the addAccount function without needing the save logic yet.
    
    printf("\nSession ended. System shutdown complete (File handle remains open in memory).\n");
    
    return 0; 
}