#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <stdexcept>
using namespace std;

class book
{
private:
		string title;
		string author;
		string category;
		bool is_borrowed;

public:
		book()
		{
			title = "None";
			author = "None";
			category = "None";
			is_borrowed = false;
		}
	    book(string t, string a, string c)
		{
			title = t;
			author = a;
			category = c;
			is_borrowed = false;

		}

		void setTitle(string t){title = t;}
		void setAuthor(string a){author = a;}
		void setCategory(string c){category = c;}
		void setIsBorrowed(bool b){is_borrowed = b;}

		string getTitle() const {return title;}
		string getAuthor() const {return author;}
		string getCategory() const {return category;}
		bool isBorrowed() const {return is_borrowed;}

	};

class User
{
private:
    int userID;
    string username;
    string password;

public:
    User(int id, string name, string pass)
    {
        userID = id;
        username = name;
        password = pass;
    }

    bool login(string inputUsername, string inputPassword)
    {
        return (username == inputUsername && password == inputPassword);
    }

    int getUserId() const {return userID;}
    string getUsername() const {return username;}
    string getPassword() const {return password;}

};

class Library{
private:
    book* Books;
    int bookcount;
    int capacity;
public:
    Library(int MAX_BOOKS):capacity(MAX_BOOKS), bookcount(0)
    {
        Books = new book[capacity];
    }
    ~Library(){
        delete[]Books;
    }
    void addBooks(const book&b){
        if(bookcount >= capacity) throw overflow_error("Library is full cannot add more books");
        Books[bookcount++] = b;
    
    }
    void removeBooks(const string&title){
        book* newBooks = new book[capacity];
        int counter = 0;
        for(int i=0 ; i<bookcount ; i++){
                if(Books[i].getTitle() != title){
                        newBooks[counter] = Books[i];
                        counter ++;
                }
        }
        delete[] Books;
        Books = newBooks;
        bookcount = counter;
    }
    void searchByTitle(const string&title){
        bool found = false;
        string lowTitle = title;
        transform(lowTitle.begin(), lowTitle.end(), lowTitle.begin(), ::tolower);
        for(int i=0 ; i<bookcount ; i++){
                string lowOgTitle = Books[i].getTitle();
                transform(lowOgTitle.begin(), lowOgTitle.end(), lowOgTitle.begin(), ::tolower);
                if(Books[i].getTitle() == title || lowOgTitle == lowTitle){
                       cout << Books[i].getAuthor() << " " << Books[i].getTitle() << " " << Books[i].getCategory() << endl;
                       found = true;
                }

    }
        if (! found) cout << "Sorry, book is not found" << endl;
    }
    void searchByAuthor(const string&author){
        bool found = false;
        string lowAuthor = author;
        transform(lowAuthor.begin(), lowAuthor.end(), lowAuthor.begin(), ::tolower);
        for(int i=0 ; i<bookcount ; i++){
                string lowOgAuthor = Books[i].getAuthor();
                transform(lowOgAuthor.begin(), lowOgAuthor.end(), lowOgAuthor.begin(), ::tolower);
                if(Books[i].getAuthor() == author || lowOgAuthor == lowAuthor){
                       cout << Books[i].getAuthor() << " " << Books[i].getTitle() << " " << Books[i].getCategory() << endl;
                       found = true;
                }
    }
                if (! found) cout << "Sorry, book is not found" << endl;
    }
    void searchByCategory(const string&category){
        bool found = false;
        string lowCategory = category;
        transform(lowCategory.begin(), lowCategory.end(), lowCategory.begin(), ::tolower);
        for(int i=0 ; i<bookcount ; i++){
                string lowOgCategory = Books[i].getCategory();
                transform(lowOgCategory.begin(), lowOgCategory.end(), lowOgCategory.begin(), ::tolower);
                if(Books[i].getCategory() == category || lowOgCategory == lowCategory){
                       cout << Books[i].getAuthor() << " " << Books[i].getTitle() << " " << Books[i].getCategory() << endl;
                       found = true;
                }
    }
                if (! found) cout << "Sorry, book is not found" << endl;
     }
    void displayBorrowedBooks(){
        cout<<"Borrowed books: "<<endl;
        for(int i=0 ; i < bookcount ; i++){
                if(Books[i].isBorrowed()){
                        cout << Books[i].getAuthor() << " " << Books[i].getTitle() << " " << Books[i].getCategory() << endl;
                }
        }
    }
    void displayNonBorrowed(){
        cout<<"Non borrowed books: "<<endl;
        for(int i=0 ; i < bookcount ; i++){
                if(! Books[i].isBorrowed()){
                        cout << Books[i].getAuthor() << " " << Books[i].getTitle() << " " << Books[i].getCategory() << endl;

    } }

}
   int getBookCount() {return bookcount;}

