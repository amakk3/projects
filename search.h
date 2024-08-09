
#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

//This function takes in a string and cleans out all the beginning and trailing punctuation
//that would be in the way, the returned string starts with a letter and ends with a letter
string cleanToken(string s) {
    if (s == "") { // edge case to catch any empty strings
        return "";
    }
    string clean_string = ""; //string to build up with clean token
    int i = s.size() - 1;
    char last_letter;
    int letter_counter = 0;
    bool contains_letter = false; //if word contains letter, makes sure to continue to build it from the front loop
    while (i > -1) { //loop from back of string until first letter is reached
        if (isalpha(s[i]) || isdigit(s[i]) || !ispunct(s[i])) { //once alpha is reached, put last letter into temp var
            last_letter = tolower(s[i]);
            contains_letter = true;
            break;
        }
        i--;
    }
    bool first_reached = false; // if first letter is reached, continue to collect rest of characters until final character
    int j = 0;
    while (j < s.size() && j != i) { //loop through front of string
        if (isalpha(s[j]) || first_reached || isdigit(s[j]) || static_cast<unsigned char>(s[j]) > 127) { //when first char is reached, continue to add to clean string
            clean_string += tolower(s[j]);
            first_reached = true; //set both bools to true to properly return clean_string later
            contains_letter = true;
        }
        j++;
    }
    for (int i = 0; i < s.size(); i++) { //loop to make sure token has at least one letter or else return nothing
        if (isalpha(s[i])) {
            letter_counter += 1;
        }
    }
    clean_string += last_letter; //add final temp char holder
    if (contains_letter == 0 || letter_counter == 0) { //if there is no letters then return nothing, else return token
        return "";
    }
    else {
        return clean_string;
    }
}
// Test for cleanToken to make sure that the real word is built by outputing to the terminal
// returns a pass for any correct condition in comparison to the answer
bool testCleanToken() { //unit testing for cleanToken function
    string ans = "";
    string ans1 = "3delivery4";
    string ans2 = "dəˈvraɪ";
    string ans3 = "hello";
    string ans4 = "beyond_reason";
    string ans5 = "eggs";
    int pass = 0;
    int fail = 0;

    ans == cleanToken("....2312^#@@@...") ? pass++ : fail++;
    ans1 == cleanToken("3delivery4") ? pass++ : fail++;
    ans2 == cleanToken("/dəˈvraɪ/") ? pass++ : fail++;
    ans3 == cleanToken("...HELLO...") ? pass++ : fail++;
    ans4 == cleanToken("{{beyond_reason'}}") ? pass++ : fail++;
    ans5 == cleanToken("EGGS!") ? pass++ : fail++;
    return (fail > 0);
}

