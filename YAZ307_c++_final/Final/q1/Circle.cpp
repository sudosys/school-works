#include <iostream>
#include "Circle.h"

#define PI 3.14159265359

std::string Circle::get_type() const { return "Circle"; }

void Circle::set_size() {
    
    std::cout << "Enter the radius of the circle: ";

    std::cin >> radius;

}

double Circle::calc_area() const { return PI*radius*radius; }

double Circle::calc_perimeter() const { return 2*PI*radius; }

double Circle::get_radius() const { return radius; }
