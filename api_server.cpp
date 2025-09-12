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
        }
        //hw to make another error handling funtion like  - page not found
    }





