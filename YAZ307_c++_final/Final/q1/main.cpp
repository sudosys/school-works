#include <iostream>
#include <vector>
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

void print(std::vector<IShape*> container);

int main() {

    char choice;

    std::vector<IShape*> ishape_container;

    while(true) {
        
        std::cout << "Please enter a shape:\n";

        std::cout << "Press (s) for Square, (r) for Rectangle, (c) for Circle, (t) for Triangle or (q) to quit:\n";

        std::cin >> choice;

        if (choice == 'q') { 
            std::cout << "The user has pressed 'q'\nThe loop is terminating...\n";
            print(ishape_container);
            exit(EXIT_SUCCESS);
        } else if (choice == 's') {
            std::cout << "The user has pressed 's'\n";
            Square* square_obj = new Square();
            square_obj->set_size();
            ishape_container.push_back(square_obj);
        } else if (choice == 'r') {
            std::cout << "The user has pressed 'r'\n";
            Rectangle* rectangle_obj = new Rectangle();
            rectangle_obj->set_size();
            ishape_container.push_back(rectangle_obj);
        } else if (choice == 'c') {
            std::cout << "The user has pressed 'c'\n";
            Circle* circle_obj = new Circle();
            circle_obj->set_size();
            ishape_container.push_back(circle_obj);
        } else if (choice == 't') {
            std::cout << "The user has pressed 't'\n";
            Triangle* triangle_obj = new Triangle();
            triangle_obj->set_size();
            ishape_container.push_back(triangle_obj);
        }
    }

    // deleting each dynamically allocated shape to prevent memory leak

    for (IShape* shape_to_delete: ishape_container) { delete shape_to_delete; }

    return 0;
}

void print(std::vector<IShape*> container) {

    std::string side_info;

    for (IShape* shape: container) {

        // using dynamic_cast to determine the shape

        Square* square = dynamic_cast<Square*>(shape);
        Rectangle* rectangle = dynamic_cast<Rectangle*>(shape);
        Circle* circle = dynamic_cast<Circle*>(shape);
        Triangle* triangle = dynamic_cast<Triangle*>(shape);

        std::cout << "Shape: " << shape->get_type() << "\n";
        if (square != nullptr) { side_info += "Side: " + std::to_string(square->get_side()) + "\n"; }
        if (rectangle != nullptr) { side_info += "Sides: " + std::to_string(rectangle->get_short_side()) + " " + std::to_string(rectangle->get_long_side()) + "\n"; }
        if (circle != nullptr) { side_info += "Radius: " + std::to_string(circle->get_radius()) + "\n"; }
        if (triangle != nullptr) { side_info += "Sides: " + std::to_string(triangle->get_side1()) + " " + std::to_string(triangle->get_side2()) + " " + std::to_string(triangle->get_side3()) + "\n"; }
        std::cout << side_info;
        std::cout << "Area: " << shape->calc_area() << " m^2\n";
        std::cout << "Perimeter: " << shape->calc_perimeter() << " m\n";
        std::cout << "#################\n";

        side_info = "";

    }

}