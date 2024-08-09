#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

const int NMISP = 5;
const int RNG_RANGE = 100;

void
display_header(const int ndict, const int nmiss)
{
    // Parameters:
    //     int ndict -> the number of words in the full dictionary
    //     int nmiss -> the number of word pairs in the misspelled
    //                  dataset.
    // */
    cout << "*** Typing Tutor" << endl;
    cout << "There are " << ndict << " words in the dictionary." << endl;
    cout << "There are " << nmiss << " commonly misspelled words." << endl;

}

void
display_menu_options()
{

    cout << endl << "*** Select a menu option:" << endl
         << "1. Spell commonly misspelled words" << endl
         << "2. Type random words from the full dictionary" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in the dictionary" << endl
         << "5. Exit the program." << endl
         << "Your choice: ";
}

vector<int>
randn(const int n, const int max)
{
    // Parameters:
    //     int n -> the number of random numbers to generate
    //     int max -> the maximum random number, random numbers are drawn
    //                 from between [0, max]

    // Returns:
    //     a vector that contains n random numbers between [0, max]
    // */
    vector<int> temp;
    for (int i = 0; i < n; ++i) { // put random numbers in a vector
        int randnum = rand() % (max + 1);
        temp.push_back(randnum);
    }
    return temp;
}

ifstream
open(const string& src_file) //open file function
{
    ifstream src{src_file};
    if (!src.is_open()) {
        cout << "Could not find file " << src_file << "." << endl;
        exit(1);
    }
    return src;
}

void
extract_dict(vector<string>& dst, const string& src_file)
{

    // Parameters:
    //     dst -> an empty vector (of strings), passed by reference,
    //            that  you  will  store  every line  of the file in
    //            (each line is one element in the file).

    //     src_file -> a string, passed by reference, that you are not
    //                 allowed to change  (const),  that is simply the
    //                 name of the file.
    ifstream dict_file;
    dict_file.open(src_file);
    if (!dict_file.is_open()) {
        cout << "FILE NOT OPEN" << endl;
    }
    string temp;
    for (string line; getline(dict_file, line);) {
        dst.push_back(line);    
    }
}

void
extract_misspelled(vector<string>& misspelled, vector<string>& correct,
                    const string& src_file)
{
    // Parameters:
    //     misspelled -> an  empty vector (strings),  passed by reference,
    //                   that you will store the misspelled words in.

    //     correct -> an empty vector (strings), passed by reference, that
    //                you will store the correct version of the words in.

    //     src_file -> a string, passed by reference, that you are not
    //                 allowed to change  (const),  that is simply the
    //                 name of the file.

    ifstream mspell_file; // open file
    mspell_file.open(src_file);
    if (!mspell_file.is_open()) {
        cout << "FILE NOT OPEN" << endl;
    }
    string temp1;
    bool c = false; // bool to determine which list word goes into
    for (string line; getline(mspell_file, line);) {
        // cout << line << "  \n";
        line.push_back('\n');
        for (int i = 0; i < int(line.size()); ++i) { // for each space in input, break it up 
            if (!isspace(line.at(i))) {
                temp1.push_back(line.at(i)); //build word
            }
            else if (isspace(line.at(i))) {
                if (c == true) {
                    correct.push_back(temp1); // add word to list
                    temp1 = "";
                    c = false;
                } else {
                    misspelled.push_back(temp1);
                    temp1 = "";
                    c = true;
                    
                }
            }
        }
        
    }
    
}

void
display_elems(const vector<string>& src, const vector<int>& positions)
{
    // Parameters:
    //     src -> a vector (strings), passed by reference, that is not
    //            allowed to be modified (const), which holds the data
    //            that is to be printed

    //     positions -> a vector (int), passed by reference, that is not
    //                  allowed to be modified (const),  which holds the
    //                  indices for elements in src to print.
    // */
    for (int j = 0; j < positions.size(); ++j) { //print out each word at position
        cout << src[positions[j]];
        if (j < positions.size()) {
            cout << " ";
        }
    }
    cout << endl;
}

void
extract_spelling_answers(vector<string>& dst, const vector<string>& correct,
                            const vector<int> positions)
{
    // Parameters:
    //     dst -> an empty vector (of strings), passed by reference, that
    //            you will copy the specific elements from correct into.

    //     correct -> a vector (strings), passed by reference, that is not
    //                allowed to be modified (const), which holds the data
    //                that is to be copied over to dst

    //     positions -> a vector (int), passed by reference, that is not
    //                  allowed to be modified (const),  which holds the
    //                  indices of the elements in correct to copy over

    for (int k = 0; k < positions.size(); ++k) {
        dst.push_back(correct[positions[k]]);
    }
    
}