   book* getAvailableBook(string title, string author, string category)
{
    string lowTitle = title;
    string lowAuthor = author;
    string lowCategory = category;

    transform(lowTitle.begin(), lowTitle.end(), lowTitle.begin(), ::tolower);
    transform(lowAuthor.begin(), lowAuthor.end(), lowAuthor.begin(), ::tolower);
    transform(lowCategory.begin(), lowCategory.end(), lowCategory.begin(), ::tolower);

    for (int i = 0; i < bookcount; i++)
    {
        string lowOgTitle = Books[i].getTitle();
        string lowOgAuthor = Books[i].getAuthor();
        string lowOgCategory = Books[i].getCategory();

        transform(lowOgTitle.begin(), lowOgTitle.end(), lowOgTitle.begin(), ::tolower);
        transform(lowOgAuthor.begin(), lowOgAuthor.end(), lowOgAuthor.begin(), ::tolower);
        transform(lowOgCategory.begin(), lowOgCategory.end(), lowOgCategory.begin(), ::tolower);

        if ((Books[i].getTitle() == title || lowOgTitle == lowTitle) &&
            (Books[i].getAuthor() == author || lowOgAuthor == lowAuthor) &&
            (Books[i].getCategory() == category || lowOgCategory == lowCategory) &&
            !Books[i].isBorrowed()) return &Books[i];

    }
    cout << "Sorry, this book is not available right now!";
    return nullptr;
}

};

class Customer : public User {
private:
    book borrowedBooks[5];
    int  borrowedCount;

public:
    Customer(): User(0, "", ""), borrowedCount(0){}
    Customer(int id, const string& name, const string& pass): User(id, name, pass), borrowedCount(0){}

    void available_books(Library& libr) {
        libr.displayNonBorrowed();}
    void search_by_title(Library& libr, const string& title) {
        libr.searchByTitle(title);}
    void search_by_author(Library& libr, const string& author) {
        libr.searchByAuthor(author);}
    void search_by_category(Library& libr, const string& category) {
        libr.searchByCategory(category);}

    bool borrow_book(Library& libr,const string& title,const string& author,const string& category){
        if (borrowedCount >= 5) throw overflow_error("you can't borrow more than 5 books.\n");
          
        for (int i = 0; i < borrowedCount; i++) {
            if (borrowedBooks[i].getTitle() == title) {
                cout << "you already have " << title << ".\n";
                return false;
            }
        }
        libr.removeBooks(title);

        book b(title, author, category);
        b.setIsBorrowed(true);
        borrowedBooks[borrowedCount++] = b;

        cout << "Borrowed: " << title << "\n";
        return true;
    }

    bool return_book(Library& libr, const string& title) {
        int idx = -1;
        for (int i = 0; i < borrowedCount; i++) {
            if (borrowedBooks[i].getTitle() == title) {
                idx = i;
                break;
            }
        }
        if (idx < 0) {
            cout << "You have not borrowed " << title << ".\n";
            return false;
        }
        borrowedBooks[idx].setIsBorrowed(false);
        libr.addBooks(borrowedBooks[idx]);

        for (int j = idx; j + 1 < borrowedCount; j++) {
            borrowedBooks[j] = borrowedBooks[j + 1];
        }
        borrowedCount--;

        cout << "returned: " << title << "\n";
        return true;
    }

    void view_borrowed_books() const {
        cout << "\nMy borrowed books:\n";
        if (borrowedCount == 0) {
            cout << "  (none)\n";
            return;
        }
        for (int i = 0; i < borrowedCount; i++) {
            const book& b = borrowedBooks[i];
            cout << "  " << b.getAuthor()   << " " << b.getTitle()    << " " << b.getCategory() << "\n";
        }
    }

