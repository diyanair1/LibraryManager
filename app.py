from flask import Flask , request
# getrequest is when get data and read data
# postrequests is when you change or write/add into some data
# put request is to change/edit data
# deleterequest is to delete certain data or content

# module is like a file with different funtions and classes with different. ex. random module
# module(in py) == library(in cpp)

# package is a folder with several modules in it. Ex. numpy(for ex it has its own random modules inside it)
# package.module.function  or  package.module.class.function

# a route is a link that calles a funtion
# an api is always a link


app = Flask(__name__) # 

@app.route("/search", methods = ["GET"]) # this route link is for searching a book where we are using get request
def search_book():
    query = request



