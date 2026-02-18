# 📚 Library Management System

A simple console-based Library Management System implemented in both **C** and **Python**. This project simulates basic library operations like adding books (admin/staff) and searching or ordering books (users).

## 🚀 Project Overview

This project was originally developed for my **1st Semester Structured Programming Course** using **C**. Later, I implemented the same logic using **Python** to demonstrate the differences in syntax, file handling, and ease of development between a low-level and high-level language.

### 📂 Folder Structure
```bash
BookStore/
├── With-C/
│   ├── library.c       # Source code in C
│   └── library.exe     # Compiled executable (Windows)
│
└── With-Python/
    ├── library-system.py # Source code in Python
    └── book.csv          # Data storage (Auto-generated)
```
## ✨ Features
The system is divided into two roles: Staff and User.

### 👨‍💼 Staff (Admin) Features:
Add Books: Add new books with ID, Name, Price, and Quantity.

Modify Books: Update book details (Price, Quantity) by searching via ID or Name.

Data Storage:

C: Uses file handling (books.csv or binary file logic).

Python: Uses csv module for structured data storage.

### 👤 User Features:
Search Books: Search for books by name.

View Availability: Check if a book is in stock or out of stock.

Order Books: Place an order which automatically updates the stock quantity in the database.

## 🛠️ How to Run
1️⃣ Running the C Version
Navigate to the With-C folder.

Compile the code (if not already compiled):

Bash
gcc library.c -o library
Run the executable:

On Windows: library.exe

On Linux/Mac: ./library

2️⃣ Running the Python Version
Ensure you have Python installed.

Navigate to the With-Python folder.

Run the script:

Bash
python library-system.py
A books.csv file will be created automatically to store data.

## 🧠 Learning Outcomes
Structured Programming: Understanding functions, structures, and flow control.

File Handling: Reading from and writing to files in both C and Python.

Algorithm Design: Implementing search logic and inventory management.

Comparison: Observing how 100+ lines of C code can often be condensed into fewer lines in Python.

## 📝 Author
**Atul Paul**

**1st Semester Project**

**Structured Programming Course**

**Check me Here:**
<p align="left">
  <a href="https://github.com/atul-dev-ai">
    <img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white" alt="GitHub">
  </a>
  <a href="https://github.com/paulatul020@gmail.com">
    <img src="https://img.shields.io/badge/email-100000?style=for-the-badge&logo=github&logoColor=white" alt="email">
  </a>
  
  <a href="https://atulpaul.vercel.app">
    <img src="https://img.shields.io/badge/Portfolio-Visit%20Now-blue?style=for-the-badge&logo=google-chrome&logoColor=white" alt="Portfolio">
  </a>
</p>
