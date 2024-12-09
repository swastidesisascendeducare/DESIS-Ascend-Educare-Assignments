// Code for BookStore Inventory Management Assignment
// Detailed descriptions of classes and their methods are given before each class

#include<bits/stdc++.h>
using namespace std;

/*
Defining the Book & Magazine Class (Both are similar): 

It has the attributes: title, author name, publication, bookID, selling price, cost price and the count of the total number of books. (And edition in case of Magazine)

A constructor Book/Magazine is there for easy object creation.

Methods of the class include:
- addBookCount/ addMagazineCount: to add to the existing stock of books/ magazines.
- subtractBookCount/ subtractMagazineCount: to discard books/ magazines from the stock
- calculateProfit: to calculate profit made on selling the specific book/ magazine.
- display: displays the title of the book/ magazine along with the selling price and the count of the books in the inventory.
- getCount: displays number of books/ magazines in inventory
- getTitle: displays title of book/magazine
*/

class Book{
public:
    string title;
    string author;
    string publication;
    string bookID;
    double sellingPrice;
    double costPrice; // (cost to store the books)
    int count;

    Book(string t, string a, string p, string i, double sp, double cp, int c): 
        title(t), author(a), publication(p), bookID(i), sellingPrice(sp), costPrice(cp), count(c) {}

    void addBookCount(int additions) {
        if(additions < 0){
            cout << "Cannot add stock for given input! Try again." << endl;
            return;
        }
        count += additions;
        cout << "Added stock for " << title << " (Publication " << publication << "): " << ": " << count << " copies available." << endl;
    }
    
    void subtractBookCount(int discard) {
        if (discard < 0) {
            cout << "Cannot discard stock for given input! Try again." << endl;
            return;
        }
        if (discard > count) {
            cout << "Insufficient stock for " << title << ". Current stock: " << count << endl;
            return;
        }
        count -= discard;
        cout << "Discarded stock for " << title << " (Publication " << publication << "): " << count << " copies available." << endl;
    }

    double calculateProfit() const {
        return sellingPrice - costPrice;
    }

    void display() const {
        cout << title << " - ₹" << sellingPrice << " (Stock: " << count << ")\n";
    }

    int getCount() const { 
        return count; 
    }

    string getTitle() const { 
        return title; 
    }
};

class Magazine{
public:
    string title;
    string publication;
    string edition;
    string magazineID;
    double sellingPrice;
    double costPrice; // (cost to store the books)
    int count;

    Magazine(string t, string p, string e, string i, double sp, double cp, int c):
        title(t), publication(p), edition(e), magazineID(i), sellingPrice(sp), costPrice(cp), count(c) {}

    void addMagazineCount(int additions) {
        if(additions < 0){
            cout << "Cannot add stock for given input! Try again." << endl;
            return;
        }
        count += additions;
        cout << "Added stock for " << title << " (Edition " << edition << "): " << count << " copies available." << endl;
    }

    void subtractMagazineCount(int discard) {
        if (discard < 0) {
            cout << "Cannot discard stock for given input! Try again." << endl;
            return;
        }
        if (discard > count) {
            cout << "Insufficient stock for " << title << ". Current stock: " << count << endl;
            return;
        }
        count -= discard;
        cout << "Discarded stock for " << title << " (Edition " << edition << "): " << count << " copies available." << endl;
    }

    double calculateProfit() const {
        return sellingPrice - costPrice;
    }

    void display() const {
        cout << title << "(Edition: " << edition << ") - ₹" << sellingPrice << " (Stock: " << count << ")\n";
    }

    int getCount() const { 
        return count; 
    }

    string getTitle() const { 
        return title; 
    }
};

/*
   Employee class is for the two employees of the BookStore: 
   - the cashier 
   - the store manager

   attributes: name, email and phone number.
*/ 

class Employee{
public:
    string name;
    string email;
    string phoneNo;

    Employee(string n, string m, string ph):
        name(n), email(m), phoneNo(ph) {}
};

/*
This is the store manager class. It inherits from the Employee class.
It has two functions:
- add books: to add books to the inventory
- add magazines: to add magazines to the inventory.
*/

class StoreManager: public Employee{
public:
    StoreManager(string n, string m, string ph): Employee(n, m, ph) {}

    void addBook(vector<Book>& inventory, const Book& book) {
        inventory.push_back(book);
        cout << "Book '" << book.title << " (Publication " << book.publication << "): " << "' added to inventory." << endl;
    }

