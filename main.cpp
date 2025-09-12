
#include <iostream> // used for input and output
#include "features/book.hpp"
#include "features/library.hpp"
#include <vector>
#include <limits>

using namespace std;

// in hpp files there will be only the class and no main funtion. ex - book.hpp & library.hpp
// funtions in "features" folder - 

int main(){
    vector<Book>library; // Book class object is the type of data stored in the vector / a vector of book objects(as each book is an object from the Book class)
    Library l; // library object so that we can use the funtionalities needed for the library
    //Book b;
    //l.load_from_txt("data/books.txt" , library); 
    // create a menu in a while loop with options
    /*
    example - if (choice == 1) {
        addBook(library);
    }
    */
    int choice = 0;
    l.load_from_db(library);
    while (choice != 6){
        //l.load_from_db(library);

        // menu displaying
        cout << "\nLibrary Manager Menu:\n";
        cout << "1. Add a book\n"; // \n can be used instead of the endln() funtion.
        cout << "2. Search a book\n";
        cout << "3. List a library\n";
        cout << "4. Remove a book\n";
        cout << "5. Sort the library\n";
        cout << "6. Exit\n";

        // choice user input
        cout << "Enter the number of the action you want to perform: ";
        cin >> choice;

        if (choice == 1){
            l.add_book(library);
            //cout << "Successfully added the book. Book preview - \n";
            //how to display single book
            //b.display();
            //l.list_library(library);
        }
        else if (choice == 2) {
        //Search a book
            string title;
            vector<Book> result = l.sort_library(library, "title"); // storing the sorted library in "result" variable
            cout << "Enter book name: " << endl;
            cin.ignore();
            getline(cin, title);
            // need to store sorted library in a variable to do binary search
            l.search_book(result, title); // using the sorted library("result") for the search funtion
        }

        else if (choice == 3) {
            // List the entire library
            l.list_library(library);
        }
        else if (choice == 4) {
            string title;
            cout << "Enter the title of the book to remove: ";
            cin.ignore();
            getline(cin, title);
            l.remove_book(library, title);
        }
        else if (choice == 5) {
            // sort the books
            string choice2;
            cout << "Would you like to sort by title or author? : " << endl;
            cin.ignore();
            getline(cin, choice2);
            vector<Book> result = l.sort_library(library, choice2);
            l.list_library(result);
        }
    }
}