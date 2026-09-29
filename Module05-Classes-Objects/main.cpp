#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include "RecordTools.h"

using namespace std;

int main() {
    vector<double> records;
    int numberOfRecords;

    showMessage();
    cout << "How many records would you like to add? ";

    while (!(cin >> numberOfRecords) || numberOfRecords < 0) {
        cout << "Please enter a non-negative whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < numberOfRecords; ++i) {
        double value;
        cout << "Enter record " << i + 1 << ": ";

        while (!(cin >> value)) {
            cout << "Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        addRecord(records, value);
    }

    displayRecords(records);

    if (!records.empty()) {
        cout << fixed << setprecision(2);
        cout << "Average: " << calculateAverage(records) << endl;
    }

    return 0;
}
