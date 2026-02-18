import csv
import os

import os
import csv

class LibrarySystem:
    def __init__(self, filename='book.csv'):
        # ১. এই পাইথন ফাইলটি (script) কোন ফোল্ডারে আছে তা বের করা
        script_dir = os.path.dirname(os.path.abspath(__file__))
        
        # ২. সেই ফোল্ডারের পাথের সাথে 'book.csv' জোড়া লাগানো
        self.filename = os.path.join(script_dir, filename)
        
        self.columns = ['id', 'name', 'price', 'quantity']
        
        # ফাইল তৈরি করা (যদি না থাকে)
        if not os.path.exists(self.filename):
            try:
                with open(self.filename, 'w', newline='') as f:
                    writer = csv.DictWriter(f, fieldnames=self.columns)
                    writer.writeheader()
                print(f"File created at: {self.filename}")
            except PermissionError:
                print("Error: Permission denied. Please close the CSV file if it's open.")

    def load_books(self):
        books = []
        try:
            with open(self.filename, 'r', newline='') as f:
                reader = csv.DictReader(f)
                for row in reader:
                    books.append(row)
        except FileNotFoundError:
            return []
        return books

    def save_books(self, books):
        """লিস্ট আপডেট করার পর CSV তে সেভ করবে"""
        with open(self.filename, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=self.columns)
            writer.writeheader()
            writer.writerows(books)

    # ================= STAFF FUNCTIONS =================
    def add_book(self):
        print("\n--- Add New Book ---")
        b_id = input("Enter Book/Product ID: ")
        name = input("Enter Book Name: ").lower()
        price = input("Enter Price: ")
        qty = input("Enter Quantity: ")

        books = self.load_books()
        
        for book in books:
            if book['id'] == b_id:
                print("Error: This ID already exists!")
                return

        books.append({'id': b_id, 'name': name, 'price': price, 'quantity': qty})
        self.save_books(books)
        print("Book added successfully!")

    def modify_book(self):
        print("\n--- Modify Book ---")
        search_term = input("Enter Book Name or ID to search: ").lower()
        books = self.load_books()
        found_books = []

        # সার্চ করা হচ্ছে
        for index, book in enumerate(books):
            if search_term in book['name'] or search_term == book['id']:
                found_books.append((index, book))

        if not found_books:
            print("No books found!")
            return

        # যদি একের অধিক বই পাওয়া যায়
        print(f"\nFound {len(found_books)} book(s):")
        for i, (original_index, book) in enumerate(found_books):
            print(f"{i+1}. ID: {book['id']}, Name: {book['name'].title()}, Price: {book['price']}, Qty: {book['quantity']}")

        choice = int(input("\nEnter the number of the book you want to update: ")) - 1
        
        if 0 <= choice < len(found_books):
            target_index = found_books[choice][0]
            current_book = books[target_index]
            
            print(f"\nUpdating: {current_book['name'].title()}")
            print("Leave blank to keep current value.")
            
            new_name = input(f"New Name ({current_book['name']}): ").lower()
            new_price = input(f"New Price ({current_book['price']}): ")
            new_qty = input(f"New Quantity ({current_book['quantity']}): ")

            if new_name: books[target_index]['name'] = new_name
            if new_price: books[target_index]['price'] = new_price
            if new_qty: books[target_index]['quantity'] = new_qty
            
            self.save_books(books)
            print("Book updated successfully!")
        else:
            print("Invalid selection.")

    # ================= USER FUNCTIONS =================
    def search_books(self):
        print("\n--- Search Books ---")
        search_term = input("Enter Book Name: ").lower()
        books = self.load_books()
        found = False
        
        print(f"{'ID':<10} {'Name':<25} {'Price':<10} {'Availability'}")
        print("-" * 60)
        
        for book in books:
            if search_term in book['name']:
                status = f"{book['quantity']} available" if int(book['quantity']) > 0 else "Not Available"
                print(f"{book['id']:<10} {book['name'].title():<25} {book['price']:<10} {status}")
                found = True
        
        if not found:
            print("No books found with that name.")

    def order_book(self):
        print("\n--- Order Book ---")
        search_term = input("Enter Book Name to Order: ").lower()
        books = self.load_books()
        target_index = -1
        
        # বই খোঁজা হচ্ছে
        for index, book in enumerate(books):
            if search_term == book['name']:
                target_index = index
                break
        
        if target_index != -1:
            book = books[target_index]
            current_qty = int(book['quantity'])
            
            print(f"Book found: {book['name'].title()} | Price: {book['price']} | Available: {current_qty}")
            
            if current_qty > 0:
                order_qty = int(input(f"How many copies do you want to order? (Max {current_qty}): "))
                
                if 0 < order_qty <= current_qty:
                    books[target_index]['quantity'] = str(current_qty - order_qty)
                    self.save_books(books)
                    print(f"Order successful! You bought {order_qty} copies.")
                    print(f"Remaining stock: {books[target_index]['quantity']}")
                else:
                    print("Invalid quantity entered!")
            else:
                print("Sorry, this book is currently Out of Stock.")
        else:
            print("Book not found.")

# ================= MENU SYSTEM =================
def main():
    system = LibrarySystem()
    
    while True:
        print("\n==============================")
        print("LIBRARY MANAGEMENT SYSTEM")
        print("1. Staff Login")
        print("2. User Site")
        print("3. Exit")
        choice = input("Select Option: ")

        if choice == '1':
            while True:
                print("\n--- STAFF DASHBOARD ---")
                print("1. Add New Book")
                print("2. Modify Book (Search & Update)")
                print("3. Back to Main Menu")
                s_choice = input("Select Action: ")
                
                if s_choice == '1':
                    system.add_book()
                elif s_choice == '2':
                    system.modify_book()
                elif s_choice == '3':
                    break
                else:
                    print("Invalid choice")

        elif choice == '2':
            while True:
                print("\n--- USER SITE ---")
                print("1. Search Book")
                print("2. Order Book")
                print("3. Back to Main Menu")
                u_choice = input("Select Action: ")
                
                if u_choice == '1':
                    system.search_books()
                elif u_choice == '2':
                    system.order_book()
                elif u_choice == '3':
                    break
                else:
                    print("Invalid choice")
        
        elif choice == '3':
            print("Exiting system...")
            break
        else:
            print("Invalid selection!")

if __name__ == "__main__":
    main()