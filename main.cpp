
#include <iostream>
#include "features/book.hpp"
#include "features/library.hpp"
#include <vector>
using namespace std;

// funtions in "features" file - 

int main(){
    vector<Book>library; // Book class object is the type of data stored in the vector / a vector of book objects(as each book is an object from the Book class)
    Library l;
    //Book b;
    l.load_from_txt("data/books.txt" , library);
    // create a menu in a while loop with options
    /*
    example - if (choice == 1) {
        addBook(library);
    }
    */
    int choice;
    while (choice != 5){
        // menu displaying
        cout << "Library Manager Menu:\n";
        cout << "1. Add a book\n"; // \n can be used instead of the endln() funtion.
        cout << "2. Search a book\n";
        cout << "3. List a library\n";
        cout << "4. Remove a book\n";
        cout << "4. Exit\n";

        // choice user input
        cout << "Enter the number of the action you want to perform: ";
        cin >> choice;

        if (choice == 1){
        l.add_book(library);
        cout << "Successfully added the book. Book preview - \n";
        //how to display single book
        //b.display();
        //l.list_library(library);
        }
        else if (choice == 2) {
        //Search a book
        //l.search_book(**book);
        }
        else if (choice == 3) {
        // List the entire library
        l.list_library(library);
        }
        else if (choice == 4) {
        // Remove a book
        //l.remove_book(***book)
        }
    }
   

}