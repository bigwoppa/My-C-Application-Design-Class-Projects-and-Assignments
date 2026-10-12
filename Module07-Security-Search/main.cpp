#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

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
        if (binarySearch(id) != -1) {
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

int readInteger(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

        choice = readInteger("Choice: ");

        if (choice == 1) {
            int id = readInteger("Record ID: ");
            string name;
            cout << "Record name: ";
            getline(cin, name);
            admin.addRecord(id, name);
        } else if (choice == 2) {
            admin.viewRecords();
        } else if (choice == 3) {
            admin.searchForRecord(readInteger("ID to find: "));
        } else if (choice == 4) {
            admin.deleteRecord(readInteger("ID to delete: "));
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

        choice = readInteger("Choice: ");

        if (choice == 1) {
            user.viewRecords();
        } else if (choice == 2) {
            user.searchForRecord(readInteger("ID to find: "));
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
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

        roleChoice = readInteger("Choice: ");

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
    return 0;
}
