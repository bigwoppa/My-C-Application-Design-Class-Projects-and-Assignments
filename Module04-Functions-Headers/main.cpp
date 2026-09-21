#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    string Majors[10];
    int MedianAnnual[10];
    float UnemploymentRate[10];
    
    int *Pincome = &MedianAnnual[0];

    for (int i = 0; i < 3; i++) {
        cout << Majors[i] << ": " << MedianAnnual[i] << ", Unemployment Rate: " << UnemploymentRate[i] << "%" << endl;
    }

    cout << "First income through pointer: " << *Pincome << endl;
    return 0;
}