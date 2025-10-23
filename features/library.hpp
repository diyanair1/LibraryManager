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
#include <pqxx/pqxx>
#include <fmt/core.h> // module to import fomat
#include <tuple>
//#include <bits/stdc++.h>
using namespace std;

// hpp stands for header++ - used to put a just a class inside it. only contains class/template
//.cpp also works

class Library{
    public:
        map<string, string> load_env(const string &filename){
            map<string, string> env_variables; // type of a variable
            ifstream file(filename); // a pointer to the file (in this case .env)
            if(!file){ // if the pointer to the file has not been made(maybe because file doesnt exist or other errors)
                cerr << "Could not open the requested file\n"; // giving an error message
                return env_variables; // returning an empty map
            }
            string line;
            while(getline(file, line)){ // getting each line of the file(thru the file pointer)
                if(line.empty() || line[0] == '#'){
                    continue;
                } //if the line is either empty or is a comment, then continue
                int pos = line.find('='); // finding the position of the = sign
                if(pos != string::npos){ // if the pos is not at the end of the line(string::npos), then its in the middle
                    string key = line.substr(0 , pos); // line.substr is to make a substring or to slice a part of the string
                    string value = line.substr(pos +1);
                    env_variables[key] = value;
                }
            }
            file.close(); // closing the file
            return env_variables; //returning the map
        }
    /*
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
    */
    //pqxx - this is a cpp library to connect to postgres
        tuple<string, string, string, string, int> connect_to_db(){ // func which contains credentials in order to connect to the db
            map<string, string> env_data  = load_env(".env");
            string db_name = env_data["DB_NAME"];
            string user = env_data["USER"];
            string postgres_password = env_data["POSTGRES_PASSWORD"];
            string host = env_data["HOST"]; // kurian mama's library-core
            int port = std::stoi(env_data["PORT"]);

            return make_tuple(db_name, user, postgres_password, host, port);
            
        }

        void load_from_db(vector<Book>& library){
            try{
                auto [db_name, user, postgres_password, host, port] = connect_to_db(); // auto identifies the datatype of the variables
                pqxx::connection c( // using the connection class constructer of pqxx library, we are doing the connection wih our postgres database
                fmt::format("dbname={} user={} password={} host={} port={}" , db_name, user, postgres_password, host, port) // format is used to retrieve the values of variables needed to connect to db
                );
                //cout << typeid(c).name() << endl; //return the datatype of "c"
                pqxx::work txn(c); // starts a transaction block,which is important to do any interaction with the database
                pqxx::result r = txn.exec("SELECT * FROM books"); // We are using the result func to exract and store the data in a variable(by executing an sql command)
                for(auto row: r){ //it auto detects each row in the db(which is named "r")
                    int bid = row["bid"].as<int>(); //storing the bid value from row into int variable
                    string title = row["title"].as<string>();
                    string author = row["author"].as<string>();// note - make sure the value names are same as th db
                    string category = row["category"].as<string>();
                    string status = row["status"].as<string>();

                    // as we now got all the values for the book, we are creating and object with the values retrieved
                    Book newBook = Book(bid, title, author, category, status); // Create Book object as we have got a value for each section(ex. bid, title, etc,.)
                    library.push_back(newBook);
                }
                txn.commit(); // to seal the changes made to the db
                //cout << "data retrieved from db successfully!" << endl;
            }
            catch(const exception &e){ // if any of the lines in the try block fails - () storing a constant error from try block inside variable "e" (an exception is a class that contains all differnt types of errors)
                cout << e.what() << endl; // we use the .what() func to view the error from object "e"
            } 
        }

