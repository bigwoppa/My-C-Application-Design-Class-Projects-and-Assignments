# Record Management System

This is a basic C++ record management program. I made two types of users: an Admin and a Regular User.

The Admin can:

- Add records
- View all records
- Search for a record by ID
- Delete records

The Regular User can:

- View all records
- Search for a record by ID

The records are kept in order by their ID numbers. The program uses binary search to find records faster. I also used inheritance so both user types share the basic features from the User class.

## How to Run

Compile the program with a C++ compiler:

```text
g++ role_based_record_manager.cpp -o record_manager
```

Then run it and choose a user role from the menu.
