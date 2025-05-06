# Personal Library Management System

A application to manage a book collection. This project combines core data structures and algorithms to enable efficient operations like adding, removing, searching, and sorting books.

---
## 🚧 Project Status

**In Progress**: This project is currently under development. Below are the planned features and data structures that will be implemented.

---
## Current Features:

- **Add/Remove Books** – Maintain your personal library
- **Search Books** – Lookup by title or ISBN (partial or full)
- **List Books** – View all books with sorting options
<!-- - **Undo/Redo** – Reverse your recent actions -->
<!-- - **Categorization** – Group books by genre -->
<!-- - **Save/Load Collection** – Persist your data via file I/O -->

---

## 📦 Data Structures (In Development)

| Structure         | Purpose                                         |
|------------------|-------------------------------------------------|
| **Arrays/Vectors** | Store the book collection                      |
| **Linked List**    | Dynamic list (manual implementation if no STL) |
| **Stack / Queue**  | Undo/Redo functionality, command history       |
| **Hash Table (Map)** | Fast search by ISBN, title, genre             |
| **Binary Search Tree (BST)** | Sorted views (e.g., by author/title)     |
| **Priority Queue / Heap** | Sort or rank books by rating               |

---

## Project Structure

BookManager/
├── main.cpp / main.py
├── data/
│ └── books.txt # Persistent storage
├── structures/
│ ├── Book.hpp / Book.py # Book class
│ ├── LinkedList.hpp # Linked list for books
│ ├── Stack.hpp # Undo feature
│ └── BST.hpp # Sorted display
├── features/
│ ├── add_remove.cpp
│ ├── search.cpp
│ ├── sort.cpp
│ ├── undo_redo.cpp
│ └── save_load.cpp


## 🤖 Roadmap

### Working on these Features:
- Search by partial title
- Categorize by genre using hash map
- Sort by author, year, rating

### Planned Features
- Command history (queue-based)
- Book ratings (priority queue / heapsort)
- Hash-indexed file access via BookID
- Integrate machine learning for book recommendations
