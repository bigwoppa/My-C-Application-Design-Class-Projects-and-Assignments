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
void deleteRecord() {
                    string targetName;
                    cout << "Enter name to delete: ";
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
                            // Close the input file before deleting
                            file.close();
                            // Delete the record by creating a temporary file
                            ifstream inFile("records.csv");
                            ofstream outFile("temp.csv");
                            while (getline(inFile, line)) {
                                stringstream ss(line);
                                string cell;
                                vector<string> row;
                                while (getline(ss, cell, ',')) {
                                    row.push_back(cell);
                                }
                                if (!row.empty() && row[0] != targetName) {
                                    outFile << line << endl;
                                }
                            }
                            inFile.close();
                            outFile.close();
                            // Replace the original file with the temporary file
                            remove("records.csv");
                            rename("temp.csv", "records.csv");

                        }
                    }
                if (!found) {
                            cout << "Record not found." << endl;
                    }
                    file.close();
                };
int main() {
    int choice = 0;

    while (choice != 5) {
        cout << "\n=== MY APPLICATION ===" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Exit" << endl;
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
                deleteRecord();
                break;
            case 5:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}