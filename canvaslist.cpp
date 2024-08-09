/*-------------------------------------------
Program 3: Shape & Canvas List
Course: CS 251, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */

#include <iostream>
#include <string>
#include "canvaslist.h"

using namespace std;
// Default constructor
CanvasList::CanvasList() {
    this->listSize = 0;
    this->listFront = nullptr;
    this->listBack = nullptr;
}
// Copy constructor 
CanvasList::CanvasList(const CanvasList& original) {
    this->listSize = 0;             //initialize defaults
    this->listFront = nullptr;
    this->listBack = nullptr;
    ShapeNode* currNode = original.front();
    for (int i = 0; i < original.size(); i++) { // traverse linked list in orgiinal canvas
        auto newShape = currNode->value->copy(); // copy and push back the new shape into new canvas
        this->push_back(newShape);
        currNode = currNode->next;
    }
}
// Operator= overloaded function to copy/assign the rhs linked list to the lhs canvas
CanvasList& CanvasList::operator=(const CanvasList& rhs_canvas) { 
    if (this != &rhs_canvas) {           //don't self-assign
        this->clear();                //absolutely clean lhs canvas
        ShapeNode* currNode = rhs_canvas.front();
        for (int i = 0; i < rhs_canvas.size(); i++) { // loop through rhs canvas
            auto newShape = currNode->value->copy(); //copy and push back the new shapes found
            this->push_back(newShape);
            currNode = currNode->next;
        }
    }
    return *this;
}
// Deconstructor for destroy the inner allocated spaces in the canvas
CanvasList::~CanvasList() {
    if (!this->isempty()) {
        this->clear();
    }
}
// Clean out all of canvas list of its ShapeNodes and inner Shapes
void CanvasList::clear() {
    if (!this->isempty()) {
        for (int i = 0; i < this->size(); i++) { // loop through list to remove at first position
            this->removeAt(i);
            i -= 1;
        }
    }
    this->listSize = 0;
    this->listFront = nullptr;
    this->listBack = nullptr;
}
// Given an index pos and pointer to allocated addShape, insert after the index
void CanvasList::insertAfter(int pos, Shape* addShape) {
    if (pos >= this->size() || pos < 0) { // if index out of bounds, do nothing
        return;
    } 
    if (pos == this->size() - 1) { // if position is first in list, simply push_back shape
        this->push_back(addShape);
        return;
    }
    ShapeNode* addNode = new ShapeNode; //create space for new shapenode and initialize it
    addNode->value = addShape;
    addNode->next = nullptr;
    ShapeNode* currNode = this->front();
    for (int i = 0; i < this->size(); i++) { // loop through list to find correct node
        if (i == pos) {
            addNode->next = currNode->next; // rewire node at position and assign new node to the next
            currNode->next = addNode;
            break;
        }
        currNode = currNode->next;
    }
    this->listSize += 1;
}
// Function to take in a pointer to allocated new_Shape and then create and insert a new_ShapeNode to the front of the list
void CanvasList::push_front(Shape* new_Shape) {
    ShapeNode* new_ShapeNode = new ShapeNode;
    new_ShapeNode->value = new_Shape;
    if (this->listSize == 0) {          // if list empty then simply assign front and back to new node
        new_ShapeNode->next = nullptr;
        this->listBack = new_ShapeNode;
        this->listFront = new_ShapeNode;        
    } else {
        ShapeNode* temp_front = this->listFront;   // else just rewire head pointer to new node and new node's next to old head 
        this->listFront = new_ShapeNode;
        new_ShapeNode->next = temp_front;
    }
    this->listSize += 1;
}
// Function to take in a Shape* and create and add a ShapeNode to the end of the linked list
void CanvasList::push_back(Shape* new_Shape) {
    ShapeNode* new_ShapeNode = new ShapeNode; // make new node and initialize it
    new_ShapeNode->value = new_Shape;
    new_ShapeNode->next = nullptr;
    if (this->listSize == 0) { // if list is empty, assign head and tail to 
        this->listBack = new_ShapeNode;
        this->listFront = new_ShapeNode;
    } else {
        this->listBack->next = new_ShapeNode; // else rewire back to point to new node
        this->listBack = new_ShapeNode;
    }
    this->listSize += 1;
}
// Remove function given the index at the position in the linked list to remove the node
void CanvasList::removeAt(int idx) {
    if (idx >= this->size() || idx < 0) { // if index out of bounds, do nothing
        return;
    } else {
        ShapeNode* curr = this->front();
        if (idx == 0) {                 // edge cases where deleted node is the head and tail, they must be reassigned
            this->listFront = curr->next;
            delete curr->value;// completely delete nodes
            delete curr;
            this->listSize -= 1;
            return;
        } else if (idx == this->size() - 1) {
            this->listBack = this->at(this->size() - 2);
        }
        for (int i = 0; i < this->size(); i++) { // loop through list to find node at idx to delete
            if (idx == i) {
                this->at(i - 1)->next = curr->next;
                delete curr->value;// completely delete nodes
                delete curr;
                this->listSize -= 1;
                return;
            }
            curr = curr->next;
        }
    }
}
// Remove Nodes at the odd number indexes
void CanvasList::removeEveryOther() {
    int j = 0;
    for (int i = 0; i < this->size(); i++) { // loop through list
        if (j % 2 == 1) { // find odd number nodes
            this->removeAt(i); // delete odd node
            i -= 1; // decrement i, as the list shrunk and increment j which keeps track of odd numbers
            j += 1;
            continue;
        }
        j += 1;
    }
}
// Function to return the Shape* at the front node after deleting that front node
Shape* CanvasList::pop_front() {
    if (this->isempty()) { // check if empty
        return nullptr;
    }
    ShapeNode* frontNode = this->front(); //create temp node to hold front node
    this->listFront = this->front()->next; //rewire list's front node to the one after
    frontNode->next = nullptr; // assign null to the popped node's next
    Shape* frontShape = frontNode->value; // save the value (shape) out of the temp node
    delete frontNode; // delete the node
    this->listSize -= 1;
    return frontShape;
}
// Function to return the Shape* at the back and remove that node from list
Shape* CanvasList::pop_back() {
    if (this->isempty()) { // check if empty
        return nullptr;
    }
    if (this->size() == 1) { // if there is one node in list
        ShapeNode* backNode = this->back(); // collect the shape from back node
        auto* backShape = backNode->value;
        delete backNode;
        this->listBack = nullptr; // and reset canvas values;
        this->listFront = nullptr;
        this->listSize = 0;
        return backShape;
    } else {                   // else collect shape from back normally
        ShapeNode* backNode = this->back();
        auto* backShape = backNode->value;
        this->at(this->size() - 2)->next = nullptr; // make 2nd to last node point to null and rewire tail pointer
        this->listBack = this->at(this->size() - 2);
        delete backNode;
        this->listSize -= 1;
        return backShape;
    }
    return nullptr;
}
// NEW function that returns a ShapeNode* when given the index of a list
ShapeNode* CanvasList::at(int idx) const {
    ShapeNode* curr = this->front();
    for (int i = 0; i < this->size(); i++) { // loop through list to find ShapeNode* at given idx
        if (i == idx) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}
// Function to return the head pointer of the list
ShapeNode* CanvasList::front() const {
    if (this->isempty()) {
        return 0;
    } else {
        return this->listFront;
    }
}
// Function to return the tail pointer of the list
ShapeNode* CanvasList::back() const {
    if (this->isempty()) {
        return 0;
    } else {
        return this->listBack;
    }
}
// Function to return a bool if the list is empty or not
bool CanvasList::isempty() const { return this->listSize == 0; };
// Function to return the size of the list
int CanvasList::size() const { return this->listSize; }
// Function to return the index of a position in the list when given the x and y coordinates of the Shape
int CanvasList::find(int x, int y) const {
    if (this->isempty()) {
        return -1;
    } else {
        ShapeNode* curr = this->listFront;
        for (int i = 0; i < this->size(); i++) { // loop through list to find if the y and x components of a shape match the given
            if (curr->value->getX() == x && curr->value->getY() == y) {
                return i;
            } else {
                curr = curr->next;
            }
        }
    } // else return -1
    return -1;
}
// Function to return the Shape* when given the index of a position in the list
Shape* CanvasList::shapeAt(int idx) const {
    if (idx < 0 || idx >= this->size()) { // edge case to check if idx is out of bounds and return nullptr
        return nullptr;
    }
    if (this->isempty()) { 
        return nullptr;
    } else {
        ShapeNode* curr = this->listFront;
        for (int i = 0; i < this->size(); i++) { // loop through list
            if (i == idx) {                      // if position found in list, return the value of the node
                return curr->value;
            } else {
                curr = curr->next;
            }
        }
    }
    return nullptr;
}
// Function to print out all the nodes
void CanvasList::draw() const {
    if (this->isempty()) {
        return;
    } else {
        ShapeNode* currNode = this->listFront;
        while (currNode != nullptr) { // loop through list of nodes and call their respective printShape()
            cout << currNode->value->printShape() << endl;
            currNode = currNode->next;
        }
    }
}
// Function to print out the addresses of every ShapeNode and Shape inside 
void CanvasList::printAddresses() const {
    for (ShapeNode* curr = this->listFront; curr->next != nullptr; curr = curr->next) { // loop through list to print out addresses 
        cout << "Node Address: " << curr << "   Shape Address: " << curr->value << endl;
        if (curr->next->next == nullptr) {
            cout << "Node Address: " << curr->next << "   Shape Address: " << curr->next->value << endl;
        }
    }
    
}