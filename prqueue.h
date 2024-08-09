/// @file prqueue.h
/// @author Abrar Makki
/// @date October 20, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>
#include <stack>
#include <string>
#include <map>
#include <vector>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child
    };
    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)
    
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    prqueue() {
        //create an empty priority queue
        this->root = nullptr;
        this->sz = 0;
        this->curr = nullptr;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    prqueue& operator=(const prqueue& other) {
        this->clear();
        if (other.root == nullptr) {
            return *this;
        } else {
            stack<NODE*> s;
            NODE* currNode = other.root; // pointer to current node in other tree root
            while (currNode != nullptr || !s.empty()) { // loop through other tree
                while (currNode != nullptr) { //get nodes from left subtree
                    s.push(currNode);
                    currNode = currNode->left;
                }
                currNode = s.top();// get node from stack
                s.pop();
                this->enqueue(currNode->value, currNode->priority); // add node to this tree
                if (currNode->link != nullptr) { // add all link nodes to this tree
                    NODE* currLink = currNode->link;
                    while (currLink != nullptr) {
                        this->enqueue(currLink->value, currLink->priority);
                        currLink = currLink->link;
                    }
                }
                currNode = currNode->right;
            }
            return *this;
        }
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        //loop through the tree and add all nodes to a list
        //delete all nodes in the list
        //set root to nullptr
        if (this->root == nullptr) {
            return;
        } else {
            stack<NODE*> s;
            NODE* curr = this->root;
            while (curr != nullptr || !s.empty()) {
                while (curr != nullptr) {
                    s.push(curr);
                    curr = curr->left;
                }
                curr = s.top();
                s.pop();
                if (curr->link != nullptr) {
                    NODE* currLink = curr->link;
                    while (currLink != nullptr) {
                        NODE* temp = currLink;
                        currLink = currLink->link;
                        delete temp;
                    }
                }
                NODE* temp = curr;
                curr = curr->right;
                delete temp;
            }
            this->root = nullptr;
            this->sz = 0;
            this->curr = nullptr;
        }
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~prqueue() {
        if (this->root != nullptr) {
            this->clear();
        }
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        //create a new node with the given value and priority and insert it into the BST in the correct location based on priority
        NODE* newNode = new NODE;
        newNode->value = value;
        newNode->priority = priority;
        newNode->dup = false;
        newNode->parent = nullptr;
        newNode->link = nullptr;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if (root == nullptr) { // if tree is empty then set root to new node
            root = newNode;
            this->sz++;
            return;
        } else { // if tree is not empty then find correct location to insert new node
            NODE* curr = root;
            while (curr != nullptr) {
                if (priority < curr->priority) {
                    if (curr->left == nullptr) { // check for left children and go down left subtree if priority is less than current node's priority
                        curr->left = newNode;
                        newNode->parent = curr;
                        this->sz++;
                        return;
                    } else {
                        curr = curr->left;
                    }
                } else if (priority > curr->priority) {// check for right children and go down right subtree if priority is greater than current node's priority
                    if (curr->right == nullptr) {
                        curr->right = newNode;
                        newNode->parent = curr;
                        this->sz++;
                        return;
                    } else {
                        curr = curr->right;
                    }
                } else { // priority == curr->priority
                    newNode->dup = true;
                    if (curr->dup == false) { // if there are no duplicates then add newNode to curr's link and set dup to true
                        curr->dup = true;
                        curr->link = newNode;
                        this->sz++;
                        return;
                    } else { // if there are duplicates then add newNode to the end of curr's link
                        NODE* currLink = curr->link;
                        while (currLink->link != nullptr) {
                            currLink = currLink->link;
                        }
                        currLink->link = newNode;
                        this->sz++;
                        return;
                    }
                }
            }
        }
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
        if (this->root == nullptr) { // if tree is empty then return 0
            return 0;
        } else {
            NODE* toDelete = this->root;
            while (toDelete->left != nullptr) { // find leftmost node
                toDelete = toDelete->left;
            }
            T valueOut = toDelete->value;
            if (toDelete->dup == true) { // if node has link nodes then delete link node
                if (toDelete->parent != nullptr) {// if duplicate and has parent
                    if (toDelete->parent->left == toDelete) { // if toDelete is a left child
                        toDelete->parent->left = toDelete->link;
                    } else if (toDelete->parent->right == toDelete) {
                        toDelete->parent->right = toDelete->link;
                    }
                } else { // if duplicate and has no parent
                    this->root = toDelete->link;
                }
                toDelete->link->parent = toDelete->parent; //rewire link node
                toDelete->link->left = toDelete->left;
                toDelete->link->right = toDelete->right;
                if (toDelete->link->link == nullptr) {
                    toDelete->link->dup = false;
                }
                delete toDelete;
            } else {
                if (toDelete->right != nullptr) { // not duplicate and has right child
                    if (toDelete == this->root) { // if toDelete is root
                        this->root = toDelete->right;
                        if (toDelete->parent != nullptr) { // if toDelete has parent
                            if (toDelete->parent->left == toDelete) {
                                toDelete->parent->left = toDelete->right;
                            } else if (toDelete->parent->right == toDelete) {
                                toDelete->parent->right = toDelete->right;
                            }
                        } else { // if toDelete has no parent
                            this->root->parent = nullptr;
                        }
                        delete toDelete;
                    } else { // if toDelete is not root
                        if (toDelete->parent->left == toDelete) {
                            toDelete->parent->left = toDelete->right;
                        } else if (toDelete->parent->right == toDelete) {
                            toDelete->parent->right = toDelete->right;
                        }
                        toDelete->right->parent = toDelete->parent;
                        delete toDelete;
                    }
                } else { // not duplicate and has no right child
                    if (toDelete->parent == nullptr) { // if toDelete has no parent
                        delete toDelete;
                        this->root = nullptr;
                        this->sz--;
                        return valueOut;
                    } else { // if toDelete has parent
                        if (toDelete->parent->left == toDelete) {
                            toDelete->parent->left = nullptr;
                        } else {
                            toDelete->parent->right = nullptr;
                        }
                        delete toDelete;
                    }
                }
            }
            this->sz--;
            return valueOut;
        }
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int size() {
        return this->sz;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        //set curr to the leftmost node in the tree
        NODE* curr = this->root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        this->curr = curr;
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        if (this->curr == nullptr) {
            return false;
        } else {
            value = this->curr->value;
            priority = this->curr->priority;
            // if curr has link nodes then set curr to the next link node
            if (this->curr->dup == true) {
                if (this->curr->link == nullptr && this->curr->dup == true) { // if curr has no link nodes then set curr to the next node with priority
                    this->curr = this->root;
                    //find node with priority
                    while (this->curr->priority != priority) {
                        if (this->curr->priority > priority) {
                            this->curr = this->curr->left;
                        } else {
                            this->curr = this->curr->right;
                        }
                    }
                    //go down to right subtree and find leftmost node
                    if (this->curr->right != nullptr) {
                        NODE* curr = this->curr->right;
                        while (curr->left != nullptr) {
                            curr = curr->left;
                        }
                        this->curr = curr;
                    } else { // if curr has no right subtree then go up tree until curr is a left child
                        NODE* curr = this->curr;
                        while (curr->parent != nullptr && curr->parent->left != curr) {
                            curr = curr->parent;
                        }
                        this->curr = curr->parent;
                    }
                    if (this->curr == nullptr) { // if curr is nullptr then return false
                        return false;
                    } else {
                        return true;
                    }
                }
                this->curr = this->curr->link;
                return true;
            }else if (this->curr->right != nullptr) { // if curr has right subtree then set curr to the leftmost node in the right subtree
                NODE* curr = this->curr->right;
                while (curr->left != nullptr) {
                    curr = curr->left;
                }
                this->curr = curr;
            } else {
                NODE* curr = this->curr;
                while (curr->parent != nullptr && curr->parent->left != curr) { // if curr has no right subtree then go up tree until curr is a left child
                    curr = curr->parent;
                }
                this->curr = curr->parent;
            }
            if (this->curr == nullptr) { // if curr is nullptr then return false
                return false;
            } else {
                return true;
            }
        }
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        string result;
        stack<NODE*> s; // stack to store nodes
        NODE* curr = this->root;
        while(curr != nullptr || !s.empty()) { // loop through tree
            while(curr != nullptr) { // get nodes from left subtree
                s.push(curr); // push nodes to stack
                curr = curr->left;
            }
            curr = s.top(); // get node from top of stack to retraverse tree
            s.pop();
            stringstream ss; // convert priority and value to string
            ss << curr->priority;
            string priority = ss.str();
            ss.str("");
            ss << curr->value;
            string value = ss.str();
            ss.str("");
            result += priority + " value: " + value + "\n";
            if (curr->dup == true) { // if node has link nodes then add them to result
                NODE* currLink = curr->link;
                while (currLink != nullptr) { // loop through link nodes
                    ss << currLink->priority; // convert priority and value to string
                    priority = ss.str();
                    ss.str("");
                    ss << currLink->value;
                    value = ss.str();
                    ss.str("");
                    result += priority + " value: " + value + "\n";
                    currLink = currLink->link;
                }
            }
            curr = curr->right;
        }
        return result;
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        if (this->root == nullptr) { // if tree is empty then return 0
            return 0;
        } else { // if tree is not empty then find leftmost node and return its value
            NODE* currNode = this->root;
            while (currNode->left != nullptr) {
                currNode = currNode->left;
            }
            T valueOut = currNode->value;
            return valueOut;
        }
        
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const prqueue& other) const {
        if (this->root == nullptr && other.root == nullptr) { // if both trees are empty then return true
            return true;
        } else if (this->root == nullptr || other.root == nullptr) {
            return false;
        } else if (this->sz != other.sz) { //if sizes are not equal then return false
            return false;
        } else {
            return true;
        }

    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
