#include <iostream>
#include <cmath>
#include "Triangle.h"

std::string Triangle::get_type() const { return "Triangle"; }

void Triangle::set_size() {
    
    std::cout << "Enter the first side of the circle: ";
    
    std::cin >> side1;

    std::cout << "Enter the second side of the circle: ";
    
    std::cin >> side2;

    std::cout << "Enter the third side of the circle: ";

    std::cin >> side3;

}

double Triangle::calc_area() const { 
    double semi_perimeter = (side1+side2+side3)/2;
    return sqrt(semi_perimeter*(semi_perimeter-side1)*(semi_perimeter-side2)*(semi_perimeter-side3));
}

double Triangle::calc_perimeter() const { return side1+side2+side3; }

double Triangle::get_side1() const { return side1; }
double Triangle::get_side2() const { return side2; }
double Triangle::get_side3() const { return side3; }