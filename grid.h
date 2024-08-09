/*-------------------------------------------
Program 7: Outlast the Baddies & Avoid the Abyss
Course: CS 211, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */
#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
	struct ROW {
		T*  Cols;     // array of column elements
		size_t NumCols;  // total # of columns (0..NumCols-1)
	};

	ROW* Rows;     // array of ROWs
	size_t  NumRows;  // total # of rows (0..NumRows-1)
		
public:
//
// default constructor:
//
// Called automatically by to construct a 4x4 Grid. 
// All elements initialized to default value of T.
//
Grid() {
	Rows = new ROW[4];  // 4 rows
	NumRows = 4;

	// initialize each row to have 4 columns:
	for (size_t r = 0; r < NumRows; ++r) {
		Rows[r].Cols = new T[4];
		Rows[r].NumCols = 4;

	// initialize the elements to their default value:
		for (size_t c = 0; c < Rows[r].NumCols; ++c) {
			Rows[r].Cols[c] = T();  // default value for type T:
		}
	}
}

//
// parameterized constructor:
//
// Called automatically to construct a Grid 
// with R rows, where each row has C columns. 
// All elements initialized to default value of T.
//
Grid(size_t R, size_t C) {
	Rows = new ROW[R];  //initialize rows and columns
	NumRows = R;
	for (size_t r = 0; r < R; ++r) { //initialize rows of size R
		Rows[r].Cols = new T[C];
		Rows[r].NumCols = C;
		for (size_t c = 0; c < C; ++c) { //initialize columns of size C
			Rows[r].Cols[c] = T(); //assign default value to each element
		}
	}
}
	
//
// destructor:
//
// Called automatically to free memory for this Grid.
//
virtual ~Grid() {
	for (size_t r = 0; r < NumRows; ++r) { // loop through rows to delete the list of columns
		delete[] Rows[r].Cols;
	}
	delete[] Rows; //delete the rows
}


//
// copy constructor:
//
// Called automatically to construct a Grid that contains a
// copy of an existing Grid.  Example: this occurs when passing
// Grid as a parameter by value
//
//   void somefunction(Grid<int> G2)  <--- G2 is a copy:
//   { ... }
//
Grid(const Grid<T>& other) {
	Rows = new ROW[other.NumRows]; //initialize rows and columns
	NumRows = other.NumRows;
	for (size_t r = 0; r < NumRows; ++r) { //initialize rows of size R
		Rows[r].Cols = new T[other.Rows[r].NumCols];
		Rows[r].NumCols = other.Rows[r].NumCols;
		for (size_t c = 0; c < Rows[r].NumCols; ++c) { //initialize columns of size C
			Rows[r].Cols[c] = other.Rows[r].Cols[c]; //assign default value to each element
		}
	}
}
	
//
// copy operator=
//
// Called when one Grid is assigned into another, i.e. this = other;
//
Grid& operator=(const Grid& other) {
	for (size_t r = 0; r < NumRows; ++r) { // loop through rows to delete the list of columns
		delete[] Rows[r].Cols;
	}
	delete[] Rows; //delete the rows
	Rows = new ROW[other.NumRows]; //initialize rows and columns
	NumRows = other.NumRows;
	for (size_t r = 0; r < NumRows; ++r) { //initialize rows of size R
		Rows[r].Cols = new T[other.Rows[r].NumCols];
		Rows[r].NumCols = other.Rows[r].NumCols;
		for (size_t c = 0; c < Rows[r].NumCols; ++c) { //initialize columns of size C
			Rows[r].Cols[c] = other.Rows[r].Cols[c]; //assign default value to each element
		}
	}
	return *this; 
	
}

//
// numrows
//
// Returns the # of rows in the Grid.  
// The indices for these rows are 0..numrows-1.
//
size_t numrows() const {
	//return this->NumRows typecasted to size_t
	return this->NumRows;
}


//
// numcols
//
// Returns the # of columns in row r.  
// The indices for these columns are 0..numcols-1.  
// For now, each row has the same number of columns.
//
size_t numcols(size_t r) const {
	return this->Rows[r].NumCols; //gets the number of columns in the first row
}


//
// size
//
// Returns the total # of elements in the Grid.
//
size_t size() const {
	return this->Rows[0].NumCols * this->NumRows; //multiplies the number of rows by the number of columns in the first row
}


//
// ()
//
// Returns a reference to the element at location (r, c);
// this allows you to access or assign the element:
//
//    grid(r, c) = ...
//    cout << grid(r, c) << endl;
//
T& operator()(size_t r, size_t c) {
	if (r < 0 || r >= this->NumRows || c < 0 || c >= this->Rows[0].NumCols) { //check if the row and column are within the bounds
        throw false;
    } else {
        return Rows[r].Cols[c];
    }
}

//
// _output
//
// Outputs the contents of the grid; for debugging purposes.  
// This is not tested.
//
void _output() {
	for (size_t r = 0; r < NumRows; ++r) {
		for (size_t c = 0; c < Rows[r].NumCols; ++c) { // loop through every element in the grid to print out its contents
			cout << Rows[r].Cols[c] << " ";
		}
		cout << endl;
	}
	
}

};
