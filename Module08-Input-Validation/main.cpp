#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

string trim(const string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}


struct Record {
    int id;
    string name;
};

class RecordManager {
private:
    vector<Record> records;

public:
    // Returns the record's index, or -1 when the ID is not found.
    int binarySearch(int targetId) const {
        int left = 0;
        int right = static_cast<int>(records.size()) - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;

            if (records[middle].id == targetId) {
                return middle;
            }

            if (records[middle].id < targetId) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return -1;
    }

    bool addRecord(int id, const string& name) {
        if (id <= 0 || trim(name).empty() || name.size() > 80 || binarySearch(id) != -1) {
            return false;
        }

        // Find the correct location so the vector stays sorted by ID.
        auto position = records.begin();
        while (position != records.end() && position->id < id) {
            ++position;
        }

        records.insert(position, {id, name});
        return true;
    }

    bool deleteRecord(int id) {
        int index = binarySearch(id);
        if (index == -1) {
            return false;
        }

        records.erase(records.begin() + index);
        return true;
    }

    void viewRecords() const {
        if (records.empty()) {
            cout << "No records are available.\n";
            return;
        }

        cout << "\nRecords (sorted by ID)\n";
        cout << "----------------------\n";
        for (const Record& record : records) {
            cout << "ID: " << record.id << " | Name: " << record.name << '\n';
        }
    }

    void findRecord(int id) const {
        int index = binarySearch(id);
        if (index == -1) {
            cout << "Record not found.\n";
        } else {
            cout << "Found record - ID: " << records[index].id
                 << " | Name: " << records[index].name << '\n';
        }
    }
};

class User {
protected:
    string username;
    RecordManager& manager;

public:
    User(string name, RecordManager& recordManager)
        : username(name), manager(recordManager) {}

    virtual ~User() = default;

    void viewRecords() const {
        manager.viewRecords();
    }

    void searchForRecord(int id) const {
        manager.findRecord(id);
    }

    virtual void showPermissions() const = 0;
};

class Admin : public User {
public:
    Admin(string name, RecordManager& recordManager)
        : User(name, recordManager) {}

    void addRecord(int id, const string& name) {
        if (manager.addRecord(id, name)) {
            cout << "Record added successfully.\n";
        } else {
            cout << "A record with that ID already exists.\n";
        }
    }

    void deleteRecord(int id) {
        if (manager.deleteRecord(id)) {
            cout << "Record deleted successfully.\n";
        } else {
            cout << "Record not found.\n";
        }
    }

    void showPermissions() const override {
        cout << username << " is an Admin and can add, view, search, and delete records.\n";
    }
};

class RegularUser : public User {
public:
    RegularUser(string name, RecordManager& recordManager)
        : User(name, recordManager) {}

    void showPermissions() const override {
        cout << username << " is a Regular User and can only view and search records.\n";
    }
};

// Read the entire line so inputs such as 12abc and 1.5 are rejected.
int readInteger(const string& prompt, int minimum, int maximum) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) throw runtime_error("Input closed.");
        istringstream input(line);
        int value;
        char extra;
        if ((input >> value) && !(input >> extra) &&
            value >= minimum && value <= maximum) {
            return value;
        }
        cout << "Enter a whole number from " << minimum
             << " to " << maximum << ". Please try again.\n";
    }
}

string readName() {
    while (true) {
        cout << "Record name (1-80 characters): ";
        string name;
        if (!getline(cin, name)) throw runtime_error("Input closed.");
        name = trim(name);
        if (!name.empty() && name.size() <= 80) return name;
        cout << "Name cannot be blank and must be 80 characters or fewer. Try again.\n";
    }
}

void adminMenu(Admin& admin) {
    int choice;

    do {
        cout << "\nAdmin Menu\n"
             << "1. Add record\n"
             << "2. View records\n"
             << "3. Search by ID\n"
             << "4. Delete record\n"
             << "0. Log out\n";

        choice = readInteger("Choice: ", 0, 4);

        if (choice == 1) {
            int id = readInteger("Record ID: ", 1, numeric_limits<int>::max());
            string name = readName();
            admin.addRecord(id, name);
        } else if (choice == 2) {
            admin.viewRecords();
        } else if (choice == 3) {
            admin.searchForRecord(readInteger("ID to find: ", 1, numeric_limits<int>::max()));
        } else if (choice == 4) {
            admin.deleteRecord(readInteger("ID to delete: ", 1, numeric_limits<int>::max()));
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void regularUserMenu(RegularUser& user) {
    int choice;

    do {
        cout << "\nRegular User Menu\n"
             << "1. View records\n"
             << "2. Search by ID\n"
             << "0. Log out\n";

        choice = readInteger("Choice: ", 0, 2);

        if (choice == 1) {
            user.viewRecords();
        } else if (choice == 2) {
            user.searchForRecord(readInteger("ID to find: ", 1, numeric_limits<int>::max()));
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
    try {
    RecordManager manager;

    // Initial data is deliberately entered out of order. The manager stores it
    // in sorted order so binary search works correctly.
    manager.addRecord(103, "Jordan Lee");
    manager.addRecord(101, "Avery Smith");
    manager.addRecord(102, "Morgan Diaz");

    Admin admin("Alex", manager);
    RegularUser regularUser("Taylor", manager);

    int roleChoice;
    do {
        cout << "\nRecord Management System\n"
             << "1. Log in as Admin\n"
             << "2. Log in as Regular User\n"
             << "0. Exit\n";

        roleChoice = readInteger("Choice: ", 0, 2);

        if (roleChoice == 1) {
            admin.showPermissions();
            adminMenu(admin);
        } else if (roleChoice == 2) {
            regularUser.showPermissions();
            regularUserMenu(regularUser);
        } else if (roleChoice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (roleChoice != 0);

    cout << "Goodbye!\n";
    } catch (const runtime_error& error) {
        cout << "\n" << error.what() << " Exiting safely.\n";
    }
    return 0;
}
