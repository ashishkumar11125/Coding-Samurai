#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class BookEntry
{
public:
    string bookName;
    string bookAuthor;
    string publisher;
    int ISBN;
    int edition;
    int publishYear;
    int numberOfBooks;
    vector<BookEntry> books; // Store multiple books

    void registerBook();
    void printData();
    void saveBookDataToFile(const string &filename);
};

class MemberEntry
{
public:
    string memberName;
    string memberAddress;
    string memberEmail;
    int memberID;

    void registerMember();
    void saveMemberDataToFile(const string &filename);
    bool isMemberExist(const string &filename);
};

void BookEntry::registerBook()
{
    cout << "Enter the number of Books this time:\n";
    cin >> numberOfBooks;

    for (int i = 0; i < numberOfBooks; ++i)
    {
        cout << "===============================\n";
        cout << "     CLI for Book Entry\n";
        cout << "===============================\n";
        cout << "Enter the Name of the Book: ";
        cin >> bookName;
        cout << "Enter the Author of the Book: ";
        cin >> bookAuthor;
        cout << "Enter the Publisher: ";
        cin >> publisher;
        cout << "Enter the ISBN number of the Book: ";
        cin >> ISBN;
        cout << "Enter the Edition (numbers only): ";
        cin >> edition;

        // Create a book object and add it to the vector of books
        BookEntry book;
        book.bookName = bookName;
        book.bookAuthor = bookAuthor;
        book.publisher = publisher;
        book.ISBN = ISBN;
        book.edition = edition;
        books.push_back(book);
    }
}

void BookEntry::printData()
{
    cout << "=========================================\n";
    cout << "           Books in Library\n";
    cout << "=========================================\n";

    if (books.empty())
    {
        cout << "No books available.\n";
        return;
    }

    cout << left << setw(6) << "S.No"
         << setw(25) << "Title"
         << setw(25) << "Author"
         << setw(25) << "Publication"
         << setw(15) << "ISBN"
         << setw(10) << "Edition"
         << "\n";

    for (int i = 0; i < books.size(); i++)
    {
        if (i >= books.size() - numberOfBooks)
            cout << left << setw(6) << i + 1 << "*"
                 << setw(25) << books[i].bookName
                 << setw(25) << books[i].bookAuthor
                 << setw(25) << books[i].publisher
                 << setw(15) << books[i].ISBN
                 << setw(10) << books[i].edition
                 << "\n";
        else
            cout << left << setw(6) << i + 1
                 << setw(25) << books[i].bookName
                 << setw(25) << books[i].bookAuthor
                 << setw(25) << books[i].publisher
                 << setw(15) << books[i].ISBN
                 << setw(10) << books[i].edition
                 << "\n";
    }
}

void BookEntry::saveBookDataToFile(const string &filename)
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    outputFile << "Books in Library\n";
    outputFile << "=========================================\n";
    outputFile << left << setw(6) << "S.No"
               << setw(25) << "Title"
               << setw(25) << "Author"
               << setw(25) << "Publication"
               << setw(15) << "ISBN"
               << setw(10) << "Edition"
               << "\n";

    for (int i = 0; i < books.size(); i++)
    {
        if (i >= books.size() - numberOfBooks)
            outputFile << left << setw(6) << i + 1 << "*"
                       << setw(25) << books[i].bookName
                       << setw(25) << books[i].bookAuthor
                       << setw(25) << books[i].publisher
                       << setw(15) << books[i].ISBN
                       << setw(10) << books[i].edition
                       << "\n";
        else
            outputFile << left << setw(6) << i + 1
                       << setw(25) << books[i].bookName
                       << setw(25) << books[i].bookAuthor
                       << setw(25) << books[i].publisher
                       << setw(15) << books[i].ISBN
                       << setw(10) << books[i].edition
                       << "\n";
    }

    cout << "Book data saved to file: " << filename << endl;

    outputFile.close();
}

void MemberEntry::registerMember()
{
    cout << "===============================\n";
    cout << "     CLI for Member Entry\n";
    cout << "===============================\n";
    cout << "Enter the Name of the Member: ";
    cin >> memberName;
    cout << "Enter the Address of the Member: ";
    cin >> memberAddress;
    cout << "Enter the Email of the Member: ";
    cin >> memberEmail;
    cout << "Enter the Member ID: ";
    cin >> memberID;
}

void MemberEntry::saveMemberDataToFile(const string &filename)
{
    ofstream outputFile(filename, ios::app);

    if (!outputFile.is_open())
    {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    outputFile << "Member Details\n";
    outputFile << "=========================================\n";
    outputFile << "Name: " << memberName << endl;
    outputFile << "Address: " << memberAddress << endl;
    outputFile << "Email: " << memberEmail << endl;
    outputFile << "Member ID: " << memberID << endl;
    outputFile << "--------------------------------------" << endl;

    cout << "Member data saved to file: " << filename << endl;

    outputFile.close();
}

bool MemberEntry::isMemberExist(const string &filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Failed to open the file: " << filename << endl;
        return false;
    }

    string line;
    string searchName = "Name: " + memberName;
    string searchEmail = "Email: " + memberEmail;

    while (getline(inputFile, line))
    {
        if (line.find(searchName) != string::npos || line.find(searchEmail) != string::npos)
        {
            cout << "Member already exists.\n";
            inputFile.close();
            return true;
        }
    }

    inputFile.close();
    return false;
}

class Options : public BookEntry, public MemberEntry
{
public:
    void options();
};

void Options::options()
{
    char opts; // Change the data type to char
    bool running = true;

    while (running)
    {
        cout << "===============================\n";
        cout << "      CLI for Options\n";
        cout << "===============================\n";
        cout << "1. To make an Entry of Book\n";
        cout << "2. To Issue Book \n";
        cout << "3. Register a Member \n";
        cout << "Press Esc key to exit\n";
        cin >> opts;

        switch (opts)
        {
        case '1': 
            registerBook();
            printData();
            saveBookDataToFile("book_data.txt");
            break;
        case '2':
            cout << "Issuing the book...\n";
            break;
        case '3':
            registerMember();
            if (!isMemberExist("member_data.txt"))
                saveMemberDataToFile("member_data.txt");
            break;
        case 27:
            running = false;
            break;
        default:
            cout << "Invalid option\n";
            break;
        }
    }
}

int main()
{
    Options op;
    op.options();

    return 0;
}