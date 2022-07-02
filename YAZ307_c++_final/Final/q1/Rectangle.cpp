#include <iostream>
#include "Rectangle.h"

std::string Rectangle::get_type() const { return "Rectangle"; }

void Rectangle::set_size() {
    
    std::cout << "Enter the short side of rectangle: ";

    std::cin >> short_side;

    std::cout << "Enter the long side of rectangle: ";

    std::cin >> long_side;

}

double Rectangle::calc_area() const { return short_side*long_side; }

double Rectangle::calc_perimeter() const { return (short_side+long_side)*2; }

double Rectangle::get_short_side() const { return short_side; }
double Rectangle::get_long_side() const { return long_side; }