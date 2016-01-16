#include "Rectangle.hpp"

//Construct a rectangle
Rectangle::Rectangle(float t, float b, float l, float r){
    top = t;
    bottom = b;
    left = l;
    right = r;
}

//The y-coordinate of the top side.
float Rectangle::getTop(){
    return top;
}

//The y-coordinate of the bottom side.
float Rectangle::getBottom(){
    return bottom;
}

//The x-coordinate of the left side.
float Rectangle::getLeft(){
    return left;
}

//The x-coordinate of the right side.
float Rectangle::getRight(){
    return right;
}

//Returns true if the two rectangles are overlapping in area.
bool Intersect(Rectangle rect1, Rectangle rect2){
    bool returnVal = false;

    if( (rect2.getLeft() < rect1.getRight() && rect2.getLeft() > rect1.getLeft() && rect2.getTop() < rect1.getTop() && rect2.getTop() > rect1.getBottom())
     || (rect2.getLeft() < rect1.getRight() && rect2.getLeft() > rect1.getLeft() && rect2.getBottom() < rect1.getTop() && rect2.getBottom() > rect1.getBottom())
     || (rect2.getRight() < rect1.getRight() && rect2.getRight() > rect1.getLeft() && rect2.getTop() < rect1.getTop() && rect2.getTop() > rect1.getBottom())
     || (rect2.getRight() < rect1.getRight() && rect2.getRight() > rect1.getLeft() && rect2.getBottom() < rect1.getTop() && rect2.getBottom() > rect1.getBottom())){
      returnVal = true;
    }

    return returnVal;
}

//Returns true if the point (x, y) is inside the area of the rectangle.
bool Contains(Rectangle rect, float x, float y){
    bool returnVal = false;

    if(x < rect.getRight() && x > rect.getLeft() && y < rect.getTop() && y > rect.getBottom()){
        returnVal = true;
    }

    return returnVal;
}
