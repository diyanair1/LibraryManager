#ifndef BOOK_HPP
#define BOOK_HPP
#include <iostream>
using namespace std;

class Book{
    private:
        int bid;
        string title;
        string author;
        string category;
        string status;
    public:
        Book(){
        }
        Book(int bid , string title, string author , string category, string status){
            this -> bid = bid;
            this -> title = title;
            this -> author = author;
            this -> category = category;
            this -> status = status;
        }
        void set_title(string title){
            this->title = title;
        }
        string get_title(){
            return title;
        }
        string get_author(){
            return author;
        }
        string get_category(){
            return category;
        }
        string get_status(){
            return status;
        }
        int get_bid(){
            return bid;
        }
        void set_bid(int new_bid){
            this -> bid = new_bid;
        }
        
        void display(){
            //cout << title << author << ISBN << year << genre << endl;
            // cout << title << " by " << author << " (" << year << ") [ISBN: " << isbn << "] - Genre: " << genre << endl;
            cout << "ID: " << bid << " | "
                << "Title: " << title << " | "
                << "Author: " << author << " | "
                << "Category: " << category << " | "
                << "Status: " << status << endl;
        }

};
#endif