    int get_borrowed_count() const {
        return borrowedCount;
    }

    void show_customer_info() const {
        cout << "\nCustomer Information:\n" << "User ID: "  << getUserId()    << "\n"<< "Username: " << getUsername() << "\n"
        << "Borrowed: " << borrowedCount << "/5\n";
        view_borrowed_books();
    }
};

class Librarian : public User
{
private:
    Customer* customers;
    int customerCount, maxCustomers;

public:
    Librarian(int id, string name, string pass, int maxCust = 100) : User(id,name,pass)
    {
        customers = new Customer[maxCust];
        customerCount = 0;
        maxCustomers = maxCust;
    }
    ~Librarian() {delete[] customers;}

    bool addCustomer(int id, string name, string pass)
    {
        if (customerCount >= maxCustomers) throw overflow_error("Library is full, cannot add new customer");
            customers[customerCount] = Customer(id, name, pass);
            customerCount++;
            return true;
    }

    bool removeCustomer(int id)
    {
        bool customerFound = false;
        int newCustomerCount = 0;
        Customer* newCustomers = new Customer[maxCustomers];
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].getUserId() != id)
            {
                newCustomers[newCustomerCount] = customers[i];
                newCustomerCount++;
            }
            else customerFound = true;
        }

        delete[] customers;
        customers = newCustomers;
        customerCount = newCustomerCount;

        if (customerFound)
        {
            cout << "Customer removed successfully!" << endl;
            return true;
        }
        else
        {
            cout << "Customer not found" << endl;
            return false;
        }

    }

    void viewCustomerData(int id)
    {
        bool found = false;
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].getUserId() == id)
            {
                customers[i].show_customer_info();
                found = true;
                break;
            }
        }
        if (found == false)
        {
            cout << "Customer not found" << endl;
        }
    }

    void addBook(Library &libr, book b)
    {
        libr.addBooks(b);
        cout << "Book added successfully!" << endl;
    }

    void removeBook(Library &libr, string title)
    {
        libr.removeBooks(title);
        cout << "Book removed successfully!" << endl;
    }

    void viewAllBooks(Library &libr)
    {
        cout << "Library's books: " << endl;
        libr.displayBorrowedBooks();
        libr.displayNonBorrowed();
    }
    void viewBorrowedBooks(Library &libr) {libr.displayBorrowedBooks();}
    void viewNonBorrowedBooks(Library &libr) {libr.displayNonBorrowed();}

    void searchByTitle(Library &libr, string title) {libr.searchByTitle(title);}
    void searchByAuthor(Library &libr, string author) {libr.searchByAuthor(author);}
    void searchByCategory(Library &libr, string category) {libr.searchByCategory(category);}

    int getCustomerCount() const {return customerCount;}
    Customer &getSpecificCust(int index) {return customers[index];}

};

void librarianOptions(Library &libr, Librarian &librarian)
{
    int option;
    while (true)
    {
    int id;
    string title, author, category, name, password;

    cout << "1-Add book\n2-Remove book\n3-View all books\n4-View borrowed books\n5-View non borrowed books\n6-Add customer" << endl;
    cout << "7-Remove customer\n8-View customer data\n9-Search by title\n10-Search by author\n11-Search by category\n0-Logout" << endl;
    cout << "Choose an option: ";
    cin >> option;
    cin.ignore();

    if (option == 1)
    {
        cout << "Enter the book's name: ";
        getline(cin, title);
        cout << "Enter book's author: ";
        getline(cin, author);
        cout << "Enter book's category: ";
        cin >> category;
        try {librarian.addBook(libr, book(title,author,category));}
        catch(overflow_error& error)
        {
            cout << error.what() << endl;
        }
    }
    else if (option == 2)
    {
        cout << "Enter the book's name: ";
        getline(cin, title);
        libr.removeBooks(title);
    }
    else if (option == 3) librarian.viewAllBooks(libr);
    else if (option == 4) librarian.viewBorrowedBooks(libr);
    else if (option == 5) librarian.viewNonBorrowedBooks(libr);
    else if (option == 6)
    {
        cout << "Enter customer's name: ";
        getline(cin, name);
        cout << "Enter customer's id: ";
        cin >> id;
        cout << "Enter customer's password: ";
        cin >> password;
        try {librarian.addCustomer(id, name, password);}
        catch(overflow_error& error)
        {
            cout << error.what() <<endl; 
        }
       
        cout << "Customer added successfully to the library!" << endl;
    }
    else if (option == 7)
    {
        cout << "Enter customer's id: ";
        cin >> id;
        librarian.removeCustomer(id);
    }
    else if (option == 8)
    {
        cout << "Enter customer's id: ";
        cin >> id;
        librarian.viewCustomerData(id);
    }
    else if (option == 9)
    {
        cout << "Enter the book's name: ";
        getline(cin, title);
        librarian.searchByTitle(libr, title);
    }
    else if (option == 10)
    {
        cout << "Enter book's author: ";
        getline(cin, author);
        librarian.searchByAuthor(libr, author);
    }
    else if (option == 11)
    {
        cout << "Enter book's category: ";
        cin >> category;
        librarian.searchByCategory(libr, category);
    }
    else if (option == 0)
    {
        cout << "Logged out" << endl;
        break;
    }
    else cout << "Invalid input" << endl;

    }
}

