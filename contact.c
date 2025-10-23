/*This file implements functions for managing contacts in an address book,
  including creating, searching, editing, deleting, and listing contacts.
  It also includes validation functions for phone numbers and email addresses.
  The contacts are saved to and loaded from a file to ensure data persistence.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

#define MAX_MATCHES 100


// Function Implementations
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook); 
}

// List contacts with sorting options
void listContacts(AddressBook *addressBook) {
    printf("Select sort criteria:\n");
    printf("1. Sort by name\n");
    printf("2. Sort by phone\n");
    printf("3. Sort by email\n");
    printf("Enter your choice: ");
    int sortChoice;
    scanf("%d", &sortChoice);
    getchar();
    // Simple bubble sort based on choice
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            int cmp = 0;
            if (sortChoice == 1) {
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
            } else if (sortChoice == 2) {
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
            } else if (sortChoice == 3) {
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            if (cmp > 0) {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    
    if (addressBook->contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("\n------ CONTACT LIST ------\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%d. %s | %s | %s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("--------------------------\n");
}

// Create a new contact
void createContact(AddressBook *addressBook) {
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("❌ Address book is full!\n");
        return;
    }

    char name[50], phone[20], email[50];
    int valid;

    printf("Enter name: ");
    scanf(" %[^\n]", name);
    getchar();

    // Phone validation
    valid = 0;
    do {
        printf("Enter phone number (10 digits): ");
        scanf(" %[^\n]", phone);
        getchar();

        if (!isValidPhone(phone)) {
            printf("❌ Invalid phone number!\n");
            continue;
        }

        if (isDuplicatePhone(addressBook, phone, -1)) {
            printf("⚠️ Duplicate phone number!\n");
            continue;
        }
        valid = 1;
    } while (!valid);

    // Email validation
    valid = 0;
    do {
        printf("Enter email ID: ");
        scanf(" %[^\n]", email);
        getchar();

        if (!isValidEmail(email)) {
            printf("❌ Invalid email!\n");
            continue;
        }

        if (isDuplicateEmail(addressBook, email, -1)) {
            printf("⚠️ Duplicate email!\n");
            continue;
        }
        valid = 1;
    } while (!valid);

    // Save contact
    int index = addressBook->contactCount;
    strcpy(addressBook->contacts[index].name, name);
    strcpy(addressBook->contacts[index].phone, phone);
    strcpy(addressBook->contacts[index].email, email);
    addressBook->contactCount++;

    saveContactsToFile(addressBook);
    printf("✅ Contact added successfully!\n");
}

// Search for a contact
void searchContact(AddressBook *addressBook) {
    int choice;
    char value[50];
    int matches[MAX_MATCHES], matchCount;

    printf("Search by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    printf("Enter value: ");
    fgets(value, sizeof(value), stdin);
    value[strcspn(value, "\n")] = 0;

    int found = findContact(addressBook, value, choice, matches, &matchCount);

    if (found == -1) {
        printf("❌ Contact not found.\n");
        return;
    }

    if (matchCount == 1) {
        int idx = matches[0];
        printf("Contact found: %s | %s | %s\n",
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    } else {
        printf("Multiple contacts found:\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }
    }
}
// Edit an existing contact
void editContact(AddressBook *addressBook) {
    int choice;
    char value[50], newValue[50];
    int matches[MAX_MATCHES], matchCount;
    
    printf("Edit by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    printf("Enter value: ");
    fgets(value, sizeof(value), stdin);
    value[strcspn(value, "\n")] = 0;

    int found = findContact(addressBook, value, choice, matches, &matchCount);
    if (found == -1) {
        printf("❌ Contact not found.\n");
        return;
    }
    // If multiple matches, ask user to select
    if (matchCount > 1) {
        printf("Multiple contacts found:\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int selection;
        do {
            printf("Select contact number to edit (1-%d): ", matchCount);
            scanf("%d", &selection);
            getchar();
        } while (selection < 1 || selection > matchCount);
        found = matches[selection - 1];
    }

    printf("\nEditing Contact:\n%s | %s | %s\n",
           addressBook->contacts[found].name,
           addressBook->contacts[found].phone,
           addressBook->contacts[found].email);

    printf("Edit field:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    int editChoice;
    scanf("%d", &editChoice);
    getchar();
        // Input validation loop
    int valid = 0;
    switch (editChoice) {
        case 1:
            printf("Enter new name: ");
            fgets(newValue, sizeof(newValue), stdin);
            newValue[strcspn(newValue, "\n")] = 0;
            strcpy(addressBook->contacts[found].name, newValue);
            break;

        case 2:
            do {
                printf("Enter new phone: ");
                fgets(newValue, sizeof(newValue), stdin);
                newValue[strcspn(newValue, "\n")] = 0;

                if (!isValidPhone(newValue)) {
                    printf("❌ Invalid phone!\n");
                    continue;
                }

                if (isDuplicatePhone(addressBook, newValue, found)) {
                    printf("⚠️ Duplicate phone!\n");
                    continue;
                }
                valid = 1;
            } while (!valid);
            strcpy(addressBook->contacts[found].phone, newValue);
            break;

        case 3:
            do {
                printf("Enter new email: ");
                fgets(newValue, sizeof(newValue), stdin);
                newValue[strcspn(newValue, "\n")] = 0;

                if (!isValidEmail(newValue)) {
                    printf("❌ Invalid email!\n");
                    continue;
                }

                if (isDuplicateEmail(addressBook, newValue, found)) {
                    printf("⚠️ Duplicate email!\n");
                    continue;
                }
                valid = 1;
            } while (!valid);
            strcpy(addressBook->contacts[found].email, newValue);
            break;

        default:
            printf("❌ Invalid choice.\n");
            return;
    }
    // Save changes
    saveContactsToFile(addressBook);
    printf("✅ Contact updated successfully!\n");
}
// Delete a contact
void deleteContact(AddressBook *addressBook) {
    int choice;
    char value[50];
    int matches[MAX_MATCHES], matchCount;

    if (addressBook->contactCount == 0) {
        printf("⚠️ No contacts to delete.\n");
        return;
    }

    printf("Delete by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    printf("Enter value: ");
    fgets(value, sizeof(value), stdin);
    value[strcspn(value, "\n")] = 0;

    int found = findContact(addressBook, value, choice, matches, &matchCount);
    if (found == -1) {
        printf("❌ Contact not found.\n");
        return;
    }

    if (matchCount > 1) {
        printf("Multiple contacts found:\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("%d. %s | %s | %s\n",
                   i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int selection;
        do {
            printf("Select contact number to delete (1-%d): ", matchCount);
            scanf("%d", &selection);
            getchar();
        } while (selection < 1 || selection > matchCount);
        found = matches[selection - 1];
    }

    printf("Deleting Contact: %s | %s | %s\n",
           addressBook->contacts[found].name,
           addressBook->contacts[found].phone,
           addressBook->contacts[found].email);

    char confirm;
    printf("Are you sure? (y/n): ");
    scanf(" %c", &confirm);
    getchar();
    if (confirm != 'y' && confirm != 'Y') {
        printf("⚠️ Deletion cancelled.\n");
        return;
    }

    // Shift contacts
    for (int i = found; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    saveContactsToFile(addressBook);
    printf("✅ Contact deleted successfully!\n");
}
// Save and exit
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    printf("All changes saved. Exiting...\n");
    exit(EXIT_SUCCESS);
}

// Validation and utility functions
int isValidPhone(const char *phone) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') return 0;
    }
    return 1;
}
// Check for duplicate phone number
int isDuplicatePhone(AddressBook *ab, const char *phone, int excludeIndex) {
    for (int i = 0; i < ab->contactCount; i++) {
        if (i != excludeIndex && strcmp(ab->contacts[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}
// Simple email validation
int isValidEmail(const char *email) {
    char *at = strchr(email, '@');
    char *dot = strstr(email, ".com");
    return at && dot && at < dot;
}
// Check for duplicate email
int isDuplicateEmail(AddressBook *ab, const char *email, int excludeIndex) {
    for (int i = 0; i < ab->contactCount; i++) {
        if (i != excludeIndex && strcmp(ab->contacts[i].email, email) == 0)
            return 1;
    }
    return 0;
}

// Search contacts: type 1=name, 2=phone, 3=email
int findContact(AddressBook *ab, const char *value, int type, int *matches, int *matchCount) {
    *matchCount = 0;
    for (int i = 0; i < ab->contactCount; i++) {
        if ((type == 1 && strcmp(ab->contacts[i].name, value) == 0) ||
            (type == 2 && strcmp(ab->contacts[i].phone, value) == 0) ||
            (type == 3 && strcmp(ab->contacts[i].email, value) == 0)) {
            matches[(*matchCount)++] = i;
        }
    }
    return (*matchCount > 0) ? matches[0] : -1;
}