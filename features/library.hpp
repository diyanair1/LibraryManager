#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include <iostream>
#include <vector>
#include <string>
#include "book.hpp"
#include <fstream> // to read/write a file
#include <sstream> // to read line by line
#include <algorithm>
#include <cctype>
#include <cstring>
//#include <bits/stdc++.h>
using namespace std;

// hpp stands for header++ - used to put a just a class inside it. only contains class/template
//.cpp also works

class Library{
    public:
        void load_from_txt(const string& filename, vector<Book>& library){ // used to take data from books.txt to library vector
            // take input from book.txt, split it (w/commas)
            //  we pass by reference(&) so that it can be changed outside the funtion as well.

            ifstream in(filename); // kind of opening the file or telling the program that this is the file going to be read

            // ifstream is used to read from the file
            // offstream is to write in a file(output)
            // in order to use the above, u have to use fstream library
            string line;
            while(getline(in,line)){ // get each line until there is a line
                // getline() can be used to take input from a file or user(in or cin)
                stringstream ss(line); // used for taking input from a line(with getline()) FROM A FILE
                
                string bid, title, author, category, status;
                getline(ss, bid, ','); // seperating by comma and breaking down the line input
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, category, ',');
                getline(ss, status, ',');
                int id = stoi(bid); //converts bid string variable to integer and stores in an updated variable
                Book newBook = Book(id, title, author, category, status); // Create Book object as we have got a value for each section(ex. bid, title, etc,.)
                library.push_back(newBook);
                // cout << "ID: " << bid << " | "
                // << "Title: " << title << " | "
                // << "Author: " << author << " | "
                // << "Category: " << category << " | "
                // << "Status: " << status << endl;
            }
        }

        void add_book(vector<Book>& library){ // & is used to keep changes that are done in a funtions even after the funtion is passed
            int bid;
            string title, author, category, status;
            //bid,title,author,category,status
            cout << "Enter BID:";// ???
            cin >> bid;
            cin.ignore(); // Clear input buffer

            cout << "Enter Title: \n";
            getline(cin,title); // or cin >> title; which both takes input

            /*
            The getline() function extracts characters from the input stream
            and appends it to the string object until the delimiting character is encountered.
            */
            //first take every input, make book class object with those inputs and then push_back it into the library vector
            // push on github and update when changes are made
            cout << "Enter Author: \n";
            getline(cin, author);

            cout << "Enter category: \n";
            getline(cin, category);

            cout << "Enter status: ";
            getline(cin, status);

            Book newBook = Book(bid, title, author, category, status); // Create Book object
            library.push_back(newBook);
            
        }
        void list_library(vector<Book>& library){
            // displays all the books in the library line by line
            // library vector has to first be stored with data in books.txt 
            for (Book book : library){ // going to each book in the library and displaying it one at a time
                book.display();
            }
        }

        string toLower(const string& str) {
            string lower = str;
            for (char& c : lower) {
                c = tolower(c);
            }
            return lower;
        }

        void search_book(vector<Book>& library, string search_title){
            // LINEAR SEARCH
            // search_title = toLower(search_title);
            // bool found = false;
            // for (Book &book : library){ // linear search
            //     //string lower_title = tolower(book.get_title());
            //     string title = book.get_title();
            //     string lower_title = toLower(title);
            //     //string lower_title = transform(title.begin(), title.end(), title.begin(), tolower );
            //     if (lower_title == search_title){ // if the user title and book title is matched then,
            //         book.display(); // display the book that was matched
            //         found = true;
            //         break;
            //     }
            // }
            // if (found == false){ // if the title wasnt found in the entie loop/library, print;
            //     cout << "Book not found in library!" << endl;
            // }

            //BINARY SEARCH
            // [2 , 4 , 5 , 7 , 9 , 11] (sorted list example)
            // low = 0
            // high = 5
            // mid = (0 + 5)// 2 = 2



            search_title = toLower(search_title); // avaoioding case sensitivity issues
            //cout << search_title << endl;
            int low = 0; // left side
            int high = library.size()-1; // right side
            while (low <= high){
                //cout << "low: " << low << endl;
                //cout << "high: " << high << endl;
                int mid = (low + high)/2;
                //cout << mid << endl;
                Book book = library[mid]; // the middle book of the current chunk of books
                string title = toLower(book.get_title());
                //cout << "search book: " << search_title << endl;
                //cout << "current book: " << title << endl;

                if (title == search_title){ // if both the books ae same display the book and break the loop
                    book.display();
                    cout << "Book found!" << endl;
                    //cout << title << endl;
                    //cout << search_title << endl;
                    break;
                }
                else if(title > search_title){ // Being and Time > war and peace -------- z > a
                    high = mid - 1; // shift to left chunk and discarding the right chunk
                }
                else{
                    low = mid + 1; // shift to right chunk and discarding the left chunk
                }

            }
        }
        
        void remove_book(vector<Book>& library, string book_name){
            //can we not use the find/search funtion here?
            for (Book &book : library){ // go to each book in the library
                //string lower_title = tolower(book.get_title());

                string title = book.get_title(); // the original title name
                string lower_title = toLower(title); // lowercase version of title

                toLower(book_name); // lowercase version of user input book name

                int bid = book.get_bid() - 1; // accessing book using index
                //string lower_title = transform(title.begin(), title.end(), title.begin(), tolower );

                if (lower_title == book_name){
                    library.erase(library.begin() + bid);
                    update_id(library , bid);
                    break;
                }
            }
        }

        void update_id(vector<Book>& library, int book_bid){
            if (book_bid != library.size() - 1){ //if it is not th last book, then;
                for (int i = book_bid; i < library.size(); i++){
                    Book &book = library[i];
                    book.set_bid(book.get_bid() - 1);
                    //cout << book.get_bid() <<  endl;
                }
            }
        }

        vector<Book> merge(vector<Book>& left_sorted, vector<Book>& right_sorted, string choice){
            int n1 = left_sorted.size();
            int n2 = right_sorted.size();
            int i = 0 , j = 0; // indexes used to do incrimentation
            // i is for left array, j is for right array, and k is for result array

            vector<Book> result; // array where the sorted boks will enter while in sorting loop

            while(i < n1 && j < n2){ // run until both left and right arrays have elements 
                if (choice == "title"){
                    if (left_sorted[i].get_title() < right_sorted[j].get_title()){ // compare with value comes first alphabetically, iTH value of L array or jTH value of R array
                        result.push_back(left_sorted[i]); //push back the smaller value(alphabetically) into the result array
                        i++;
                    }
                    else{
                        result.push_back(right_sorted[j]);
                        j++;
                    }
                }

                else if(choice == "author"){
                    if (left_sorted[i].get_author() < right_sorted[j].get_author()){
                        result.push_back(left_sorted[i]);
                        i++;
                    }
                    else{
                        result.push_back(right_sorted[j]);
                        j++;
                    }
                }
            }
            while(i < n1){
                result.push_back(left_sorted[i]);
                i++;
            }
            while(j < n2){
                result.push_back(right_sorted[j]);
                j++;
            }
            return result;
        }

        vector<Book> merge_sort(vector<Book>& library , int left, int right, string choice){ // left & right are indexes
            if (left >= right){
                vector<Book> single;
                single.push_back(library[left]);
                return single;
            }
            int mid = (left + right)/2;
            vector<Book> left_sorted = merge_sort(library, left, mid , choice); // recursion for the left chunck which will further split it
            vector<Book> right_sorted = merge_sort(library, mid + 1, right, choice); // same for the right chunck
            return merge(left_sorted, right_sorted, choice); // this funtion will sort and merge the chunks in the sorted order

        }

        
        vector<Book> sort_library(vector<Book>& library , string choice){
        //     if(choice == "title"){
        //         sort(library.begin() , library.end() , [](Book a , Book b){ //comparater funtion
        //             return a.get_title() < b.get_title();
        //         });

        //     }
        //     else if(choice == "author"){
        //         sort(library.begin() , library.end() , [](Book a , Book b){ //comparater funtion
        //             return a.get_author() < b.get_author();
        //         });


        //     }
        //     else{
        //         cout << "Invalid choice!" << endl;
        //     }
        //     list_library(library);
        // } cmmd + / to comment
            
            if (choice == "title" || choice == "author"){
                vector<Book> result = merge_sort(library, 0,library.size()-1 , choice);
                //list_library(result);
                return result;
            }
            else{
                    cout << "Invalid choice!" << endl;
                    vector<Book> empty;
                    return empty;
            }
        }

};

#endif