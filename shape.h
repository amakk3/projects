/// @file shape.h
/// @author NO NAME
/// @date October 2, 2023
/// @brief The shape file contains declarations for the Shape
///     class and its derived classes to be used with CanvasList.
///     Initial file authored by:
///     Adam T Koehler, PhD - University of Illinois Chicago

#pragma once

#include <string>

using namespace std;

class Shape
{
    protected:
        int x;
        int y;

    public: 
        Shape();
        Shape(int x, int y);

        virtual ~Shape();
        virtual Shape* copy();

        int getX() const;
        int getY() const;
        void setX(int);
        void setY(int);
        
        virtual string printShape() const;
};


class Circle : public Shape 
{
    private:
        int radius;

    public: 
        Circle();
        Circle(int r);
        Circle(int x, int y, int r);
  
        virtual ~Circle();
        virtual Circle* copy();
        
        int getRadius() const;
        void setRadius(int);
        
        virtual string printShape() const;
};


class Rect : public Shape 
{
    private:
        int width;
        int height;

    public: 
        Rect();
        Rect(int w, int h);
        Rect(int x, int y, int w, int h);
        
        virtual ~Rect();
        virtual Rect* copy();
        
        int getWidth() const;
        int getHeight() const;
        void setWidth(int);
        void setHeight(int);
        
        virtual string printShape() const;
};

class RightTriangle : public Shape 
{
    private:
        int base;
        int height;

    public: 
        RightTriangle();
        RightTriangle(int b, int h);
        RightTriangle(int x, int y, int b, int h);
        
        virtual ~RightTriangle();
        virtual RightTriangle* copy();
        
        int getBase() const;
        int getHeight() const;
        void setBase(int);
        void setHeight(int);

        virtual string printShape() const;
};


// DO NOT REMOVE - USED BY AUTOGRADER
#include "moreshapes.h"
// DO NOT REMOVE - USED BY AUTOGRADER