/**------------------------------------------
    Program 1: ASCII Flowers
    Prompt for the number of flower layers and display

    Course : CS 141, Spring 2023
    System : Linux_x86_64 and G ++
    Author : George Maratos and David Hayes
    Name : Abrar Makki
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    // display the prompt to the user
    cout << "Program 1: ASCII Flowers\n"
         << "Choose from the following options:\n"
         << "   1. Display the HELLO graphic\n"
         << "   2. Display The Flower\n"
         << "   3. Exit the program\n"
         << "Your choice -> ";

    // read in the user's choice
    int menu_option;
    cin >> menu_option;

    // handle option to quit
    if (menu_option == 3) {
        exit(0);
    }

    // handle the HELLO graphic choice
    if (menu_option == 1) {
        char frame;
        cout << "Enter your frame character: ";
        cin >> frame;
        //top border
        cout << endl;
        for (int i=0; i<2; i++) {
            cout << setfill(frame) << setw(36) << ' ' << endl;
        }
        //message
        cout << setfill(frame) << setw(3) << right << " "
             << "** ** ***** **    **    *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** **    **    *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** **    **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "***** ***** **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "***** ***** **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** **    **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** ***** ***** *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** ***** ***** *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << right;
        //bottom border
        for (int i=0; i<2; i++) {
            cout << setfill(frame) << setw(36) << " " << endl;
        }
    }

    // handle the floral pattern TODO for students
    if (menu_option == 2) {
        int segments;
        int k = 0;
        int o = 0;
        int petal = 0;
        int l;
        bool middle = false;
        cout << "Enter a number: ";
        cin >> segments;
        cout << endl;
        for (int i = 0; i < segments + 1; i++){ //building the upper portion of flower
            o = 0;
                cout << setfill(' ') << setw(segments) << right << "" //building the divider of segments
                     << "---"
                     << setfill(' ') << setw(segments) << left << "" << endl;
            if (k != segments) {
                petal = 1; // counter for each sub section in each segment
                for (l = 0; l <= i + k; l++){
                    if (l == i) { // telling if middle column 
                        middle = true;
                    }
                    else {
                        middle = false;
                    }
                    cout << setfill(' ') << setw(segments - o) << right << "{"; //left brace for sub-sections
                    
                    for (int j = 0; j < petal; j++) { // left side of petals
                        cout << ":";
                    }
                    
                    if (middle == true) { // middle column
                        cout << "@";
                        middle = false;
                    }
                    else {
                        cout << ":";
                    }

                    
                    for (int j = 0; j < petal; j++) { // right side of petals
                        cout << ":";
                    }
                    
                    cout << setfill(' ') << setw(segments - o) << left << "}" << endl; // right brace for sub-section
                    
                    if (l == i + k) { // terminate loop after reaching threshold
                        break;             
                    }
                    if (l >= i) { // reverse order the sub-sections
                        o -= 2;
                        petal -= 2;

                    }
                    petal += 1;
                    o += 1; 
                    
                }
            }
            k += 1;
        }
        for (int h = 0; h < segments; h++) { //building the stem
            if (h % 2 != 0) { // build left leaf
                cout << setfill(' ') << setw(segments + 1) << "\\";
            }
            else {
                cout << setfill(' ') << setw(segments + 2);
            }
            cout << right << "|"; // build stem
            if (h % 2 == 0) {
                cout << left << "/"; // build right leaf
                cout << endl;
            }

            else {
                cout << endl;
            }
            cout << setfill(' ') << setw(segments + 2) << right << "|" << endl; //build second stem
        }
    }
}