        bool add_book(vector<Book>& library , int bid, string title, string author, string category, string status){ // & is used to keep changes that are done in a funtions even after the funtion is passed
            // 1. create the new book object with user inputs

            // int bid = library.size()+2;
            // string title, author, category, status;
            // //bid,title,author,category,status
            // cin.ignore(); // Clear input buffer

            // cout << "Enter Title: \n";
            // getline(cin,title); // or cin >> title; which both takes input

            // /*
            // The getline() function extracts characters from the input stream
            // and appends it to the string object until the delimiting character is encountered.
            // */
            // //first take every input, make book class object with those inputs and then push_back it into the library vector
            // // push on github and update when changes are made
            // cout << "Enter Author: \n";
            // getline(cin, author);

            // cout << "Enter category: \n";
            // getline(cin, category);

            // cout << "Enter status: ";
            // getline(cin, status);
            try{
                Book newBook = Book(bid, title, author, category, status); // Create Book object
                //library.push_back(newBook); // this adds book in the vector temporarily and not in the db

                // 2. Connect to db

                auto [db_name, user, postgres_password, host, port] = connect_to_db(); // auto identifies the datatype of the variables
                pqxx::connection c( // using the connection class constructer of pqxx library, we are doing the connection wih our postgres database
                fmt::format("dbname={} user={} password={} host={} port={}" , db_name, user, postgres_password, host, port) // format is used to retrieve the values of variables needed to connect to db
                );

                pqxx::work txn(c); // starts a transaction block,which is important to do any interaction with the database
                
                // 3. inserting book object to the db using sql insert function

                txn.exec(
                    "INSERT INTO books (bid, title, author, category, status) VALUES ($1, $2, $3, $4, $5)",
                    pqxx::params(bid, title, author, category, status)
                );
                // use insert command to add the new Book object as a row in our sql db table
                
                txn.commit(); // to seal the changes made to the db
                //c.disconnect();
                //cout << "Book added to database successfully!\n";

                // is this step nessesary?
                library.push_back(newBook);

                // displaying the added book
                //cout << "Successfully added the book. Book preview - \n";
                //newBook.display();
                return true;
            }
            catch(const exception& e){
                return false;
            }
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

        Book search_book(vector<Book>& library, string search_title){ // do i have to go into thee db and search or just in the vector?
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


            search_title = toLower(search_title); // avoiding case sensitivity issues
            //cout << search_title << endl;
            int low = 0; // left side
            int high = library.size()-1; // right side
            bool found = false;
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
                    found = true;
                    return book;
                }
                else if(title > search_title){ // Being and Time > war and peace -------- z > a
                    high = mid - 1; // shift to left chunk and discarding the right chunk
                }
                else{
                    low = mid + 1; // shift to right chunk and discarding the left chunk
                }

            }
            if (found == false){ // if the title wasnt found in the entie loop/library, print;
                cout << "Book not found in library!" << endl;
            }
        }
        
        void remove_book(vector<Book>& library, string book_name){
            //can we not use the find/search funtion here?
            for (Book &book : library){ // go to each book in the library
                //string lower_title = tolower(book.get_title());

                string title = book.get_title(); // the original title name
                string lower_title = toLower(title); // lowercase version of title

                string book_name_lower = toLower(book_name); // lowercase version of user input book name

                int bid = book.get_bid() - 1; // accessing book using index
                //string lower_title = transform(title.begin(), title.end(), title.begin(), tolower );

                if (lower_title == book_name_lower){
                    library.erase(library.begin() + bid); // this deletes the book object from only the vector

                    // DELETING BOOK FROM DB
                    // 2. Connect to db

                    auto [db_name, user, postgres_password, host, port] = connect_to_db(); // auto identifies the datatype of the variables
                    pqxx::connection c( // using the connection class constructer of pqxx library, we are doing the connection wih our postgres database
                    fmt::format("dbname={} user={} password={} host={} port={}" , db_name, user, postgres_password, host, port) // format is used to retrieve the values of variables needed to connect to db
                    );

                    pqxx::work txn(c); // starts a transaction block,which is important to do any interaction with the database
                
                    string query = "DELETE FROM books WHERE title=" + txn.quote(title) + ";"; // sql query to delete a row from the postgres db
                    cout << query << endl;
                    txn.exec(query); // executing the sql query to delete row
                    txn.commit();
                    //c.disconnect();

                    cout << "Book deleted successfully!" << endl;

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
                    if (toLower(left_sorted[i].get_title()) < toLower(right_sorted[j].get_title())){ // compare with value comes first alphabetically, iTH value of L array or jTH value of R array
                        result.push_back(left_sorted[i]); //push back the smaller value(alphabetically) into the result array
                        i++;
                    }
                    else{
                        result.push_back(right_sorted[j]);
                        j++;
                    }
                }

                else if(choice == "author"){
                    if (toLower(left_sorted[i].get_author()) < toLower( right_sorted[j].get_author())){
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