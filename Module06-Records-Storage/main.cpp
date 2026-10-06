#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Book {
private:
    string title;
    string author;
    double price;

public:
    // Constructor
    Book(string title, string author, double price) {
        this->title = title;
        this->author = author;
        this->price = price;
    }

    // Displays the book's information
    void displayBook() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << fixed << setprecision(2);
        cout << "Price: $" << price << endl;
    }

    // Applies a percentage discount
    void applyDiscount(double percent) {
        if (percent >= 0 && percent <= 100) {
            price -= price * (percent / 100.0);
        }
    }

    // Getter
    string getTitle() const {
        return title;
    }

    // Setter
    void setPrice(double newPrice) {
        if (newPrice >= 0) {
            price = newPrice;
        }
    }
};

int main() {
    // Create two objects
    Book book1("The Hobbit", "J.R.R. Tolkien", 15.99);
    Book book2("1984", "George Orwell", 12.50);

    // Use a member function
    book2.applyDiscount(20);

    cout << "Book 1" << endl;
    book1.displayBook();

    cout << "\nBook 2" << endl;
    book2.displayBook();

    // Demonstrate the getter
    cout << "\nThe first book's title is: "
         << book1.getTitle() << endl;

    return 0;
}