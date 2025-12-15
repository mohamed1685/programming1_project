#include "Banksys.h"

// Note: Assumes essential headers and function prototypes are included via "Banksys.h"

int main() {
    
    // --- 1. DATA DECLARATION ---
    
    // User Data (File closed by loadUsers)
    User userArray[maxUsers]; 
    int userCount = 0; 
    
    // Account Data (File must remain open, handle stored here)
    Account accountArray[maxAccounts]; 
    int accountCount = 0;
    
    // File Handle (To store the pointer for the open accounts file)
    FILE *accountFileHandle = NULL;
    
    // --- 2. LOAD DATA ---
    
    // loadUsers is VOID and closes its own file.
    loadUsers(userArray, &userCount); 
    
    if (userCount == 0) {
        printf("FATAL: System cannot proceed without user data. Exiting.\n");
        return 1;
    }

    // loadacc returns the OPEN FILE HANDLE, which we must store.
    accountFileHandle = loadacc(accountArray, &accountCount); 
    
    if (accountCount == 0 || accountFileHandle == NULL) {
        printf("FATAL: System cannot proceed without account data. Exiting.\n");
        
        // Cleanup the accounts file handle if it was opened
        if (accountFileHandle != NULL) {
            fclose(accountFileHandle); 
        }
        return 1;
    }

    // 🛑 VERIFICATION: Print loaded accounts list
    printf("\n--- VERIFICATION: Loaded Accounts List (%d total) ---\n", accountCount);
    for (int i = 0; i < accountCount; i++) {
        // FIX: Using %ld because account_number is now a long integer
        printf("Index %d: Account Number: %lld, Name: %s\n", 
               i, 
               accountArray[i].account_number, // This field is now long
               accountArray[i].name);
    }
    printf("--------------------------------------------------\n");
    
    // --- 3. LOGIN LOOP ---
    
    int loggedInIndex = -1; // -1 means failure/not logged in
    
    printf("\nWelcome to the Bank System. Please log in.\n");
    
    // Loop until successful login
    while (loggedInIndex == -1) { 
        // Assuming login() returns the index of the logged-in user (0 to userCount-1)
        loggedInIndex = login(userArray, userCount);
    }
    
    printf("Successfully authenticated. User index: %d\n", loggedInIndex);
    
    // --- 4. CLEANUP AND EXIT ---
    
    // 🛑 CRITICAL: The required single fclose() for the accounts file.
    if (accountFileHandle != NULL) {
        fclose(accountFileHandle); 
    }
    
    printf("Session ended. System shutdown complete.\n");
    
    return 0; 
}