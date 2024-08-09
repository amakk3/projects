/*-------------------------------------------
Program 1: Library Management Menu
Course: CS 251, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */

// You cannot use any libraries beyond the ones we have given below.
// You must use output streams, file streams, vectors, and strings.
// You are not allowed to use any other containers or objects.
// You may not use structs, pointers, or dynamic memory allocations.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition
void printMenu();
void checkfile(fstream& data, string& file_name); //check if file is open and exists
void add_to_lib(vector<vector<string>>& library, string name, string isbn, int& book_count); //add single entry into database
void display_lib(vector<vector<string>>& library); //displays database
void clear_lib(vector<vector<string>>& library, int& book_count); //wipes data from 2D vector
void load_lib(vector<vector<string>>& library, int& book_count); //loads and parses data from files
void output_tofile(vector<vector<string>>& library); //creates an output file with database
void print_stats(vector<vector<string>>& library, int& book_count); //prints number of books
void search(vector<vector<string>>& library); // searches for books in database
string get_status(vector<vector<string>>& library, string input); //helper function to retrieve status string of a book
void remove(vector<vector<string>>& library, int& book_count); //removes entry from database
void list_I(vector<vector<string>>& library, int& book_count); //lists all invalid entries in database
int main()
{
    string command;
    vector<vector<string>> library; //main 2D vector storage
    string book_title;// temporary refernce variable for add_to_lib function
    string book_ISBN; // temporary refernce variable for add_to_lib function
    int book_count = 0; //refered to variable keeping track of the books in database
    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        // We use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;

        switch (toupper(command[0])) //switch case to execute functions cleanly
        {
        case 'A':
            add_to_lib(library, book_title, book_ISBN, book_count);
            break;
        case 'D':
            display_lib(library);
            break;
        case 'C':
            clear_lib(library, book_count);
            break;
        case 'L':
            load_lib(library, book_count);
            break;
        case 'O':
            output_tofile(library);
            break;
        case 'P':
            print_stats(library, book_count);
            break;
        case 'S':
            search(library);
            break;
        case 'R':
            remove(library, book_count);
            break;
        case 'I':
            list_I(library, book_count);
            break;
        }
        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}

// Function definitions for all the glorious function decomposition
// Tip: alphabetical order makes it easy to find things if you have
//      a lot of function decomposition.

