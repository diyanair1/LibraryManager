
#include <iostream>
#include "features/book.hpp"
#include "features/library.hpp" //??
#include <vector>
using namespace std;

int main(){
    vector<Book>library; // Book class object is the type of data stored in the vector / a vector of book objects(as each book is an object from the Book class)
    Library l;
    //Book b;
    l.load_from_txt("data/books.txt" , library);

    int choice;
    while (choice != 6){
        // menu displaying
        cout << "Library Manager Menu:\n";
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
        cout << "Successfully added the book. Book preview - \n";
        //how to display single book
        //b.display();
        //l.list_library(library);
        }
        else if (choice == 2) {
        //Search a book
            string title;
            cout << "Enter book name: " << endl;
            cin.ignore();
            getline(cin, title);
            l.search_book(library, title);
        }

        else if (choice == 3) {
            // List the entire library
            l.list_library(library);
        }
        else if (choice == 4) {
            // Remove a book
            //l.remove_book(***book)
        }
        else if (choice == 5) {
            // sort the books
            string choice;
            cout << "Would you like to sort by title or author? : " << endl;
            cin.ignore();
            getline(cin, choice);
            l.sort_library(library, choice);
        }
    }
    

}