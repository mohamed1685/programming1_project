#include "Banksys.h"
// Note: <stdio.h>, <stdlib.h>, <string.h> are included via "Banksys.h"

int main() {
    
    // Memory Allocation and Count Variables 
    User userArray[maxUsers]; 
    int userCount = 0; 
    
    // Call loadUsers()
    loadUsers(userArray, &userCount);
    
    // Check for Loading Failure (loadUsers prints the error message)
    if (userCount == 0) {
        // KEEP: Essential message to tell the user why the program is exiting
        printf("System cannot proceed without user data. Exiting.\n");
        return 1;
    }
    
    // Loop Login Attempt
    int loginStatus = loginFail;
    
    while (loginStatus != loginSuccess) {
        
        // login() handles its own prompts and failure messages
        loginStatus = login(userArray, userCount);
        
        // No extra printf needed here; login() already printed "Login failed..."
    }
    
    // KEEP: Final success message
    printf("Successfully authenticated. Proceeding to Bank System Menu...\n");
    
    return 0; 
}