/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Linux x86_64 and G++
    Author: George Maratos and David Hayes
    Name: Abrar Makki
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */
bool end; //initialize the global variable for exiting status determined by the functions
void make_move();
void initialize_board();
bool game_over();


int main()
{
    display_instructions();
    initialize_board(); //make default board
    do {
        display_board();//update board
        make_move();//take inputs
    } while (game_over()); // determine whether game is over
    return 0;
}

void make_move() //determing
{
    
    string move;
    char from;
    char jump;
    char to;
    cout << "Enter positions from, jump, and to (e.g. EFG): ";
    cin >> move;
    from = toupper(move[0]);//converted first letter
    jump = toupper(move[1]);//converted second letter
    to = toupper(move[2]);//converted third letter
    switch (from){ //compare the first character 
        case 'X': // x determines exiting status and calls game_over()
            ::end = true;//set exiting status by updating global variable
            game_over();
            cout << "Exiting." << endl;
            break;
        case 'R': //r determins reseting of board
            cout << "Restarting game." << endl;
            initialize_board();//call function to reset array
            break;
        default: //when no special case sent automatically move game forward
            if (move.length() > 3 || move.length() < 3) {
                cout << "*** Invalid sequence. Please retry." << endl;
            }else if (((from < 'A') || (from > 'M')) || ((jump < 'A') || (jump > 'M')) || ((to < 'A') || (to > 'M'))) {
                cout << "*** Given move has positions not on the board! Please retry." << endl;
            } else if (get_element(jump) == '.') { // error middle piece
                cout << "*** Must jump a piece. Please retry." << endl;
            } else if (get_element(from) == '.'){ //error beginning piece
                cout << "*** Source needs a piece. Please retry." << endl;
            } else if (get_element(to) != '.') { //error end piece
                cout << "*** Destination must be empty. Please retry." << endl;
            } else if (!(((from == 'A' || from == 'E') && jump == 'B' && (to == 'A' || to == 'E')) ||
                        ((from == 'D' || from == 'J') && jump == 'G' && (to == 'D' || to == 'J')) ||
                        ((from == 'I' || from == 'M') && jump == 'L' && (to == 'I' || to == 'M')) ||
                        ((from == 'A' || from == 'I') && jump == 'D' && (to == 'A' || to == 'I')) ||
                        ((from == 'B' || from == 'L') && jump == 'G' && (to == 'B' || to == 'L')) ||
                        ((from == 'E' || from == 'M') && jump == 'J' && (to == 'E' || to == 'M')) ||
                        ((from == 'B' || from == 'D') && jump == 'C' && (to == 'B' || to == 'D')) ||
                        ((from == 'B' || from == 'J') && jump == 'F' && (to == 'B' || to == 'J')) ||
                        ((from == 'J' || from == 'L') && jump == 'K' && (to == 'J' || to == 'L')) ||
                        ((from == 'D' || from == 'L') && jump == 'H' && (to == 'D' || to == 'L')) ||
                        ((from == 'A' || from == 'G') && jump == 'C' && (to == 'A' || to == 'G')) ||
                        ((from == 'M' || from == 'G') && jump == 'K' && (to == 'M' || to == 'G')) ||
                        ((from == 'I' || from == 'G') && jump == 'H' && (to == 'I' || to == 'G')) ||
                        ((from == 'E' || from == 'G') && jump == 'F' && (to == 'E' || to == 'G')) ||
                        ((from == 'F' || from == 'H') && jump == 'G' && (to == 'F' || to == 'H')) ||
                        ((from == 'C' || from == 'K') && jump == 'G' && (to == 'C' || to == 'K')))){ //error if not any of these combos
                cout << "*** Move is invalid." << endl;
            } else { //else make the move
                set_element(to, '#');
                set_element(jump, '.');
                set_element(from, '.');
    }         
    }
}

bool game_over()
{
    int j = 13; //counter to check empty board
    for (int i = 0; i < 13; ++i) { //iterates through board to determine only one piece left
        if (board[i] == '.') {
            j -= 1;
        }
    }
    if (::end == true){ //if special character x exiting status is true then end program
        return false;
    }
    if (j == 1) { //if one piece left you win game and end program
        cout << "Congrats you win!" << endl;
        return false;
    } else {
        return true;
    }
}

void initialize_board() //set default positions and their values 
{
    set_element('A', '#');
    set_element('B', '#');
    set_element('C', '#');
    set_element('D', '#');
    set_element('E', '#');
    set_element('F', '#');
    set_element('G', '.');
    set_element('H', '#');
    set_element('I', '#');
    set_element('J', '#');
    set_element('K', '#');
    set_element('L', '#');
    set_element('M', '#');
    
}