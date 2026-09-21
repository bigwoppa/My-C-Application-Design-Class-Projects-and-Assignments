#include <iostream>
using namespace std;

int main() {
    string Majors[10] = {"Ada", "Sam", "Jordan"};
    int MedianAnnual[10] = {91, 84, 97};
    float UnemploymentRate[10] = {5, 7, 4};
    
    int *scorePtr = &MedianAnnual[0];

    for (int i = 0; i < 3; i++) {
        cout << Majors[i] << ": " << MedianAnnual[i] << endl;
    }

    cout << "First score through pointer: " << *scorePtr << endl;
    return 0;
}