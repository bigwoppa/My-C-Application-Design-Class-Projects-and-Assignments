#include <iostream>
#include <string>

// This program demonstrates a simple menu-driven application that allows users to add, view, and search records. It uses file handling to store records in a CSV file.
#include <fstream>
#include <sstream>
#include <vector>

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

int main() {
    int choice = 0;

    while (choice != 4) {
        cout << "\n=== MY APPLICATION ===" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

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
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}