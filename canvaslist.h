/// @file canvaslist.h
/// @author Adam T Koehler, PhD
/// @date October 2, 2023
/// @brief The canvaslist file contains declarations for the CanvasList
///     class that is a linked list class that mimics the drawing of 
///     shapes to a screen or space. For our simplified drawing we do
///     not use GUI but each shape in the list will output its details to
///     the console when draw is called. Initial file authored by:
///     Adam T Koehler, PhD - University of Illinois Chicago

#pragma once

#include "shape.h"

using namespace std;

// ShapeNode class used as nodes in linked list
// implemented akin to a struct as all data is public
class ShapeNode
{
    public:
        Shape *value;
        ShapeNode *next;
};

// The CanvasList class implements the functionality of a linked list.
// This linked list can contain all types of Shape and its derived classes.
class CanvasList
{
    private:
        int listSize;
        ShapeNode* listFront;
        ShapeNode* listBack;
    public:
        CanvasList();
        CanvasList(const CanvasList &);
        CanvasList& operator=(const CanvasList &);
        
        virtual ~CanvasList();
        void clear();
        
        void insertAfter(int, Shape *);
        void push_front(Shape *);
        void push_back(Shape *);
        
        void removeAt(int);
        void removeEveryOther();
        Shape* pop_front();
        Shape* pop_back();

        ShapeNode* at(int) const;
        ShapeNode* front() const;
        ShapeNode* back() const;
        bool isempty() const;
        int size() const;

        int find(int x, int y) const;
        Shape* shapeAt(int) const;
        
        void draw() const;
        void printAddresses() const;
};
