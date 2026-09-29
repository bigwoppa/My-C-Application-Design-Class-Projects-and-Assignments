#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

#include <vector>

void showMessage();
void addRecord(std::vector<double>& records, double value);
void displayRecords(const std::vector<double>& records);
double calculateAverage(const std::vector<double>& records);

#endif
