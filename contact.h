#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);                 
void listContacts(AddressBook *addressBook); 
void createContact(AddressBook *addressBook);               
void searchContact(AddressBook *addressBook);               
void editContact(AddressBook *addressBook);                 
void deleteContact(AddressBook *addressBook);               
void saveAndExit(AddressBook *addressBook);                 

void saveContactsToFile(AddressBook *addressBook);          
void loadContactsFromFile(AddressBook *addressBook); 

int isValidPhone(const char *phone);                        
int isDuplicatePhone(AddressBook *addressBook, const char *phone, int excludeIndex);
int isValidEmail(const char *email);                        
int isDuplicateEmail(AddressBook *addressBook, const char *email, int excludeIndex);
int findContact(AddressBook *addressBook, const char *value, int criteria, int *matches, int *matchCount);       
#endif
