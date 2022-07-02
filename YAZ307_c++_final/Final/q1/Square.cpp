#include <iostream>
#include "Square.h"

std::string Square::get_type() const { return "Square"; }

void Square::set_size() {
    
    std::cout << "Enter the side length of the square: ";

    std::cin >> side;

}

double Square::calc_area() const { return side*side; }

double Square::calc_perimeter() const { return side*4; }

double Square::get_side() const { return side; }