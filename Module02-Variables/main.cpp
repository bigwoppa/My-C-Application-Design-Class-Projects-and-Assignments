#include <iostream>
#include <string>
using namespace std;

void addRecord() {
    cout << "Add Record selected." << endl;
}

void viewRecords() {
    cout << "View Records selected." << endl;
}

void searchRecords() {
    cout << "Search selected." << endl;
}

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