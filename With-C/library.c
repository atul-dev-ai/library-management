#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100 // সর্বোচ্চ ১০০টি বই রাখা যাবে

// বইয়ের স্ট্রাকচার
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Book;

// গ্লোবাল ভেরিয়েবল (Global Variables)
Book library[MAX_BOOKS]; // সব বই এই অ্যারেতে থাকবে
int totalBooks = 0;      // বর্তমানে কয়টি বই আছে তার হিসাব

// বাফার ক্লিয়ার করার ফাংশন (ইনপুট সমস্যা এড়াতে)
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ================= STAFF FUNCTIONS =================

void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("\nMemory Full! Cannot add more books.\n");
        return;
    }

    printf("\n--- Add New Book ---\n");
    
    // ID ইনপুট
    printf("Enter Book ID: ");
    int id;
    scanf("%d", &id);
    clearBuffer(); // বাফার পরিষ্কার

    // ডুপ্লিকেট আইডি চেক
    for (int i = 0; i < totalBooks; i++) {
        if (library[i].id == id) {
            printf("Error: Book ID %d already exists!\n", id);
            return;
        }
    }

    library[totalBooks].id = id;

    // নাম ইনপুট
    printf("Enter Book Name: ");
    fgets(library[totalBooks].name, 50, stdin);
    // নামের শেষের নিউলাইন (\n) রিমুভ করা
    library[totalBooks].name[strcspn(library[totalBooks].name, "\n")] = 0;

    // দাম ইনপুট
    printf("Enter Price: ");
    scanf("%f", &library[totalBooks].price);

    // সংখ্যা ইনপুট
    printf("Enter Quantity: ");
    scanf("%d", &library[totalBooks].quantity);

    totalBooks++; // বইয়ের সংখ্যা ১ বাড়লো
    printf("Book added successfully!\n");
}

void modifyBook() {
    printf("\n--- Modify Book ---\n");
    printf("Enter Book ID or Name to search: ");
    
    char searchInput[50];
    clearBuffer(); // আগের বাফার থাকলে ক্লিয়ার করবে
    fgets(searchInput, 50, stdin);
    searchInput[strcspn(searchInput, "\n")] = 0; // নিউলাইন রিমুভ

    int foundIndex = -1;

    // লুপ চালিয়ে বই খোঁজা (ID বা Name দিয়ে)
    for (int i = 0; i < totalBooks; i++) {
        // ID চেক করার জন্য স্ট্রিং কনভারশন বা সরাসরি নাম চেক
        // এখানে সহজ করার জন্য আমরা নাম চেক করছি অথবা ইউজার যদি সংখ্যা দেয় সেটা ID হিসেবে চেক করছি
        char idStr[20];
        sprintf(idStr, "%d", library[i].id); // int ID কে string এ কনভার্ট করা হলো

        if (strcmp(library[i].name, searchInput) == 0 || strcmp(idStr, searchInput) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("\nFound: %s (ID: %d) | Price: %.2f | Qty: %d\n", 
               library[foundIndex].name, library[foundIndex].id, 
               library[foundIndex].price, library[foundIndex].quantity);

        printf("\nUpdate Options (Enter -1 to keep old value):\n");

        int newQty;
        printf("New Quantity: ");
        scanf("%d", &newQty);
        if (newQty != -1) library[foundIndex].quantity = newQty;

        float newPrice;
        printf("New Price: ");
        scanf("%f", &newPrice);
        if (newPrice != -1) library[foundIndex].price = newPrice;

        printf("Book Updated Successfully!\n");
    } else {
        printf("Book not found!\n");
    }
}

// ================= USER FUNCTIONS =================

void searchBooks() {
    char searchName[50];
    int found = 0;

    printf("\n--- Search Book ---\n");
    printf("Enter Book Name: ");
    clearBuffer();
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    printf("\n%-5s %-20s %-10s %-15s\n", "ID", "Name", "Price", "Status");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < totalBooks; i++) {
        // strstr দিয়ে নামের অংশ মিললেও খুঁজে বের করবে
        if (strstr(library[i].name, searchName) != NULL) {
            if (library[i].quantity > 0)
                printf("%-5d %-20s %-10.2f %d Available\n", library[i].id, library[i].name, library[i].price, library[i].quantity);
            else
                printf("%-5d %-20s %-10.2f Not Available\n", library[i].id, library[i].name, library[i].price);
            found = 1;
        }
    }

    if (!found) printf("No books found matching '%s'\n", searchName);
}

void orderBook() {
    int orderId, qty, foundIndex = -1;

    printf("\n--- Order Book ---\n");
    printf("Enter Book ID to Order: ");
    scanf("%d", &orderId);

    for (int i = 0; i < totalBooks; i++) {
        if (library[i].id == orderId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Book: %s | Available: %d\n", library[foundIndex].name, library[foundIndex].quantity);

        if (library[foundIndex].quantity > 0) {
            printf("How many copies? ");
            scanf("%d", &qty);

            if (qty > 0 && qty <= library[foundIndex].quantity) {
                library[foundIndex].quantity -= qty; // স্টক কমানো হচ্ছে
                printf("Order Successful! %d copies purchased.\n", qty);
                printf("Remaining Stock: %d\n", library[foundIndex].quantity);
            } else {
                printf("Error: Invalid quantity or not enough stock!\n");
            }
        } else {
            printf("Sorry, Out of Stock!\n");
        }
    } else {
        printf("Book ID not found.\n");
    }
}

// ================= MAIN MENU =================

int main() {
    int choice;

    while (1) {
        printf("\n=================================\n");
        printf(" LIBRARY SYSTEM (No File) \n");
        printf("=================================\n");
        printf("1. Staff Login\n");
        printf("2. User Site\n");
        printf("3. Exit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearBuffer();
            continue;
        }

        if (choice == 1) {
            int sChoice;
            while(1) {
                printf("\n--- STAFF MENU ---\n");
                printf("1. Add Book\n");
                printf("2. Modify Book\n");
                printf("3. Back\n");
                printf("Choice: ");
                scanf("%d", &sChoice);

                if (sChoice == 1) addBook();
                else if (sChoice == 2) modifyBook();
                else break;
            }
        } else if (choice == 2) {
            int uChoice;
            while(1) {
                printf("\n--- USER MENU ---\n");
                printf("1. Search Book\n");
                printf("2. Order Book\n");
                printf("3. Back\n");
                printf("Choice: ");
                scanf("%d", &uChoice);

                if (uChoice == 1) searchBooks();
                else if (uChoice == 2) orderBook();
                else break;
            }
        } else if (choice == 3) {
            printf("Exiting... (All data will be lost)\n");
            break;
        } else {
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}