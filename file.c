#include <stdio.h>
#include "file.h"
#include "contact.h"
#include <string.h>
#include <stdlib.h>

void saveContactsToFile(AddressBook *addressBook) {
    
    FILE *fptr = fopen("contacts.txt", "w");
    int size = addressBook->contactCount;
    for(int i = 0; i < size; i++) {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {

    FILE *fptr = fopen("contacts.txt", "r");
    if (fptr == NULL) {
        printf("No existing contacts found. Starting fresh.\n");
        return;
    }

    char line[150];
    while (fgets(line, sizeof(line), fptr)) {
        if (addressBook->contactCount >= MAX_CONTACTS) {
            printf("Address book full, cannot load more contacts from file.\n");
            break;
        }
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        if (name && phone && email) {
            Contact newContact;
            strncpy(newContact.name, name, sizeof(newContact.name));
            strncpy(newContact.phone, phone, sizeof(newContact.phone));
            strncpy(newContact.email, email, sizeof(newContact.email));
            addressBook->contacts[addressBook->contactCount++] = newContact;
        }
    }
    fclose(fptr);
    
}