void
extract_spelling_mistakes(vector<string>& dst, const string& to_grade,
                const vector<string>& correct)
{
    // Parameters:
    //     dst -> an empty vector (of strings), passed by reference, that you
    //     will fill with strings that represent spelling errors  (mispelling
    //     -> correct spelling) (see Hints)

    //     to_grade -> a string, passed  by reference,  that is not allowed to
    //                 be modified (const) that holds the user's typed answer.

    //     correct -> a vector (strings), passed by reference, that is not
    //                allowed to be modified (const), which holds the correct
    //                answers. (one vector element -> one word)
    vector<string> user_input;
    string temp;
    for (int l = 0; l < int(to_grade.size()); ++l) { //add all the words typed by user into vector
        if (!isspace(to_grade.at(l))) {
            temp.push_back(to_grade.at(l));
        } else if (isspace(to_grade.at(l))) {
            user_input.push_back(temp);
            temp = "";
        }
    }
    user_input.push_back(temp);

    for (int m = 0; m < user_input.size(); ++m) { //print out comparison of user input and correct words
        if (correct[m] != user_input[m]) {
            dst.push_back(user_input[m] + " -> " + correct[m]);
        }
    }
}

void
report_misspell_mistakes(const vector<string>& mistakes,
                            const int num_words)
{
    // Parameters:
    //     mistakes -> a vector (strings), passed by reference, that is
    //                 not allowed  to be modified  (const),  and holds
    //                 the messages about  misspellings that we want to
    //                 report to the user.

    //     num_words -> an integer, that is not allowed to be modified
    //                  (const),  which is  the total number  of words
    //                  being tested
    // */
    if (mistakes.size() > 0) { // if there are mistakes 
        cout << "Misspelled words:" << endl;

    } else if (mistakes.size() == 0) { // if there are no mistakes
        cout << "No misspelled words!" << endl;
    }
    for (int u = 0; u < mistakes.size(); u++) { //print mistakes
        cout << "    " << mistakes[u] << endl;
    }
    int plus_p = num_words - mistakes.size(); //calculate positive and negative scores
    int minus_p = mistakes.size();
    cout << plus_p * 3 <<" points: " << plus_p << " spelled correctly x 3 points for each." << endl;
    cout << minus_p * 6 <<" point penalty: " << minus_p << " spelled incorrectly x -6 points for each." << endl;
    cout << "Score: " << (plus_p * 3 - minus_p * 6) << endl;
}

void
evaluate_user_misspells(const vector<string>& src, const vector<int>& positions)
{
    // Parameters:
    //     src -> a vector (strings), passed by reference, that is not
    //            allowed to be modified (const), which holds the data
    //            that the user is being tested on.

    //     positions -> a vector (int), passed by reference, that is not
    //                  allowed to be modified (const),  which holds the
    //                  indices of the elements in correct to copy over
    vector<string> spell_ans;
    extract_spelling_answers(spell_ans, src, positions); //get spelling answers
    string sub;
    getline(cin, sub);
    vector<string> spell_mist;
    extract_spelling_mistakes(spell_mist, sub, spell_ans); // determine wrong mistakes
    report_misspell_mistakes(spell_mist, spell_ans.size()); // output wrong mistakes and scores

    
    
}

void
misspelled(const vector<string>& mspelled, const vector<string>& correct)
{
    // Parameters:
    //     mspelled -> a vector (string) where each element is one
    //                 mispelled word from the data set

    //     correct -> a vector (string) where each element is a
    //                correctly spelled word from the data set
    vector<int> random_nums = randn(5, mspelled.size() - 1); //intiate random vector
    cout << endl;
    cout << "*** Using commonly misspelled words." << endl;
    display_elems(mspelled, random_nums); //display words
    cout << "Type the words above with the correct spelling:" << endl;
    evaluate_user_misspells(correct, random_nums); // correct mistakes 
}

void
full_dict(const vector<string>& dict)
{
    // Parameters:
    //     dict -> a vector (string), passed by reference, where
    //             each element is one word from the full
    //             dictionary.
    cout << endl;
    cout << "*** Using full dictionary." << endl;
    vector<int> random_nums2 = randn(5, dict.size() - 1); //initate random vector
    display_elems(dict, random_nums2);
    cout << "Correctly type the words above:" << endl;
    evaluate_user_misspells(dict, random_nums2);  // correct mistakes 
}

