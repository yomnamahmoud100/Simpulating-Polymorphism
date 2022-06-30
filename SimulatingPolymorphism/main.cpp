#include <iostream>

using namespace std;

struct VirtualTable;

// A base struct Shape (Base Class)
struct Shape
{
    VirtualTable* table;  //A pointer to the virtual table
};

// A struct table to hold the addresses of the functions of the (concrete) derived class
struct VirtualTable
{
    double (*GetArea) (Shape*);
    void (*PrintInfo) (Shape*);
    void (*Destroy) (Shape*);
};

//Gets the function GetArea from the virtual table based on the object that is passed to it
double GetArea(Shape* shape)
{
    return shape->table->GetArea(shape);
}

//Gets the function PrintInfo from the virtual table based on the object that is passed to it
void PrintInfo(Shape* shape)
{
    shape->table->PrintInfo(shape);
}

//Gets the function Destroy from the virtual table based on the object that is passed to it
void Destroy(Shape* shape)
{
    shape->table->Destroy(shape);
}


// A derived struct Circle (derived from Shape)
struct Circle
{
    Shape parent; //Object from type Shape that will inherit from it
    int radius;   //radius variable is specific data for this class
    double area;  //the variable area hold the value of the area in this class
};

//Calculates the area based on the their class Circle
double CircleGetArea(Circle* circle)
{
    circle->area = 3.14 * circle->radius * circle->radius;
    return circle->area;
}

//Printing the information based on the class Circle
void CirclePrintInfo(Circle* circle)
{
    cout << "Circle Information: " <<endl;
    cout << "Circle radius = " << circle->radius << endl;
    cout << endl;
}

//delete the pointer since no longer needed
void CircleDestroy(Circle* circle)
{
    delete circle;
}

//A table that holds the Circle class functions but with casting it to the base class Shape
VirtualTable circleTable =
{
    (double(*) (Shape*)) CircleGetArea,
    (void(*) (Shape *)) CirclePrintInfo,
    (void(*) (Shape *)) CircleDestroy
};

//CircleInitialize is like a constructor and knows the concrete type of the object
void CircleInitialize(Circle* circle , int radius)
{
    //make the table in the Shape (parent) holds the address of the Circle Virtual Table
    circle->parent.table = &circleTable;

    //initialize the other variables in the Circle class
    circle->radius = radius;
    circle->area = 0;
}


// A derived struct Rectangle (derived from Shape)
struct Rectangle
{
    Shape parent;  //Object from type Shape that will inherit from it
    int width;     //width variable is specific data for this class
    int height;    //height variable is specific data for this class
    double area;   //the variable area hold the value of the area in this class
};

//Calculates the area based on the their class Rectangle
double RectangleGetArea(Rectangle* rectangle)
{
    rectangle->area = rectangle->width * rectangle->height;
    return rectangle->area;
}

//printing the information based on the class Rectangle
void RectanglePrintInfo(Rectangle* rectangle)
{
    cout << "Rectangle Information: " <<endl;
    cout << "Rectangle width = " << rectangle->width << endl;
    cout << "Rectangle height = " << rectangle->height << endl;
    cout << endl;
}

//delete the pointer since no longer needed
void RectangleDestroy(Rectangle* rectangle)
{
    delete rectangle;
}

//A table that holds the Rectangle class functions but with casting it to the base class Shape
VirtualTable rectangleTable =
{
    (double(*) (Shape *)) RectangleGetArea,
    (void(*) (Shape *)) RectanglePrintInfo,
    (void(*) (Shape(*))) RectangleDestroy
};

//RectangleInitialize is like a constructor and knows the concrete type of the object
void RectangleInitialize(Rectangle* rectangle, int width , int height)
{
    //make the table in the Shape (parent) holds the address of the Rectangle Virtual Table
    rectangle->parent.table = &rectangleTable;

    //initialize the other variables in the Rectangle class
    rectangle->width = width;
    rectangle->height = height;
    rectangle->area = 0;
}


// A derived struct Ellipse (derived from Shape)
struct Ellipse
{
    Shape parent; //Object from type Shape that will inherit from it
    int radiusA;  //radiusA variable is specific data for this class
    int radiusB;  //radiusB variable is specific data for this class
    double area;  //the variable area hold the value of the area in this class
};

//Calculates the area based on the their class Ellipse
double EllipseGetArea(Ellipse* ellipse)
{
    ellipse->area = 3.14 * ellipse->radiusA * ellipse->radiusB;
    return ellipse->area;
}

//printing the information based on the class Ellipse
void EllipsePrintInfo(Ellipse* ellipse)
{
    cout << "Ellipse Information:" <<endl;
    cout << "Ellipse radiusA = " << ellipse->radiusA << endl;
    cout << "Ellipse radiusB = " << ellipse->radiusB << endl;
    cout << endl;
}

//delete the pointer since no longer needed
void EllipseDestroy(Ellipse* ellipse)
{
    delete ellipse;
}

//A table that holds the Ellipse class functions but with casting it to the base class Shape
VirtualTable ellipseTable =
{
    (double(*) (Shape*)) EllipseGetArea,
    (void(*) (Shape*)) EllipsePrintInfo,
    (void(*) (Shape*)) EllipseDestroy
};

//EllipseInitialize is like a constructor and knows the concrete type of the object
void EllipseInitialize(Ellipse* ellipse, int radiusA , int radiusB)
{
    //make the table in the Shape (parent) holds the address of the Ellipse Virtual Table
    ellipse->parent.table = &ellipseTable;

    //initialize the other variables in the Ellipse class
    ellipse->radiusA = radiusA;
    ellipse->radiusB = radiusB;
    ellipse->area = 0;
}



int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape* shapes[3];
    shapes[0] = (Shape*)&circle;
    shapes[1] = (Shape*)&rectangle;
    shapes[2] = (Shape*)&ellipse;
    double total_area = 0;
    int i;
    for (i = 0; i < 3; i++)
    {
        double d = GetArea(shapes[i]);
        total_area += d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout << total_area << endl; // check if the value is correct
    return 0;
}
