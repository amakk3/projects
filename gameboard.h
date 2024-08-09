/*-------------------------------------------
Program 7: Outlast the Baddies & Avoid the Abyss
Course: CS 211, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */
#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>
#include <string>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        size_t HeroRow; // Hero's position row
	    size_t HeroCol; // Hero's position column
        int numMonsters;
        int numSuperMonsters;
        int numAbysses;
        int numBats;
        bool wonGame; // false, unless the Hero reached the exit successfully

		
	public: 
		/* default constructor */
        GameBoard() {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 50;
            numBats = 2;
            wonGame = false;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 20;
            numBats = 3;
            wonGame = false;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Nothing(row,col);
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

        // fills board with by randomly placing...
        //  - Hero (H) in the first three columns
        //  - EscapeLadder (*) in last three columns
        //  - 3 vertical Walls (+), each 1/2 of board height, in middle segment
        //  - Abyss cells (#), quantity set by numAbysses, in middle segment
        //  - Baddies [Monsters (m), Super Monsters (M), & Bats (~)] in middle segment;
        //    number of Baddies set by numMonsters, numSuperMonsters, & numBats
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            r = rand() % numRows;
            c = rand() % 3;
            delete board(r,c);
            board(r,c) = new Hero(r,c);
            HeroRow = r;
            HeroCol = c;

            r = rand() % numRows;
            c = numCols - 1 - (rand() % 3);
            delete board(r,c);
            board(r,c) = new EscapeLadder(r,c);
            
            int sizeMid = numCols - 6;

            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);           
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }

            for (int i = 0; i < numMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c);  
                board(r,c)->setPower(1);        
            }

            for (int i = 0; i < numSuperMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c); 
                board(r,c)->setPower(2);               
            }

            for (int i = 0; i < numBats; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Bat(r,c); 
            }

            for (int i = 0; i < numAbysses; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Abyss(r,c);              
            }
        }

        // neatly displaying the game board 
		void display( ) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
        }
		
        bool getWonGame() {
            return wonGame;
        }
        
        // distributing total number of monsters so that 
        //  ~1/3 of num are Super Monsters (M), and
        //  ~2/3 of num are Regular Monsters (m)
        void setNumMonsters(int num) {
            numSuperMonsters = num/3;
            numMonsters = num - numSuperMonsters;
        }

        void setNumAbysses(int num) {
            numAbysses = num;
        }

        void setNumBats(int num) {
            numBats = num;
        }

        size_t getNumRows() {
            return numRows;
        }

        size_t getNumCols() {
            return numCols;
        }

        
        //---------------------------------------------------------------------------------
        // void getHeroPosition(size_t& row, size_t& col)
        //
        // getter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // note: row and col are passed-by-reference
        //---------------------------------------------------------------------------------
        void getHeroPosition(size_t& row, size_t& col) {
            row = this->HeroRow;
            col = this->HeroCol;
        }

        
        //---------------------------------------------------------------------------------
        // void setHeroPosition(size_t row, size_t col)
        //
        // setter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        //---------------------------------------------------------------------------------
        void setHeroPosition(size_t row, size_t col) {
            this->HeroCol = col;
            this->HeroRow = row;
        }

        
        //---------------------------------------------------------------------------------
        // findHero()
        //
        // updater for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // this function should find Hero in board and update
        //      HeroRow and HeroCol with the Hero's updated position;
        // if Hero cannot be found in board, then set Hero's position to (-1,-1)
        //---------------------------------------------------------------------------------
        void findHero() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    if (board(row, col)->isHero()) {
                        this->HeroRow = row;
                        this->HeroCol = col;
                        return;
                    }
                }
            }
            this->HeroRow = -1;
            this->HeroCol = -1;
        }

        
        //---------------------------------------------------------------------------------
        // bool makeMoves(char HeroNextMove)
        // 
        // This is the primary gameplay operation for a single round of the game. 
        // A LOT happens in this function... 
        // General steps:
        //  - Allow user to input their next move 
        //  - Get the attempted move position for the Hero
        //  - Move the hero, catching/resolving any potential collision exceptions...
        //      - attempted move out-of-bounds: change row &/or col to stay on board
        //      - attempted move into a barrier: change row &/or col to stay off barrier
        //      - attempted move to the exit: remove hero from board, hero escaped!
        //      - attempted move into a hole: remove hero from board, hero did not escape
        //      - attempted move to a baddie: remove hero from board, hero did not escape
        //      - attempted move to an empty space: actual move is the attempted move
        //  - For each baddie (regular Monster, super Monster, or Bat) on the board...
        //      - check that this baddies hasn't already moved this round
        //      - get its attempted move position
        //      - move the baddie, catching/resolving any potential collision exceptions...
        //          - attempted move out-of-bounds: change row &/or col to stay on board
        //          - attempted move into a barrier: change row &/or col to stay off barrier
        //          - attempted move to the exit: change row &/or col to stay off exit
        //          - attempted move into a hole: remove baddie from board
        //          - attempted move to hero: remove hero from board, hero did not escape
        //          - attempted move to a baddie: ignore attempted move, no position change
        //          - attempted move to an empty space: actual move is the attempted move 
        // 
        // Note: all baddies (and the hero) fall into holes if their attempted 
        //       move ENDs on a hole (i.e. even Bats are drawn into the 
        //       Abyss if their attempted move takes them to an Abyss cell); 
        //       BUT, baddies can travel over holes, as long as their attempted 
        //       move does NOT END on a hole; this only applies, in practice, 
        //       to super monsters and bats, since their step sizes can be more 
        //       than 1 (monsters and the hero are limited to steps of size 1)
        //
        // Note: also, whereas baddies (and the hero) can never move onto a 
        //       barrier (i.e. a wall), they can step over barriers as long
        //       as the attempted move does NOT END on a barrier; this only 
        //       applies, in practice, to super monsters and bats, since their 
        //       step sizes can be more than 1 (monsters and the hero are limited 
        //       to steps of size 1)
        //
        // Note: to prevent a single baddie from making multiple moves
        //       during a single round of the game, whenever a baddie 
        //       has moved, it should be marked as "already moved" in 
        //       some way; this can be done using the [moved] data member
        //       of the BoardCell base class, which has setter/getter 
        //       functions provided. The [moved] data members must be 
        //       reset for all BoardCells at the beginning of each round.
        //
        // Note: the [myRow] and [myCol] data members for BoardCell derived
        //       class objects must be updated whenever a move is made; 
        //       additionally, [HeroRow] and [HeroCol] data members for the 
        //       GameBoard must be updated whenever the Hero has moved, 
        //       which can be done easily with a call to findHero()
        //
        // Note: many actual moves made by non-static board cell objects 
        //       (i.e. Heros, Monsters, Bats) involve constructing and/or 
        //       destructing objects; be careful with memory management; 
        //       specifically, make sure to free (delete) the memory for 
        //       BoardCell derived class objects when you are done with it
        //
        // return true if Hero is still on board at the end of the round
        // return false if Hero is NOT on board at the end of the round
        //---------------------------------------------------------------------------------
        bool makeMoves(char HeroNextMove) {
            // determine where hero proposes to move to
            size_t newR, newC;
            board(HeroRow,HeroCol)->setNextMove(HeroNextMove);
            board(HeroRow,HeroCol)->attemptMoveTo(newR,newC,HeroRow,HeroCol);
            try {
                // hero attempts to move out-of-bounds in rows
                if (newR < 0 || newR >= numRows) { 
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid row");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newR = HeroRow;
                cout << "Changing row for Hero position to stay in-bounds" << endl;
            }
            try { //test for hero attempting to move out-of-bounds in columns
                if (newC < 0 || newC >= numCols) { 
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid column");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newC = HeroCol;
                cout << "Changing column for Hero position to stay in-bounds" << endl;
            }
            try { // test for hero attempting to move into a barrier
                if (board(newR,newC)->isBarrier()) { 
                    throw runtime_error("Hero trying to move into a barrier");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                auto rowTemp = newR;
                if (newR != HeroRow) { // if new row is not the same as the current hero's row
                    rowTemp = HeroRow;
                }
                if (board(rowTemp,newC)->isBarrier()) { // if new column is not the same as the current hero's column
                    newC = HeroCol;
                }

                cout << "Changing row and column for Hero position to stay off barrier" << endl;
            }

            if (board(newR,newC)->isSpace()) { //hero moves to an empty space
                delete board(HeroRow, HeroCol);
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                delete board(newR, newC);
                board(newR, newC) = new Hero(newR, newC);
                HeroRow = newR;
                HeroCol = newC;
                this->setHeroPosition(newR, newC);
            }
            //hero attempts to move to a hole
            if (board(newR,newC)->isHole()) {
                cout << "Hero fell into a hole" << endl;
                delete board(HeroRow, HeroCol);
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                return false;
            }
            //hero attempts to move to exit
            if (board(newR,newC)->isExit()) {
                cout << "Hero escaped!" << endl;
                delete board(HeroRow, HeroCol);
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                this->wonGame = true;
                return false;
            }
            if (board(newR,newC)->isBaddie()) { //hero attempts to move to a baddie, end game
                cout << "Hero was killed by a baddie" << endl;
                delete board(HeroRow, HeroCol);
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                return false;
            }
            //loop through grid, if it is not static, set moved to false
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    if (board(row, col)->isStatic() == false) {
                        board(row, col)->setMoved(false);
                    }
                }
            }
            //loop through grid to find baddies
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    if (board(row, col)->isBaddie() && board(row, col)->getMoved() == false) { //if baddie has not moved yet
                        size_t newR, newC;
                        board(row, col)->attemptMoveTo(newR, newC, HeroRow, HeroCol);
                        try {
                            // baddie attempting to move out-of-bounds in rows
                            if (newR < 0 || newR >= numRows) { 
                                throw runtime_error("Baddie trying to move out-of-bounds with an invalid row");
                            }
                        }
                        catch (runtime_error& excpt) {
                            cout << excpt.what() << endl;
                            newR = row;
                            cout << "Changing row for Baddie position to stay in-bounds" << endl;
                        }
                        try { // baddie attempting to move out-of-bounds in columns
                            if (newC < 0 || newC >= numCols) { 
                                throw runtime_error("Baddie trying to move out-of-bounds with an invalid column");
                            }
                        }
                        catch (runtime_error& excpt) {
                            cout << excpt.what() << endl;
                            newC = col;
                            cout << "Changing column for Baddie position to stay in-bounds" << endl;
                        } // baddie attempting to move into a barrier or exit
                        try {
                            if (board(newR, newC)->isBarrier() || board(newR, newC)->isExit()) { 
                                throw runtime_error("Baddie trying to move into a barrier or exit");
                            }
                        }
                        catch (runtime_error& excpt) {
                            cout << excpt.what() << endl;
                            auto rowTemp = newR;
                            if (newR != row) { // if new row is not the same as the current baddie's row
                                rowTemp = row;
                            }
                            if (board(rowTemp, newC)->isBarrier() || board(newR, newC)->isExit()) { // if new column is not the same as the current baddie's column
                                newC = col;
                            }
                            cout << "Changing row and column for Baddie position to stay off barrier" << endl;
                        }
                        //baddie attempts to move to a hole
                        if (board(newR, newC)->isHole()) {
                            cout << "Baddie fell into a hole" << endl;
                            delete board(row, col);
                            board(row, col) = new Nothing(row, col);
                        }
                        if (board(newR, newC)->isHero()) { //baddie attempts to move to hero, end game
                            cout << "Hero was killed by a baddie" << endl;
                            //baddie replaces hero position
                            auto temp = board(row, col);
                            delete board(newR, newC);
                            board(newR, newC) = temp;
                            board(newR, newC)->setPos(newR, newC);
                            board(row, col) = new Nothing(row, col);
                        }
                        if (board(newR, newC)->isBaddie()) { //baddie attempts to move to another baddie, ignore
                            continue;
                        }
                        if (board(newR, newC)->isSpace()) {//baddie attempts to move to an empty space
                            //swap baddie and space cells with each other without deleting or creating new objects
                            auto temp = board(row, col);
                            board(row, col) = board(newR, newC);
                            board(row, col)->setPos(row, col);
                            board(newR, newC) = temp;
                            board(newR, newC)->setMoved(true);
                            board(newR, newC)->setPos(newR, newC);
                        }
                    }
                }
            }
            this->findHero(); //check last to see if hero is still on board and end game properly
            if (this->HeroRow == -1 && this->HeroCol == -1) {
                return false;
            }
            return true;
        }
    
};

#endif //_GAMEBOARD_H