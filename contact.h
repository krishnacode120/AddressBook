/*This header file defines the structures and function prototypes for managing
  contacts in an address book application, including creation, searching,
  editing, deletion, and listing of contacts, as well as validation functions
  for phone numbers and email addresses. It also sets a maximum limit on the
  number of contacts that can be stored.
*/
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
// Function Prototypes
void initialize(AddressBook *addressBook);                 
void listContacts(AddressBook *addressBook); 
void createContact(AddressBook *addressBook);               
void searchContact(AddressBook *addressBook);               
void editContact(AddressBook *addressBook);                 
void deleteContact(AddressBook *addressBook);               
void saveAndExit(AddressBook *addressBook);                 
// File operations
void saveContactsToFile(AddressBook *addressBook);          
void loadContactsFromFile(AddressBook *addressBook); 
// Validation and utility functions
int isValidPhone(const char *phone);                        
int isDuplicatePhone(AddressBook *addressBook, const char *phone, int excludeIndex);
int isValidEmail(const char *email);                        
int isDuplicateEmail(AddressBook *addressBook, const char *email, int excludeIndex);
int findContact(AddressBook *addressBook, const char *value, int criteria, int *matches, int *matchCount);       
#endif
