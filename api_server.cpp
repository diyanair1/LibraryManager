using namespace std;
#include <iostream> // used for input and output
#include "features/book.hpp"
#include "features/library.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>
#include <boost/config.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <cstdlib>

Library lib;
vector<Book> library_data;


// SERIALIZING AND DESERIALIZING

json book_to_json(Book& book){ // serializing each book
    json j;
    j["bid"] = book.get_bid(); //changing to key-value json format (like dictionary)
    j["title"] = book.get_title();
    j["author"] = book.get_author();
    j["category"] = book.get_category();
    j["status"] = book.get_status();
    return j;
}

json books_to_json(vector<Book>& library){ // serializing the books from cpp to json
    json j_arr = json::array();
    for(Book& book : library){
        json j_book = book_to_json(book);
        j_arr.push_back(j_book);
    }
    return j_arr;
}

Book json_to_book(json& j){ // deserializing each book
    int bid = j.contains("bid") ? j["bid"] : -1; // .contains("bid") used to check if a value exists or not
    string title = j.contains("title") ? j["title"] : "";
    string author = j.contains("author") ? j["author"] : "";
    string category = j.contains("category") ? j["category"] : "";
    string status = j.contains("status") ? j["status"] : "";
    Book new_book = Book(bid, title, author, category, status);
    return new_book;
}


template<class Body, class Allocator> // similar to a class and will contain funtions for different endpoints(like web pages) also handling different errors
http :: message_generator handle_requests(
    http :: request <Body, http :: basic_fields<Allocator>>&& req){
        auto const bad_request = [&req](beast :: string_view why){
            http :: response<http::string_body>res{http::status::bad_request, req.version()}; // body of the response will be a string - status::bad_request will get the status code for that status
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING); // set a header value(for response) + version of boost beast in it
            res.set(http::field::content_type, "application/json"); // set a header with content type in it
            res.keep_alive(req.keep_alive()); // this says that as long as the the request is alive or active the reponse should also be "alive" or active
            json error_json; // to store body
            error_json["error"] = std::string(why);
            res.body() = error_json.dump(); //writing the error_json into the body
            res.prepare_payload(); // to say that headers are finalized and the response is ready
            return res;
        };

        auto const not_found = [&req](beast::string_view page){
            http :: response<http::string_body>res{http::status::not_found, req.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING); // set a header value(for response) + version of boost beast in it
            res.set(http::field::content_type, "application/json"); // set a header with content type in it
            res.keep_alive(req.keep_alive()); // this says that as long as the the request is alive or active the reponse should also be "alive" or active
            json error_json; // to store body
            error_json["error"] = "The resource " + std::string(page) + " is not found";
            res.body() = error_json.dump(); //writing the error_json into the body
            res.prepare_payload(); // to say that headers are finalized and the response is ready
            return res;
        };

        auto const server_error = [&req](beast::string_view what){
            http :: response<http::string_body>res{http::status::internal_server_error, req.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING); // set a header value(for response) + version of boost beast in it
            res.set(http::field::content_type, "application/json"); // set a header with content type in it
            res.keep_alive(req.keep_alive()); // this says that as long as the the request is alive or active the reponse should also be "alive" or active
            json error_json; // to store body
            error_json["error"] = "An error occured: " + std::string(what);
            res.body() = error_json.dump(); //writing the error_json into the body
            res.prepare_payload(); // to say that headers are finalized and the response is ready
            return res;
        };

        auto const success_res = [&req](const json& response_json){
            http :: response<http::string_body>res{http::status::ok, req.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING); // set a header value(for response) + version of boost beast in it
            res.set(http::field::content_type, "application/json"); // set a header with content type in it
            res.keep_alive(req.keep_alive()); // this says that as long as the the request is alive or active the reponse should also be "alive" or active
            res.body() = response_json.dump(); //writing the error_json into the body
            res.prepare_payload(); // to say that headers are finalized and the response is ready
            return res;
        };

        std::string target = std::string(req.target()); // target includes all endpoints(different url pages)

        try{ 
            // SEARCH BOOK FUNCTION
            if(req.method() == http::verb::get && target.find("/books/search")==0){ // if the target/endpoint for search book is found- 0 means the endpoint is found
                int query_start = target.find("?title="); // position of the title, if present
                if (query_start == std::string::npos){ // if there is no title in the the request
                    return bad_request("missing title");
                }
                std::string search_title = target.substr(query_start + 7);
                vector<Book> sorted_lib = lib.sort_library(library_data, "title");
                Book searched_book = lib.search_book(sorted_lib, search_title);
                json response;
                response["result"] = book_to_json(searched_book);
                return success_res(response);
            }
            // ADD BOOK FUNCTION - hw
            if(req.method() == http::verb::get && target.find("/books/add")==0){
                try{
                    json req_json = json::parse(req.body()); // getting the req body, convert it into json and store it
                    int bid = library_data.size() + 1;
                    string title = req_json["title"];
                    string author = req_json["author"];
                    string category = req_json["category"];
                    string status = req_json["status"];

                    bool success = lib.add_book(library_data, bid, title, author, category, status);
                    if(success){
                        json response;
                        response["message"] = "Book added successfully!"
                        Book new_book = Book(bid, title, author, category, status);
                        response["book"] = book_to_json(new_book);
                        return success_res(response);
                    }
                    else{
                        return server_error("Database error when adding book.");
                    }
                }
                catch(const exception& e){ // e stores the default error raised in the try block
                    return bad_request(e.message()); // returning default given error
                }
            }

            //LIST BOOKS FUNCTION
            if(req.method() == http::verb::get && target.find("/books/list")==0){  // check endpoint /books/list
                // error handling
                if(library_data.empty()){ 
                    return bad_request("library is empty");
                }

                //if the library data is not empty, then is has data which we need to list thru a response
                json response;
                response["message"] = "Library list"; 
                response["books"] = books_to_json(library_data); 

                return success_res(response);
            }
        }
    }
