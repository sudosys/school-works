#include <iostream>
#include <cmath>
#include <algorithm>
#include "Shape.h"

// Line Class

Line::Line() { x = new double[2]; y = new double[2]; }

Line::Line(double* x_axis, double* y_axis, std::string shape_color) : x{x_axis}, y{y_axis}, color{shape_color} {};

Line::~Line() { delete x; delete y; };

void Line::toString() {
                
        std::cout << "This is a " << color << " line with coordinates\n";
            
        for (int i = 0; i < 2; i++) { std::cout << i+1 << ": " << x[i] << " " << y[i] << "\n"; }
}

double Line::area() { return std::sqrt(std::pow((std::abs(x[0]-x[1])),2)+std::pow((std::abs(y[0]-y[1])),2)); }

// VerticalLine Class

VerticalLine::VerticalLine() { y = new double[2]; }

VerticalLine::VerticalLine(double* y_axis, std::string shape_color) : y{y_axis}, color{shape_color} {};

VerticalLine::~VerticalLine() { delete y; };

void VerticalLine::toString() {
    
    std::cout << "This is a " << color << " vertical line with coordinates\n";
    
    for (int i = 0; i < 2; i++) { std::cout << i+1 << ": " << y[i] << "\n"; }
    
}

double VerticalLine::area() { return std::abs(y[0]-y[1]); };

// HorizontalLine Class

HorizontalLine::HorizontalLine() { x = new double[2]; }

HorizontalLine::HorizontalLine(double* x_axis, std::string shape_color) : x{x_axis}, color{shape_color} {};

HorizontalLine::~HorizontalLine() { delete x; };

void HorizontalLine::toString() {
    
    std::cout << "This is a " << color << " horizontal line with coordinates\n";
    
    for (int i = 0; i < 2; i++) { std::cout << i+1 << ": " << x[i] << "\n"; }
    
}

double HorizontalLine::area() { return std::abs(x[0]-x[1]); };

// Triangle Class

Triangle::Triangle() { x = new double[3]; y = new double[3]; }

Triangle::Triangle(double* x_axis, double* y_axis, std::string shape_color) : x{x_axis}, y{y_axis}, color{shape_color} {};

Triangle::~Triangle() { delete x; delete y; };

void Triangle::toString() {
    
    std::cout << "This is a " << color << " triangle with coordinates\n";
    
    for (int i = 0; i < 3; i++) { std::cout << i+1 << ": " << x[i] << " " << y[i] << "\n"; }
    
}

double Triangle::area() { return std::abs((x[0]*(y[1]-y[2])+x[1]*(y[2]-y[0])+x[2]*(y[0]-y[1]))/2); }

// Parallelogram Class

Parallelogram::Parallelogram() { x = new double[4]; y = new double[4]; }

Parallelogram::Parallelogram(double* x_axis, double* y_axis, std::string shape_color) : x{x_axis}, y{y_axis}, color{shape_color} {

    std::pair<double,double> xy[3];
    
    for (int i = 0; i < 3; i++) { xy[i].first = x[i]; xy[i].second = y[i]; }

    std::sort(xy, xy+3);

    for (int i = 0; i < 3; i++) { x[i] = xy[i].first; y[i] = xy[i].second; } 

    if ((x[0] == x[1] && x[1] == x[2]) || (y[0] == y[1] && y[1] == y[2])
    || ((x[0] == x[1]-1 && x[1] == x[2]-1) && ((y[0] == y[1]+1 && y[1] == y[2]+1)
    || (y[0] == y[1]-1 && y[1] == y[2]-1)))
    /*|| !((y[0] == y[1]) || (x[1] == x[2]))*/) { 

        for (int i = 0; i < 3; i++) { x[i] = 0; y[i] = 0; }

    } else { x[3] = x[0] + x[2] - x[1]; y[3] = y[0] + y[2] - y[1]; }

}

Parallelogram::~Parallelogram() { delete x; delete y; };

void Parallelogram::toString() {
    
    std::cout << "This is a " << color << " parallelogram with coordinates\n";
    
    for (int i = 0; i < 4; i++) { std::cout << i+1 << ": " << x[i] << " " << y[i] << "\n"; }
    
}

double Parallelogram::area() { return std::abs(y[0]-y[3])*std::sqrt(std::pow(x[0]-x[1],2)+std::pow(y[0]-y[1],2)); }

// Rectangle Class

Rectangle::Rectangle() { x = new double[4]; y = new double[4]; }

Rectangle::Rectangle(double* x_axis, double* y_axis, std::string shape_color) : x{x_axis}, y{y_axis}, color{shape_color} {

    x[2] = x[1];
    y[2] = y[0];
    x[3] = x[0];
    y[3] = y[1];

}

Rectangle::~Rectangle() { delete x; delete y; };

void Rectangle::toString() {
    
    std::cout << "This is a " << color << " rectangle with coordinates\n";
    
    for (int i = 0; i < 4; i++) { std::cout << i+1 << ": " << x[i] << " " << y[i] << "\n"; }
    
}

double Rectangle::area() { return std::abs(x[1]-x[3])*std::abs(y[0]-y[3]); }