void customerOptions(Library &libr, Customer &customer)
{
    int option;
    while (true)
    {
        string title, author, category;

        cout << "1-View available books\n2-Search by title\n3-Search by author\n4-Search by category\n5-Borrow a book\n6-Return a book" << endl;
        cout << "7-View borrowed books\n8-Show customer info\n0-Logout" << endl;
        cin >> option;
        cin.ignore();

        if (option == 1) customer.available_books(libr);
        else if (option == 2)
        {
            cout << "Enter book's name: ";
            getline(cin, title);
            customer.search_by_title(libr, title);
        }
        else if (option == 3)
        {
            cout << "Enter the author's name: ";
            getline(cin, author);
            customer.search_by_author(libr, author);
        }
        else if (option == 4)
        {
            cout << "Enter the category: ";
            getline(cin, category);
            customer.search_by_category(libr, category);
        }
        else if (option == 5)
        {
            cout << "Enter book's name: ";
            getline(cin, title);
            cout << "Enter the author's name: ";
            getline(cin, author);
            cout << "Enter the category: ";
            getline(cin, category);
            try {customer.borrow_book(libr, title, author, category);}
            catch(overflow_error& error)
            {
                cout << error.what() << endl;
            }
        }
        else if (option == 6)
        {
            cout << "Enter book's name: ";
            getline(cin, title);
            customer.return_book(libr, title);
        }
        else if (option == 7) customer.view_borrowed_books();
        else if (option == 8) customer.show_customer_info();
        else if (option == 0)
        {
            cout << "Logged out" << endl;
            break;
        }
        else cout << "Invalid input" << endl;

    }
}

void login(Library &libr, Librarian &librarian)
{
    while (true){
    string password, username;
    cout << "Welcome to our library :)" << endl;
    cout << "Please enter you username: ";
    getline(cin, username);
    cout << "Please enter your password: ";
    cin >> password;
    cin.ignore();

    if (librarian.login(username, password))
    {
        cout << "Welcome admin!";
        librarianOptions(libr, librarian);
        break;
    }
    for (int i = 0; i < librarian.getCustomerCount(); i++)
    {
        if (librarian.getSpecificCust(i).login(username, password))
        {
            cout << "Welcome " << username << "!";
            customerOptions(libr, librarian.getSpecificCust(i));
            break;
        }
    }
    }
}

int main()
{
    Library libr(100);
    Librarian librarian(100, "admin", "admin123");

    librarian.addCustomer(101, "Yousef", "yousef1");
    librarian.addCustomer(102, "Reda" , "reda2");
    librarian.addCustomer(103, "Taha", "taha3");
    librarian.addCustomer(104, "Mostafa", "sasa4");
    librarian.addCustomer(105, "Adham", "adham5");

    libr.addBooks(book("Harry Potter", "JK Rowling", "Fantasy"));
    libr.addBooks(book("The idiot brain", "Dean Burnett", "Science"));
    libr.addBooks(book("Oliver Twist", "Charles Dickens", "fiction"));
    libr.addBooks(book("Great expectations", "Charles Dickens", "fiction"));
    libr.addBooks(book("The Hobbit", "Tolkien", "Fantacy"));

    login(libr, librarian);

    return 0;
}