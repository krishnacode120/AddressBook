/* main.c - Address Book Application
-------------------------------------------------------
description:
   This program allows users to create, search, edit, delete, and list contacts
   in an address book. Contacts are saved to a file upon exiting the application.
   The program uses functions defined in contact.h for contact management.

sample input:
   User selects options from the menu to manage contacts.
sample output:
   Displays menu options and results of contact operations.

author: [krishnamoorthy T]
date: [2025-10-23]
*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook; 
    initialize(&addressBook); // Initialize the address book
    // Main loop
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