/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;
    cout << "S - Search For A Library Entry" << endl;
    cout << "X - Exit Program" << endl;
}
void add_to_lib(vector<vector<string>>& library, string name, string isbn, int& book_count) {
    cout << "What is the book title? ";
    getline(cin, name);
    for (int i = 0; i < name.length(); ++i) { //check for commans in book title, else invalid
        if (name[i] == ',') {
            cout << endl << "The book title cannot contain commas." << endl;
            return;
        }
    }
    cout << endl << "What is the 13-digit ISBN (with hyphens)? ";
    getline(cin, isbn);
    vector<string> attributes(4);//vector<string> attributes{Book_Title, ISBN, Checkout Status, Invalid/Valid}
    library.push_back(attributes); //fill out specific vector with attributes
    library.at(library.size() - 1).at(0) = name;
    library.at(library.size() - 1).at(1) = isbn;
    library.at(library.size() - 1).at(2) = "0";
    cout << endl << "The Following Entry Was Added" << endl;
    cout << "-----------------------------" << endl;
    cout << name << " --- " << isbn << " --- " << "In Library" << endl;
    book_count += 1;
}
void display_lib(vector<vector<string>>& library) {
    cout << "Your Current Library" << endl << "--------------------" << endl;
    if (library.empty()) { // check if library is empty
        cout << "The library has no books." << endl;
    }
    for (int i = 0; i < library.size(); ++i) { // go through library to print out each attribute
        for (int j = 0; j < library[i].size() - 2; ++j) { //print attributes except the status number
            cout << library[i][j] << " --- ";
        }
        // cout << endl << library[i][2] << endl;
        if (library[i][2] == "0") { //branch to print out string status based on status number in vector
            cout << "In Library" << endl;
        }
        else if (library[i][2] == "1") {
            cout << "Checked Out" << endl;
        }
        else if (library[i][2] == "2") {
            cout << "On Loan" << endl;
        }
        else if (library[i][2] == "3") {
            cout << "Unknown State" << endl;
        }
        else {
            cout << "Invalid State" << endl;
        }
    }
    // cout << endl;
}
void clear_lib(vector<vector<string>>& library, int& book_count) {
    library.clear();
    cout << "Your library is now empty." << endl; //clear library and reset book count
    book_count = 0;
}
void load_lib(vector<vector<string>>& library, int& book_count) {
    fstream data;
    vector<string> attributes(4);
    int comma_count, idx1, idx2, idx3; //variables to splice the line from file 
    int ln_count = 0;
    string name, isbn, status, file_name, line, valid; //attribute names to fill into vectors
    cout << "What database to read from? ";
    getline(cin, file_name);
    data.open(file_name);
    if (data.is_open() == true) {
        while (getline(data, line)) {
            idx1 = line.find(','); // splice string into substrings based on the position of the commas
            idx2 = line.find(',', idx1 + 1);
            idx3 = line.find(',', idx2);
            name = line.substr(0, idx1);
            isbn = line.substr(idx1 + 1, (idx2 - idx1 - 1));
            if (isspace(isbn.at(0))) { //delete any potential whitespace in the beginning of isbn
                isbn.erase(0, 1);
            }
            status = line.substr(line.size() - 1);
            ln_count += 1; //counting lines to add to books later on
            library.push_back(attributes); //add a entry with space
            if (idx1 == -1 || idx2 == -1 || idx3 == -1) { //checking bad inputs that lack commas
                library.at(library.size() - 1).at(3) = "F"; //invalid if any input is bad
                if (idx2 == -1) { //fix default status on bad input
                    status = "0";
                }
                if (idx1 == -1) { //fix default isbn on bad input
                    isbn = "000-0-00-000000-0";
                }
            }
            else {
                library.at(library.size() - 1).at(3) = "T"; //if commas are intact, input is clean
            }
            library.at(library.size() - 1).at(2) = status; //fill in vector entry
            library.at(library.size() - 1).at(1) = isbn;
            library.at(library.size() - 1).at(0) = name;
        }
        cout << endl << "Read in " << ln_count << " lines from the file." << endl;
    }
    else {
        cout << endl << "Could not find the database file." << endl;
    }
    data.close();
    book_count += ln_count;
}
void output_tofile(vector<vector<string>>& library) {
    string input;
    ofstream out_file;
    cout << "Where should the database output to? ";
    getline(cin, input);
    out_file.open(input); //open new file based on input name
    for (int i = 0; i < library.size(); ++i) { //iterate through 2D vector database to print out all entries
        for (int j = 0; j < library[i].size() - 1; ++j) {
            out_file << library[i][j];
            if (!(library[i][j].size() == 1)) {
                out_file << ", ";
            }
        }
        out_file << endl;
    }
    out_file.close();
}
void print_stats(vector<vector<string>>& library, int& book_count) {
    int inlib, checkout, onloan, unknown, other; //attributes based on the status number
    inlib = checkout = onloan = unknown = other = 0;
    for (int i = 0; i < library.size(); ++i) { //counting the status numbers of each as encountered
        if (library[i][2] == "0") {
            inlib += 1;
        }
        else if (library[i][2] == "1") {
            checkout += 1;
        }
        else if (library[i][2] == "2") {
            onloan += 1;
        }
        else if (library[i][2] == "3") {
            unknown += 1;
        }
        else {
            other += 1;
        }
    }//print out statuses of books
    cout << "Your Current Library's Stats" << endl << "----------------------------" << endl;
    cout << "Total Books: " << book_count << endl;
    cout << "   In Library: " << inlib << endl;
    cout << "   Checked Out: " << checkout << endl;
    cout << "   On Loan: " << onloan << endl;
    cout << "   Unknown: " << unknown << endl;
    cout << "   Other: " << other << endl;
}
void search(vector<vector<string>>& library) {
    string input;
    string status;
    cout << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, input);
    if (input == "1") { //check by name choice
        cout << endl << "Enter the book name: ";
        getline(cin, input);
        cout << endl << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        for (int i = library.size() - 1; i >= 0; i -= 1) { //iterate to print out proper entry
            if (library[i][0] == input) {
                status = get_status(library, input); //convert status number in 2D vector to a string to print out
                cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
                return; //exit function once printed
            }
        }
        cout << "No matching entry found in the library." << endl;
    }
    else if (input == "2") {
        cout << endl << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, input);
        cout << endl << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        for (int i = library.size() - 1; i >= 0; i -= 1) {//iterate to print out proper entry
            if (library[i][1] == input) {
                status = get_status(library, input);//convert status number in 2D vector to a string to print out
                cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
                return; //exit function once printed
            }
        }
        cout << "No matching entry found in the library." << endl; // edge case for no entry found
    }
    else {
        cout << endl << "Invalid search by choice option." << endl; //edge case for invalid option
    }
}
string get_status(vector<vector<string>>& library, string input) {
    int i = 0;
    string status;
    for (i = 0; i < library.size(); ++i) {
        if (library[i][0] == input || library[i][1] == input) { //helper function to return a status string based on status number in vector database
            if (library[i][2] == "0") {
                status = "In Library";
            }
            else if (library[i][2] == "1") {
                status = "Checked Out";
            }
            else if (library[i][2] == "2") {
                status = "On Loan";
            }
            else if (library[i][2] == "3") {
                status = "Unknown State";
            }
            else {
                status = "Invalid State";
            }
        }
    }
    return status;
}
void remove(vector<vector<string>>& library, int& book_count) {
    string input;
    string status;//hold status string format
    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, input);
    if (input == "1") { //search by name
        cout << endl << "Enter the book name: ";
        getline(cin, input);
        cout << endl << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;
        for (int i = library.size() - 1; i >= 0; i -= 1) { //iterate through vector to find book
            if (library[i][0] == input) { //check if entry is right
                status = get_status(library, input); // get status in string form
                cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
                library.erase(library.begin() + i); //delete space vector
                book_count -= 1;
                return; //terminate after decrementing 
            }
        }
        cout << "No matching entry found in the library." << endl;
    }
    else if (input == "2") { //search by isbn
        cout << endl << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, input);
        cout << endl << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;
        for (int i = library.size() - 1; i >= 0; i -= 1) { //iterate until chosen isbn is found and delete
            if (library[i][1] == input) {
                status = get_status(library, input);
                cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
                library.erase(library.begin() + i);
                book_count -= 1;
                return; //terminate after decrementing
            }
        }
        cout << "No matching entry found in the library." << endl; //edge case for no book found
    }
    else {
        cout << endl << "Invalid remove by choice option." << endl; //edge case for invalid choice
    }
}
void list_I(vector<vector<string>>& library, int& book_count) {
    bool invalid = false; //boolean to prevent edgecases from printing nothing
    cout << "The Following Library Entries Have Invalid Data" << endl;
    cout << "-----------------------------------------------" << endl;
    if (book_count == 0) { //edge case for empty library
        cout << "The library has no books." << endl;
        invalid = true;
    }
    int digit_num = 0; //counting numbers, hyphens, and such to prevent edgecases in isbn
    int total = 0;
    string clean_isbn = ""; //get clean isbn string to make calculations easier
    string status;
    for (int i = 0; i < library.size(); ++i) { //iterate over library for each isbn
        for (int j = 0; j < library[i][1].size(); ++j) {
            if (isdigit(library[i][1][j])) { //get clean isbn from each entry
                digit_num += 1;
                clean_isbn += library[i][1][j];
            }
            if (isspace(library[i][1][j])) {
                library[i][1].erase(j);
                invalid = true;
            }
        }
        if (stoi(library[i][2]) > 3) { //edge case for incorect status number
            invalid = true;
            status = get_status(library, library[i][0]);
            cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
        }
        else if (digit_num > 13 || digit_num < 13) { //edge cases for correct amount of digits
            invalid = true;
            status = get_status(library, library[i][0]);
            cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
        }
        else {
            for (int k = 0; k < clean_isbn.size() - 1; ++k) { //else the calculation for a proper isbn
                if (k % 2 != 0) { //algorithm for isbn calculation
                    total += (int(clean_isbn[k]) - '0') * 3;
                }
                else {
                    total += (int(clean_isbn[k]) - '0') * 1;
                }
            }
            total = total % 10;
            if (total == 0) {
                total = 10;
            }
            total = 10 - total;
            if (total != clean_isbn[clean_isbn.size() - 1] - '0') { //check if final isbn number matches to algorithm output
                invalid = true;
                status = get_status(library, library[i][0]);
                cout << library[i][0] << " --- " << library[i][1] << " --- " << status << endl;
            }
        }
        total = 0; //reset checker variables for next entry
        clean_isbn = "";
        digit_num = 0;
    }
    if (invalid == false) { //edge case for empty invalid list
        cout << "The library has no invalid entries." << endl;
    }
}
