#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

///Open the CSV file containing the data.



int main() {
    string Majors[10];
    string MedianAnnual[10];
    float UnemploymentRate[10];
    ifstream dataFile("data.csv");
    string line;

    int count = 0;
    while (count < 10 && getline(dataFile, line)) {
        stringstream ss(line);
        getline(ss, Majors[count], ',');
        getline(ss, MedianAnnual[count], ',');
        ss >> UnemploymentRate[count];
        count++;
    }
    
    string *Pincome = &MedianAnnual[0];

    for (int i = 0; i < 10; i++) {
        cout << left << setw(35) << Majors[i] << 
        right << setw(12) << ": " << MedianAnnual[i] << 
        setw(12) << ", Unemployment Rate: " << UnemploymentRate[i] << "%" << endl;
    }

    cout << "First income through pointer: " << *Pincome << endl;
    return 0;
}