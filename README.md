Contact Management System (Address Book Application)
Create, Edit, Search, Delete & Store Contacts Persistently using C
📌 Project Overview

This project implements a full Address Book / Contact Management System in C.
It allows users to:

Create new contacts

List all contacts

Search for contacts

Edit contact details

Delete existing contacts

Persist data using a file (contacts.txt)

The application provides input validation, duplicate checks, sorting, and file storage, making it a complete real-world mini-project.

📁 Folder Structure
Contact_Management_System/
│
├── main.c               → Menu-driven program
├── contact.c            → Core logic: add, search, edit, delete, list
├── contact.h            → Struct definitions + function prototypes
├── file.c               → Save & load contacts from file
├── file.h
├── populate.c           → Load dummy contacts
├── populate.h
│
├── contacts.txt         → Persistent storage (auto-created)
├── a.out                → (generated executable)
│
└── README.md

🔧 Compilation Instructions
Using GCC:
gcc main.c contact.c file.c populate.c -o contact_app


Run the program:

./contact_app

▶️ How to Use the Application

When you run the program, this menu appears:

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice:

🧠 Features Implemented
✔ 1. Create New Contacts

Validates phone number (must be 10 digits)

Validates email (@ and .com check)

Prevents duplicates (phone/email)

Auto-saves to file

✔ 2. Search Contacts

Search by:

Name

Phone

Email

If multiple contacts match, the program lists all matches.

✔ 3. Edit Contacts

Allows editing:

Name

Phone (validated + no duplicates)

Email (validated + no duplicates)

✔ 4. Delete Contacts

Multiple match handling

User confirmation before deleting

Shifts remaining contacts

✔ 5. List All Contacts

Sorting options:

Sort by name

Sort by phone

Sort by email

Displayed in a clean tabular format.

✔ 6. Persistent Storage

All contacts are saved to contacts.txt automatically:

Example line:

Alice Smith,0987654321,alice@example.com


contacts

🔎 Important Implementation Details
Contact Structure

From contact.h:


contact

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

Address Book
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

File Storage Logic

When saving contacts:


file

fprintf(fptr, "%s,%s,%s\n", name, phone, email);


When loading contacts:

Reads line-by-line

Uses strtok() to split CSV

Handles newline trimming

Validation Functions

isValidPhone() → Checks 10 digits

isDuplicatePhone() → Prevents duplicates

isValidEmail() → Checks for @ and .com

isDuplicateEmail() → Prevents duplicates

Search Function

Search by 1 = name, 2 = phone, 3 = email:


contact

int findContact(AddressBook *ab, const char *value, int type, int *matches, int *matchCount);

💾 contacts.txt Auto-Generated Example
John Doe,1234567890,john@example.com
Alice Smith,0987654321,alice@example.com
Bob Johnson,1112223333,bob@company.com


This file is loaded automatically on startup.

🚀 How the Program Works Internally

On startup:

Address book is initialized

Contacts are loaded from contacts.txt

Dummy contacts loaded only once (optional)

Menu loop begins

Based on user input, appropriate functions are called

Before exit, contacts are saved back to file

🎯 Features You Can Add (Future Enhancements)

Sort by alphabetical groups (A–Z)

Save contacts in JSON or CSV format

Add birthdays, group tags, or notes

Export/import contact list

Encrypt contact file for security

Add search suggestions

✔ Author

Krishnamoorthy T
Address Book Application – 2025
Built using C, file handling, and structured programming.