/*-------------------------------------------
Program 7: Outlast the Baddies & Avoid the Abyss
Course: CS 211, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */
#ifndef _BOARDCELL_H
#define _BOARDCELL_H

using namespace std;

// First, the BoardCell abstract base class 

class BoardCell {
	
    public:  
		BoardCell() {} // default contstructor (do nothing)
        virtual ~BoardCell() {} // destructor (do nothing)
        
        virtual char display( ) = 0; // pure virtual function; this is an abstract base class

    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            //default attemptMoveTo function for all board cells where it is not already defined in their own class
            newR = this->getRow();
            newC = this->getCol();
        }
        
        virtual bool isHero( ) {return false;}
    	virtual bool isBaddie( ) {return false;}
    	virtual bool isSpace( ) {return false;}
        virtual bool isBarrier( ) {return false;}
        virtual bool isHole( ) {return false;}
    	virtual bool isExit( ) {return false;}
    	virtual bool isStatic( ) {return true;}

        virtual void setPower(int num) {}
        virtual int getPower() {return 1;}
        virtual void setNextMove(char inChar) {}
        
        void setMoved(bool m) {moved = m;}
        bool getMoved() {return moved;}
        void setRow(size_t r) {myRow = r;}
        size_t getRow() {return myRow;}
        void setCol(size_t c) {myCol = c;}
        size_t getCol() {return myCol;}
        void setPos(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

    private:
        size_t myRow; // current row for this board cell in a 2D grid
        size_t myCol; // current column for this board cell in a 2D grid
        bool moved;   // true = this board cell already moved in the current round

}; // BoardCell (abstract base class)


// Then, all the derived classes

class Hero: public BoardCell {
	
    public:
    	Hero(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        
        virtual bool isHero( ) {return true;}
        virtual bool isStatic( ) {return false;}
        virtual char display( ) {return 'H';}
        
        virtual void setNextMove(char inChar ) {
            nextMove = inChar;
        }
    	
        virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            switch (this->nextMove) //switch case to determine the calculated new position of the hero based on the input
            {
            case 'q':
                newR = hRow - 1;
                newC = hCol - 1;
                break;
            case 'w':
                newR = hRow - 1;
                newC = hCol;
                break;
            case 'e':
                newR = hRow - 1;
                newC = hCol + 1;
                break;
            case 'a':
                newR = hRow;
                newC = hCol - 1;
                break;
            case 'd':
                newR = hRow;
                newC = hCol + 1;
                break;
            case 'z':
                newR = hRow + 1;
                newC = hCol - 1;
                break;
            case 'x': 
                newR = hRow + 1;
                newC = hCol;
                break;
            case 'c':
                newR = hRow + 1;
                newC = hCol + 1;
                break;
            default:
                newR = hRow;
                newC = hCol;
                break;
            }
        }

    private:
        char nextMove;

}; // Hero


class Monster: public BoardCell {
    
    public:
		Monster(size_t r, size_t c) {
            setRow(r);
            setCol(c);
            power = 1;
        }
        
        virtual bool isBaddie( ) {return true;}
        virtual bool isStatic( ) {return false;}
        
        virtual char display( ) {
            if (power == 2) {
                return 'M'; // Super Monster
            } else {
                return 'm'; // Monster
            } 
        }

        virtual void setPower(int num) {
            power = num;
        }

        virtual int getPower() {
            return power;
        }
        
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            if (this->power == 1) //check the power levels of the monster
            {
                if (this->getRow() > hRow) { //if the monster is above the hero, move down
                    newR = this->getRow() - 1;
                } else if (this->getRow() < hRow) { // if the monster is below the hero, move up
                    newR = this->getRow() + 1;
                } else {
                    newR = this->getRow();
                }
                if (this->getCol() > hCol) {//if the monster is to the left of the hero, move right
                    newC = this->getCol() - 1;
                } else if (this->getCol() < hCol) {//if the monster is to the right of the hero, move left
                    newC = this->getCol() + 1;
                } else {
                    newC = this->getCol();
                }
            } else if (this->power == 2) {
                if (this->getRow() > hRow) {
                    newR = this->getRow() - 2;
                } else if (this->getRow() < hRow) {
                    newR = this->getRow() + 2;
                } else {
                    newR = this->getRow();
                }
                if (this->getCol() > hCol) {
                    newC = this->getCol() - 2;
                } else if (this->getCol() < hCol) {
                    newC = this->getCol() + 2;
                } else {
                    newC = this->getCol();
                }
            } else {
                newR = this->getRow();
                newC = this->getCol();
            }
        }
    
    private:
        int power; // power = 1 for Monster, power = 2 for SuperMonster

}; // Monster

class Bat: public BoardCell {
    public:
		Bat(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual bool isBaddie( ) {return true;}
        virtual bool isStatic( ) {return false;}
        virtual char display( ) {return '~';}
        
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) { //bat movement only moves by columns
            newR = this->getRow();
            newC = hCol;
        }

}; // Bat


class Abyss: public BoardCell {
	public:
    	Abyss(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '#';}
        virtual bool isHole( ) {return true;}
}; // Abyss


class Wall: public BoardCell {
	public:
    	Wall(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '+';}
    	virtual bool isBarrier( ) {return true;}
}; // Wall


class Nothing: public BoardCell {
	public:
    	Nothing(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return ' ';}
    	virtual bool isSpace( ) {return true;}
}; // Nothing


class EscapeLadder: public BoardCell {
	public:
    	EscapeLadder(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '*';}
    	virtual bool isExit( ) {return true;}
}; // EscapeLadder


#endif //_BOARDCELL_H
