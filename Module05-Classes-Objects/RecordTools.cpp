#include <iomanip>
#include <iostream>
#include "RecordTools.h"

using namespace std;

void showMessage() {
    cout << "Record system ready!" << endl;
}

void addRecord(vector<double>& records, double value) {
    records.push_back(value);
}

void displayRecords(const vector<double>& records) {
    if (records.empty()) {
        cout << "No records have been added." << endl;
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\nRecords:" << endl;

    for (size_t i = 0; i < records.size(); ++i) {
        cout << i + 1 << ". " << records[i] << endl;
    }
}

double calculateAverage(const vector<double>& records) {
    if (records.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (double value : records) {
        total += value;
    }

    return total / records.size();
}