// This function is meant to take in text and parse it by spaces
// to get a token to clean and then put into a set
set<string> gatherTokens(string text) {
    set<string> tokens;
    stringstream ss; //string stream to easily parse text
    string token, clean_token; //temp holders for individual input tokens and output clean tokens
    ss << text;
    while (ss >> token) { //string stream to put out each token and loop to clean and insert into set
        clean_token = cleanToken(token);
        if (clean_token == "") { //dont put empty tokens into set, insert otherwise
            continue;
        }
        else {
            tokens.insert(clean_token);
        }
    }
    return tokens;
}
// Gather token test checks for a a given input to gives the correct amount of keys
void gather_token_test() {
    set<string> tokens = gatherTokens("to be or dot dot dot to be| ||| || .yee YEE ");
    set<string> answers = { "to", "be", "or", "dot", "yee" };
    tokens.size() == answers.size() ? cout << "pass\n" : cout << "fail\n";
    tokens == answers ? cout << "pass\n" : cout << "fail\n";
}
// Helper function to take in filename and check if the file is open, print out proper message
bool check_if_open(string filename) {
    fstream file(filename);
    if (!file.is_open()) { //process of opening file
        cout << "Invalid filename." << endl;
        return false; //go back to main if fail
    }
    else {
        cout << "Stand by while building index..." << endl;
        file.close();
        return true;
    }
}
// This function takes in a filename and map to build a map
// using functions that build a set from the file text and take in the url as a key
int buildIndex(string filename, map<string, set<string>>& index) {
    fstream file(filename);
    string line, line2, text, url; //temporary storage variables to store file lines and respective line type
    set<string> tokens;
    set<string> urls;
    set<string>::iterator iter; //iterator object to help iterate over set
    int i = 0;
    while (getline(file, line)) { // loop over every two lines in the file
        getline(file, line2);
        tokens = gatherTokens(line2); //collect tokens form text
        for (iter = tokens.begin(); iter != tokens.end(); iter++) { //loop to go over all token set, get keys with *iter
            if (index.count(*iter) > 0) { //if token exists in index
                index[*iter].insert(line); //add designated urls to index key and avoid duplication
                continue;
            }
            else {                        //else add urls to temp urls storage and finally emplace url set at *iter key
                urls.insert(line);
                index.emplace(*iter, urls);
            }
        }
        urls.clear(); //clean temp container for set after filling a *iter key up
        i++; //count number of pages to return;
    }
    file.close();
    return i;
}
bool build_ind_test() { //test function to test build index
    int pgs = 0;
    map<string, set<string>> temp_test;
    int pass = 0;
    int fail = 0;
    pgs = buildIndex("tiny.txt", temp_test); // test number of pages read
    if (pgs == 4) {
        pass++;
    } else {
        fail++;
    }
    return 0 == fail;
}
// This function takes in the index map and user input query and goes through the index to
// find matching sets of urls and operate on those sets based on input modifiers
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    vector<string> search_tokens; //vectors to holder search tokens and sets that were collected from index
    vector<set<string>> set_holder;
    stringstream ss; //to parse sentence
    string temp;
    bool ini_search = false; //if one search for the set and set operations were done
    if (sentence == "") { //catch case for empty sentence to return result
        return result;
    }
    ss << sentence;
    while (ss.rdbuf()->in_avail() > 0) { //while the string stream is not empty, parse, and add to token vector
        ss >> temp;
        search_tokens.push_back(temp);
    }
    if (!(sentence.find(' ') != string::npos)) { //if only one search term is entered, only get one set of urls
        for (auto e : index) {
            if (sentence == e.first) {
                result = e.second;
            }
        }
    }
    else { // else loop through token vector
        for (int i = 0; i < search_tokens.size(); i++) {
            for (auto& e : index) { // then loop through index
                if (search_tokens.at(i) == e.first) { // to check token vector matches index token
                    set_holder.push_back(e.second); //and push back designated set to set vector container
                }
                else if (search_tokens.at(i).substr(1) == e.first && (search_tokens[i][0] == '-' || search_tokens[i][0] == '+')) {
                    set_holder.push_back(e.second); //don't forget to add tokens that have a modifier in front of it
                }
            }
        }
        for (int j = 0; j < set_holder.size() - 1; j++) { //loop to perform set operations, 1st operation done directly, any operation after requires a temp storage
            if (isalpha(search_tokens.at(j + 1).at(0)) && ini_search == false) {
                set_union(set_holder.at(j).begin(), set_holder.at(j).end(), set_holder.at(j + 1).begin(), set_holder.at(j + 1).end(), inserter(result, result.begin()));
            }
            else if ((search_tokens.at(j + 1).at(0)) == '+' && ini_search == false) {
                set_intersection(set_holder.at(j).begin(), set_holder.at(j).end(), set_holder.at(j + 1).begin(), set_holder.at(j + 1).end(), inserter(result, result.begin()));
            }
            else if ((search_tokens.at(j + 1).at(0)) == '-' && ini_search == false) {
                set_difference(set_holder.at(j).begin(), set_holder.at(j).end(), set_holder.at(j + 1).begin(), set_holder.at(j + 1).end(), inserter(result, result.begin()));
            }
            else if (isalpha(search_tokens.at(j + 1).at(0))) {
                set<string> temp = result; //operations that happen more than once need to temp store the result so the set_operation can put the output set into an empty one which is always "result"
                result.clear();
                set_union(temp.begin(), temp.end(), set_holder.at(j + 1).begin(), set_holder.at(j + 1).end(), inserter(result, result.begin()));
            }
            else if ((search_tokens.at(j + 1).at(0)) == '+') {
                set<string> temp = result;
                result.clear();
                set_intersection(temp.begin(), temp.end(), set_holder.at(j + 1).begin(), set_holder.at(j + 1).end(), inserter(result, result.begin()));
            }
            else if ((search_tokens.at(j + 1).at(0)) == '-') {
                set<string> temp = result;
                result.clear();
                set_difference(temp.begin(), temp.end(), set_holder.at(j + 1).begin(), set_holder.at(j + 1).end(), inserter(result, result.begin()));
            }
            ini_search = true; //check if one operation has already been done
        }
    }
    return result;
}
bool test_query() { // test function to test query
    map<string, set<string>> temp_test;
    set<string> temp_tokens = gatherTokens("I'm not trying to eat you");
    int pgs = buildIndex("tiny.txt", temp_test);
    set<string> query_output = findQueryMatches(temp_test, "not");
    int pass = 0, fail = 0;
    for (auto& e : query_output) {
        if (e == "www.bigbadwolf.com") {
            fail++;
        } else {
            pass++;
        }
    }
    return fail > 0;
}

//multiple tests to check proper url grabbing
void match_test(map<string, set<string>>& index) {
    set<string> test;
    test = findQueryMatches(index, "story +build grow -google");
    for (auto& e : test) {
        cout << e << endl;
    }
    cout << endl;
    test = findQueryMatches(index, "eggs eat");
    for (auto& e : test) {
        cout << e << endl;
    }
    cout << endl;
    test = findQueryMatches(index, "fish red bread eat");
    for (auto& e : test) {
        cout << e << endl;
    }
    cout << endl;
    test = findQueryMatches(index, "red +blue");
    for (auto& e : test) {
        cout << e << endl;
    }
    cout << endl;
}

// Function to format and output proper messages to the user
// takes in the file name, loops to ask for input to output a library of urls
void searchEngine(string filename) {
    map<string, set<string>> index; //create library storage, "index"
    set<string> output;
    string input;
    while (!check_if_open(filename)) { //loop to keep getting input until valid file name is given
        getline(cin, filename);
    }
    int num_pages = buildIndex(filename, index); //keep track of number of pages
    int num_terms = 0; //collect number of unique terms
    for (auto& e : index) { //loop over index to get number of unique terms
        num_terms += 1;
    }
    cout << "Indexed " << num_pages << " pages containing " << num_terms << " unique terms\n" << endl;
    do { //loop to ask user a search phrase to ultimately return a sequence of urls
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, input);
        if (input.size() == 0) { // if no input than terminate program
            break;
        }
        output = findQueryMatches(index, input);
        cout << "Found " << output.size() << " matching pages\n";
        for (auto& e : output) { //output all the urls found
            cout << e << endl;
        }
        cout << endl;
    } while (input.length() != 0); //while input stores something from user
    cout << "Thank you for searching!";
}

