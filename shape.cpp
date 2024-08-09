/*-------------------------------------------
Program 3: Shape & Canvas List
Course: CS 251, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */
#include <iostream>
#include <string>
#include "shape.h"
using namespace std;

// General Shape Definitions
void Shape::setX(int x) { this->x = x; } // Setter
void Shape::setY(int y) { this->y = y; } // Setter
int Shape::getX() const{ return this->x; }  // Getter
int Shape::getY() const{ return this->y; }  // Getter
Shape::Shape() { //Constructor
    this->x = 0;
    this->y = 0;
}
Shape::Shape(int x, int y) {//Constructor
    this->x = x;
    this->y = y; 
}
Shape::~Shape() {} // Deconstructor
Shape* Shape::copy() { //Copyer
    Shape* cpy = new Shape(this->x, this->y);
    return cpy;
}
string Shape::printShape() const { //Print out Details
    return "It's a Shape at x: " + to_string(this->getX()) + ", y: " + to_string(this->getY());
}
// Circle Definitions
Circle::Circle() {//Constructor
    this->setX(0);
    this->setY(0);
    this->setRadius(0);
}
Circle::Circle(int r) { this->setRadius(r); }//Constructor
Circle::Circle(int x, int y, int r) {//Constructor
    this->setX(x);
    this->setY(y);
    this->setRadius(r);
}
Circle::~Circle() {} // Deconstructor
Circle* Circle::copy() { //Copyer
    Circle* cpy = new Circle(this->x, this->y, this->radius);
    return cpy;
}
int Circle::getRadius() const { // Getter
    return this->radius;
}
void Circle::setRadius(int r) {// Setter
    this->radius = r;
}
string Circle::printShape() const { //Print out Details
    return "It's a Circle at x: " + to_string(this->getX()) + ", y: " + to_string(this->getY()) + ", radius: " + to_string(this->getRadius());
}
// Rectangle Definition
Rect::Rect() { //Constructor
    this->setX(0);
    this->setY(0);
    this->setHeight(0);
    this->setWidth(0);
}
Rect::Rect(int w, int h) { //Constructor
    this->setWidth(w);
    this->setHeight(h);
}
Rect::Rect(int x, int y, int w, int h) { //Constructor
    this->setHeight(h);
    this->setWidth(w);
    this->setX(x);
    this->setY(y);
}
Rect::~Rect() {} // Deconstructor
Rect* Rect::copy() { //Copyer
    Rect* cpy = new Rect(this->x, this->y, this->width, this->height);
    return cpy;
}

int Rect::getWidth() const { // Getter
    return this->width;
}

int Rect::getHeight() const { // Getter
    return this->height;
}

void Rect::setWidth(int w) { // Setter
    this->width = w;
}

void Rect::setHeight(int h) { // Setter
    this->height = h;
}

string Rect::printShape() const { //Print out Details
    return "It's a Rectangle at x: " + to_string(this->getX()) + ", y: " + to_string(this->getY()) + " with width: " + to_string(this->getWidth()) + " and height: " + to_string(this->getHeight());
}
//Right triangle definitions
RightTriangle::RightTriangle() { //Constructor
    this->setX(0);
    this->setY(0);
    this->setHeight(0);
    this->setBase(0);
}
RightTriangle::RightTriangle(int b, int h) { //Constructor
    this->setHeight(h);
    this->setBase(b);
}
RightTriangle::RightTriangle(int x, int y, int b, int h) { //Constructor
    this->setX(x);
    this->setY(y);
    this->setHeight(h);
    this->setBase(b);
}
RightTriangle::~RightTriangle() {} // Deconstructor
RightTriangle* RightTriangle::copy() { //Copyer
    RightTriangle* cpy = new RightTriangle(this->x, this->y, this->base, this->height);
    return cpy;
}

int RightTriangle::getBase() const { // Getter
    return this->base;
}

int RightTriangle::getHeight() const { // Getter
    return this->height;
}

void RightTriangle::setBase(int b) { // Setter
    this->base = b;
}

void RightTriangle::setHeight(int h) { // Setter
    this->height = h;
}

string RightTriangle::printShape() const { //Print out Details
    return "It's a Right Triangle at x: " + to_string(this->getX()) + ", y: " + to_string(this->getY()) + " with base: " + to_string(this->getBase()) + " and height: " + to_string(this->getHeight());
}