    void addMagazine(vector<Magazine>& inventory, const Magazine& magazine) {
        inventory.push_back(magazine);
        cout << "Magazine '" << magazine.title << " (Edition " << magazine.edition << "): " << "' added to inventory." << endl;
    }
};

/*
This is the cashier class. It inherits from the Employee class.
It has two functions:
- sell books: to sell books and subtract the amount from the inventory (if present in stock)
- sell magazines: to sell magazines and subtract the amount from the inventory (if present in stock)
*/

class Cashier : public Employee{
public:
    Cashier(string n, string m, string ph) : Employee(n, m, ph) {}

    void sellBook(Book& book, int quantity) {
        if (quantity <= 0) {
            cout << "Invalid quantity for selling! Must be greater than 0." << endl;
            return;
        }
        if (book.count < quantity) {
            cout << "Insufficient stock for " << book.title << ". Current stock: " << book.count << endl;
            return;
        }
        book.count -= quantity;
        cout << "Sold " << quantity << " of " << book.title << " (Publication " << book.publication << "). Remaining stock: " << book.count << "." << endl;
    }


    void sellMagazine(Magazine& magazine, int quantity) {
        if (quantity <= 0) {
            cout << "Invalid quantity for selling! Must be greater than 0." << endl;
            return;
        }
        if (magazine.count < quantity) {
            cout << "Insufficient stock for " << magazine.title << ". Current stock: " << magazine.count << endl;
            return;
        }
        magazine.count -= quantity;
        cout << "Sold " << quantity << " of " << magazine.title << " (Edition " << magazine.edition << "). Remaining stock: " << magazine.count << "." << endl;
    }

};

/*
This is the customer class. It has attributes name, email and phone number.
There is one method of this class (viewInventory) which is to see the inventory details so that he/she can buy accordingly.
*/

class Customer {
public:
    string name;
    string email;
    string phoneNo;

    Customer(string n, string m, string ph) : name(n), email(m), phoneNo(ph){}

    void viewInventory(const vector<Book>& books, const vector<Magazine>& magazines) {
        cout << "\nAvailable Books:\n";
        for (const auto& book : books) {
            cout << book.title << " (Publication " << book.publication << "): " << " by " << book.author << " - ₹" << book.sellingPrice << " (Stock: " << book.count << ")\n";
        }
        cout << "\nAvailable Magazines:\n";
        for (const auto& magazine : magazines) {
            cout << magazine.title << " (Edition " << magazine.edition << ") - ₹" << magazine.sellingPrice << " (Stock: " << magazine.count << ")\n";
        }
    }
};

// -------------------------------------------END--------------------------------------------

// main function to test working

int main() {
    vector<Book> bookInventory;
    vector<Magazine> magazineInventory;

    Book book1("Harry Potter", "J.K. Rowling", "Penguin", "A1234", 900.00, 750.00, 100);
    Book book2("Matilda", "Roald Dahl", "Penguin", "B5678", 400.00, 250.00, 50);
    Magazine magazine1("National Geographic", "National Geographic Society", "March 2024", "C1234", 200.00, 100.00, 200);
    Magazine magazine2("Time", "Time USA, LLC", "April 2024", "D5678", 300.00, 200.00, 150);

    StoreManager manager("Swasti", "swasti.mishra@desisascendeducare.in", "9730587031");
    Cashier cashier("Shreya", "shreya.ojha@gmail.com", "9277352712");

    manager.addBook(bookInventory, book1);
    manager.addBook(bookInventory, book2);
    manager.addMagazine(magazineInventory, magazine1);
    manager.addMagazine(magazineInventory, magazine2);

    Customer customer("Rahul", "rahul282@gmail.com", "1234567890");

    cout << "\n Inventory Details: \n";
    customer.viewInventory(bookInventory, magazineInventory);

    cashier.sellBook(bookInventory[0], 10); //selling 10 copies of harry potter
    cashier.sellMagazine(magazineInventory[1], 20); //selling 20 copies of time usa magazine

    cout << "\nInventory after sales:\n";
    customer.viewInventory(bookInventory, magazineInventory);

    cout << "\nProfit:\n";
    for (const auto& book : bookInventory) {
        cout << "Book: " << book.getTitle() << " - Profit: ₹" << book.calculateProfit() << "\n";
    }
    for (const auto& magazine : magazineInventory) {
        cout << "Magazine: " << magazine.getTitle() << " - Profit: ₹" << magazine.calculateProfit() << "\n";
    }
    return 0;
}

//-------------------------------------------------------------------------------------------