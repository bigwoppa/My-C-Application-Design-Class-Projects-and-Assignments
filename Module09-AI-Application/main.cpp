#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Record { int id; string name; };

string lower(string text) {
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char ch) { return static_cast<char>(tolower(ch)); });
    return text;
}

// Offline mock: keyword matching stands in for AI interpretation.
class MockSearchAssistant {
public:
    vector<Record> search(const string& request, const vector<Record>& records) const {
        istringstream input(lower(request));
        vector<string> terms;
        string word;
        while (input >> word) {
            if (word != "find" && word != "show" && word != "search" &&
                word != "record" && word != "records" && word != "for" &&
                word != "please") terms.push_back(word);
        }
        vector<Record> matches;
        if (terms.empty()) return matches;
        for (const Record& record : records) {
            string name = lower(record.name);
            bool match = true;
            for (const string& term : terms) {
                if (name.find(term) == string::npos && term != to_string(record.id)) {
                    match = false;
                    break;
                }
            }
            if (match) matches.push_back(record);
        }
        return matches;
    }
};

int main() {
    const vector<Record> records = {
        {101, "Avery Smith"}, {102, "Morgan Diaz"}, {103, "Jordan Lee"}
    };
    MockSearchAssistant assistant;
    cout << "Record Search Assistant - OFFLINE MOCK (no live AI)\n"
         << "Try: find Morgan, show Avery, search Jordan Lee, or 102.\n"
         << "Type quit to exit.\n";
    string request;
    while (cout << "\nSearch request: ", getline(cin, request)) {
        auto first = request.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            cout << "Enter a name or ID. The request cannot be blank.\n";
            continue;
        }
        auto last = request.find_last_not_of(" \t\r\n");
        request = request.substr(first, last - first + 1);
        if (lower(request) == "quit") break;
        if (request.size() > 200) {
            cout << "Use 200 characters or fewer. Please try again.\n";
            continue;
        }
        vector<Record> matches = assistant.search(request, records);
        if (matches.empty()) {
            cout << "[Mock assistant] No matching records. Try a name such as Morgan.\n";
        } else {
            cout << "[Mock assistant] Matching records:\n";
            for (const Record& record : matches)
                cout << "ID: " << record.id << " | Name: " << record.name << '\n';
        }
    }
    cout << "Goodbye!\n";
    return 0;
}