void
display_words_prompt()
{
    // This displays the data set choices for menu option 3
    cout << endl << "*** Displaying word list entries." << endl
         << "Which words do you want to display?" << endl
         << "A. Dictionary of all words" << endl
         << "B. Commonly misspelled words (wrongly spelled)" << endl
         << "C. Commonly misspelled words (correctly spelled)" << endl
         << "Your choice: ";
}

void
print_range(const vector<string>& data)
{
    // Parameters:
    //     data -> a vector (string),  passed by reference, that cannot be
    //             modified (const), which holds the all the data (and the
    //             user will print some of it in a range)
    int start;
    int end;
    if (data.size() > 115) { //determine if data is dict
        cout << "*** Enter the start and end indices between 0 and 263532: ";
        cin >> start;
        cin >> end;
        if (start > end || start < 0) { //error handler for improper index
            cout << "The end index must come after the start, and the indices must be in range." << endl;
        } else {
            for (int i = start; i < end + 1; ++i) { //print data
                cout << i << ". " << data[i] << endl;
            }            
        }
    } else { //otherwise it is the misspelled list
        cout << "*** Enter the start and end indices between 0 and 113: ";
        cin >> start;
        cin >> end;
        if (start > end || start < 0) { //error handler for improper index
            cout << "The end index must come after the start, and the indices must be in range." << endl;
        } else {
            for (int i = start; i < end + 1; ++i) {
                cout << i << ". " << data[i] << endl; //print data
            }            
        }
    }
}

void
display_in_range(const vector<string>& dict, const vector<string>& mspelled,
                const vector<string>& correct)
{
    // Parameters:
    //     dict -> a vector (string),  passed by reference, that cannot be
    //             modified (const), which holds the all the data from the
    //             full dictionary

    //     mspelled -> a vector (string), passed by reference, that cannot
    //                 be modified (const),  which holds the all the miss-
    //                 pelled words

    //     correct -> a vector (string), passed by reference, that cannot
    //                be modified (const),  which holds the all the words
    //                with correct spelling
    display_words_prompt();
    char choice;
    cin >> choice;
    choice = toupper(choice);
    switch (choice) { //direct function based on user choice
        case 'A':
            print_range(dict);
            break;
        case 'B':
            print_range(mspelled);
            break;
        case 'C':
            print_range(correct);
            break;        
    }
    
}

void
bsearch(const vector<string>& data)
{
    // // Parameters:
    // //     data -> a vector (string),  passed by reference, that cannot be
    // //             modified (const), which holds the all the data from the
    // //             full dictionary
    string input;
    cout << "*** Enter word to search: ";
    getline(cin, input);
    int size = data.size();
    int start = 0, mid, elem;
    int counter = 0; // make sure alignment is right and numbering
    int yes = 0; // determine what found message to print
    do {
        mid = (start + size) / 2;
        string elem = data[mid];
        counter += 1;
        if (counter < 10) { //fix alignment based on numbers
            cout << "    ";
        } else {
            cout << "   ";
        }
        cout << counter <<". Comparing to: " << data[mid] << endl; //print the word at mid index
        if (elem < input){
            start = mid + 1;
        } else if (elem > input) {
            size = mid;
        } else { // element found
            yes = 1;
            cout << input << " was found." << endl;
            return;
        }
    } while (start < size);
    if (yes != 1) { // element not found
        cout << input << " was NOT found." << endl;
    }
}

void
extract_all_data(vector<string>& dict, vector<string>& mspelled,
                    vector<string>& correct)
{
    extract_dict(dict, "dictionary.txt");
    extract_misspelled(mspelled, correct, "misspelled.txt");
}

int
main()
{
    srand(1);
    vector<string> dict, mspelled, correct;
    extract_all_data(dict, mspelled, correct);
    display_header(dict.size(), correct.size());
    unsigned int choice;
    do {
        display_menu_options();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            misspelled(mspelled, correct);
            break;
        case 2:
            full_dict(dict);
            break;
        case 3:
            display_in_range(dict, mspelled, correct);
            break;
        case 4:
            bsearch(dict);
            break;
        case 5:
            cout << "Exiting." << endl;
            break;
        default:
            cout << "No menu option " << choice << ". "
                 << "Please try again." << endl;
        }
    } while ((choice != 5) && !cin.eof());

    return 0;
}
