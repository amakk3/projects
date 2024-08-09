/*-------------------------------------------
Program 2: Search Engine
Course: CS 251, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */

#include "search.h"
using namespace std;


int main() {
    // test functions
    // cout << testCleanToken() << endl;
    // gather_token_test();
    // cout << build_ind_test() << endl;
    // cout << test_query() << endl;
    string filename;
    getline(cin, filename);
    searchEngine(filename);
    return 0;
}

