#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Add a name and age to the CSV file.
void addRecord()
{
    string name;
    int age;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;

    ofstream file("records.csv", ios::app);

    if (!file)
    {
        cout << "Error opening file." << endl;
        return;
    }

    file << name << "," << age << endl;
    file.close();

    cout << "Record added successfully!" << endl;
}

// Display every record in the CSV file.
void viewRecords()
{
    ifstream file("records.csv");

    if (!file)
    {
        cout << "No records are available." << endl;
        return;
    }

    string line;
    cout << "Records:" << endl;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

// Search for a record by name.
void searchRecords()
{
    string targetName;
    cout << "Enter name to search: ";
    cin >> targetName;

    ifstream file("records.csv");

    if (!file)
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    // Read the file one line at a time.
    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        vector<string> row;

        // Split the line at each comma.
        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        // Check whether the name matches.
        if (!row.empty() && row[0] == targetName)
        {
            cout << "Record found: " << line << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Record not found." << endl;
    }

    file.close();
}

// Remove all records from the CSV file.
void clearRecords()
{
    ofstream file("records.csv", ios::trunc);
    file.close();

    cout << "All records cleared." << endl;
}

// Delete records that match a name entered by the user.
void deleteRecord()
{
    string targetName;
    cout << "Enter name to delete: ";
    cin >> targetName;

    ifstream inFile("records.csv");
    ofstream outFile("temp.csv");

    if (!inFile || !outFile)
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        if (name == targetName)
        {
            found = true;
        }
        else
        {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (found)
    {
        remove("records.csv");
        rename("temp.csv", "records.csv");
        cout << "Record deleted." << endl;
    }
    else
    {
        remove("temp.csv");
        cout << "Record not found." << endl;
    }
}

int main()
{
    // Application variables: five data types are represented here.
    string userName = "Salem";
    string applicationName = "Record Manager";
    double versionNumber = 1.0;
    int numberOfMenuOptions = 6;
    char accessLevel = 'A';
    bool savesRecordsToFile = true;

    // Personalized welcome screen that prints every application variable.
    cout << "========================================" << endl;
    cout << "        WELCOME TO MY APPLICATION       " << endl;
    cout << "========================================" << endl;
    cout << "User: " << userName << endl;
    cout << "Application: " << applicationName << endl;
    cout << "Version: " << versionNumber << endl;
    cout << "Menu options: " << numberOfMenuOptions << endl;
    cout << "Access level: " << accessLevel << endl;
    cout << boolalpha;
    cout << "Saves records to a file: " << savesRecordsToFile << endl;

    int choice = 0;

    while (choice != 6)
    {
        cout << "\n=== " << applicationName << " ===" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Clear All Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
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