// Include iostream to display information and receive user input.
#include <iostream>

// Include fstream to read and save book data in a text file.
#include <fstream>

// Include vector to store the books in memory.
#include <vector>

// Include string to work with book titles and authors.
#include <string>

// Include sstream to separate the information on each line.
#include <sstream>
#include <iomanip>

// Use standard library names without writing std:: each time.
using namespace std;

// Define a class to represent a book in the library.
class Book {
    private:
    int bookID;
    string title;
    string author;
    bool borrowed;
    int pages;
    public:
    // Constructor to initialise a book with its details.
    Book(int id, string bookTitle, string bookAuthor, int bookPages, bool status) {
       bookID = id;
       title = bookTitle;
       author = bookAuthor;
       pages = bookPages;
       borrowed = status;
    }
 // Display the details and borrowing status of a book.
    void displayBook() const {
         cout << "Book ID: " << bookID << endl;
        cout << "Title: " << title << endl;
      cout << "Author: " << author << endl;
       cout << "Pages: " << pages << endl;
      cout << "Status: " << (borrowed ? "Borrowed" : "Available") << endl;
    }
   // Return the unique ID of the book.
   int getID() const { return bookID; }
    // Check whether the book is currently borrowed.
   bool isBorrowed() const { return borrowed; }
    // Mark a book as borrowed.
    void borrowBook() { borrowed = true; }
    // Mark a book as available again.
void returnBook() { borrowed = false; }

// Get the book details needed for saving to the file.
string getTitle() const { return title; }
string getAuthor() const { return author; }
int getPages() const { return pages; }
 };
 
 // Load the books from the data file.
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("bookData.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open bookData.txt" << endl;
        return books;
    }
     // Read each line of the file.
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pagesText, idText, statusText;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pagesText, ',');
        getline(ss, idText, ',');
        getline(ss, statusText, ',');
                // Convert the text values into the correct data types.
        int pages = stoi(pagesText);
        int id = stoi(idText);
        bool borrowed = (statusText == "true");

        // Add the book to the collection.
        books.push_back(Book(id, title, author, pages, borrowed));
    }

    file.close();
    return books;
}
 // Save the updated books to the data file.
void saveBooks(const vector<Book>& books) {
    ofstream file("bookData.txt");

    if (!file.is_open()) {
        cout << "Error: Could not save bookData.txt" << endl;
        return;
    }
        // Write each book to the file in the original CSV format.
    for (const Book& book : books) {
        file << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getPages() << ","
             << setw(3) << setfill('0') << book.getID() << ","
             << (book.isBorrowed() ? "true" : "false") << endl;
    }

    file.close();
}  
// Main function to run the Book Manager program.
int main() {
    vector<Book> books = loadBooks();
    int choice;

    // Display the menu until the user chooses to exit.
    do {
        cout << "\n===== BOOK MANAGER =====" << endl;
        cout << "1. View all books" << endl;
        cout << "2. View book details" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
                // Read the user's menu choice.
        cin >> choice;

        // Check that the user entered a valid number.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 5." << endl;
            continue;
        }
                // Option 1: Display all books in the library.
        if (choice == 1) {
            cout << "\n--- All Books ---" << endl;
            for (const Book& book : books) {
                book.displayBook();
                cout << "--------------------" << endl;
            }
        }
                // Option 2: Search for a book by its ID.
        else if (choice == 2) {
            int id;
            cout << "Enter book ID: ";
            cin >> id;

            bool found = false;
            for (const Book& book : books) {
                if (book.getID() == id) {
                    book.displayBook();
                    found = true;
                    break;
                }
            }
                        // Show a message if the book ID does not exist.
            if (!found) {
                cout << "Book not found." << endl;
            }
        }
                // Option 3: Borrow an available book.
        else if (choice == 3) {
            int id;
            cout << "Enter book ID to borrow: ";
            cin >> id;

            bool found = false;
            for (Book& book : books) {
                if (book.getID() == id) {
                    found = true;
                    if (book.isBorrowed()) {
                        cout << "This book is already borrowed." << endl;
                    } else {
                        book.borrowBook();
                        cout << "Book borrowed successfully." << endl;
                    }
                    break;
                }
            }
                        // Show a message if the book ID does not exist.
            if (!found) {
                cout << "Book not found." << endl;
            }
        }
                // Option 4: Return a borrowed book.
        else if (choice == 4) {
            int id;
            cout << "Enter book ID to return: ";
            cin >> id;

            bool found = false;
            for (Book& book : books) {
                if (book.getID() == id) {
                    found = true;
                    if (!book.isBorrowed()) {
                        cout << "This book is already available." << endl;
                    } else {
                        book.returnBook();
                        cout << "Book returned successfully." << endl;
                    }
                    break;
                }
            }
                        // Show a message if the book ID does not exist.
            if (!found) {
                cout << "Book not found." << endl;
            }
        }
                // Option 5: Exit the program.
        else if (choice == 5) {
            cout << "Exiting Book Manager. Goodbye!" << endl;
        }
        // Handle menu choices outside the range 1 to 5.
        else {
            cout << "Invalid choice. Please select 1 to 5." << endl;
        }
            } while (choice != 5);

    // Save any changes to the books before exiting.
    saveBooks(books);

    return 0;
}