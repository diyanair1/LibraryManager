# 📚 Personal Library Management System

A application to manage a book collection. This project combines core data structures and algorithms to enable efficient operations like adding, removing, searching, and sorting books.

## Current Features:

- **Add/Remove Books** – Maintain your personal library
- **Search Books** – Lookup by title or ISBN (partial or full)
- **List Books** – View all books with sorting options
- Sort by author, year, rating
- **Save/Load Collection** – Persist your data via file I/O
<!-- - **Undo/Redo** – Reverse your recent actions -->
<!-- - **Categorization** – Group books by genre -->


## 📦 Data Structures

| Structure         | Purpose                                         |
|------------------|-------------------------------------------------|
| **Arrays/Vectors** | Store the book collection                      |
| **Linked List**    | Dynamic list  |
| **Stack / Queue**  | Undo/Redo functionality, command history       |
| **Hash Table (Map)** | Fast search by ISBN, title, genre             |
| **Binary Search Tree (BST)** | Sorted views (e.g., by author/title)     |
| **Priority Queue / Heap** | Sort or rank books by rating               |


## 🤖 Roadmap

### Currently Working on these Features:
- Search by partial title
- Categorize by genre using hash map

### Planned Features
- Add command history with Queue (like shell history)
- Add rating and sort by rating (priority queue or heapsort)
- Create a `BookID` index using a Hash Table and link it to file position for fast access
- Integrate machine learning for book recommendations
