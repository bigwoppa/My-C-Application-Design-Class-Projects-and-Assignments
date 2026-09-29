# Record System

This C++ program demonstrates how to:

- Add numeric records
- Display all records
- Calculate the average of the records
- Declare functions in a header file
- Implement functions in a separate `.cpp` file

## Files

- `main.cpp` runs the program and collects user input.
- `RecordTools.h` contains the function declarations.
- `RecordTools.cpp` contains the function implementations.

## Build

Compile both `.cpp` files together:

```powershell
g++ main.cpp RecordTools.cpp -std=c++17 -o records.exe
```

Do not compile the `.h` file by itself.

## Run

```powershell
.\records.exe
```

## Example

```text
Record system ready!
How many records would you like to add? 3
Enter record 1: 80
Enter record 2: 90
Enter record 3: 100

Records:
1. 80.00
2. 90.00
3. 100.00
Average: 90.00
```
