#include <iostream>
#include <string>

// This program demonstrates a simple menu-driven application that allows users to add, view, and search records. It uses file handling to store records in a CSV file.
#include <fstream>
#include <sstream>
#include <vector>

// Function to delete a record from the CSV file based on the name provided by the user.
#include <cstdio>

using namespace std;

void addRecord() {
                    string name;
                    int age;

                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;

                    ofstream file("records.csv", ios::app);

                    file << name << "," << age << endl;

                    file.close();

                    cout << "Record added successfully!" << endl;
                };

void viewRecords() {
                    ifstream file("records.csv");
                    string line;

                    cout << "Records:" << endl;
                    while (getline(file, line)) {
                        cout << line << endl;
                    }

                    file.close();
                };
void searchRecords() {
                    string targetName;
                    cout << "Enter name to search: ";
                    cin >> targetName;
                    
                    ifstream file("records.csv");
                    if (!file) {
                        cout << "Error opening file." << endl;
                        return;
                    }
                    string line;
                    bool found = false;

                    // read file line by line
                    while (getline(file, line)) {
                        stringstream ss(line);
                        string cell;
                        vector<string> row;
                        // split line by comma
                        while (getline(ss, cell, ',')) {
                            row.push_back(cell);
                        }
                        // check if the name matches
                        if (!row.empty() && row[0] == targetName) {
                            cout << "Record found: " << line << endl;
                            found = true;
                        
                        }
                    }
                if (!found) {
                            cout << "Record not found." << endl;
                    }
                    file.close();
                };

void clearRecords() {
    ofstream file("records.csv", ios::trunc);

    file.close();

    cout << "All records cleared." << endl;
}

void deleteRecord() {
    string targetName;
    cout << "Enter name to delete: ";
    cin >> targetName;

    ifstream inFile("records.csv");
    ofstream outFile("temp.csv");

    if (!inFile || !outFile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;

        getline(ss, name, ',');

        if (name == targetName) {
            found = true;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("records.csv");
        rename("temp.csv", "records.csv");
        cout << "Record deleted." << endl;
    } else {
        remove("temp.csv");
        cout << "Record not found." << endl;
    }
}
int main() {
    int choice = 0;

    while (choice != 6) {
        cout << "\n=== MY APPLICATION ===" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Clear All Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
        if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        continue;
        }

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                searchRecords();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                clearRecords();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}