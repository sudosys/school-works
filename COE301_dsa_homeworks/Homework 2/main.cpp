#include <iostream>
#include "Polynomial.h"

int main() {

    int coef = 0, exp = 0;

    Polynomial::polynomial_linked_list* poly1_ll = new Polynomial::polynomial_linked_list;
    Polynomial::polynomial_linked_list* poly2_ll = new Polynomial::polynomial_linked_list;

    Polynomial* poly1 = new Polynomial(poly1_ll);
    poly1->insert_node(0, 1, 3);
    poly1->insert_node(1, 2, 2);
    poly1->insert_node(2, 9, 5);

    Polynomial* poly2 = new Polynomial(poly2_ll);
    poly2->insert_node(0, 2, 1);
    poly2->insert_node(1, 4, 2);
    poly2->insert_node(2, 9, 5);

    Polynomial* poly3 = poly1->add(poly1, poly2);
    // Polynomial* poly3 = poly1->subtract(poly1, poly2);
    // Polynomial* poly3 = poly1->multiply(poly1, poly2);

    std::cout << "Polynomial 1: " << poly1->toString() << std::endl;
    std::cout << "Polynomial 2: " << poly2->toString() << std::endl;
    std::cout << "Polynomial 3: " << poly3->toString() << std::endl;

    delete poly1;
    delete poly2;
    delete poly3;

    return 0;

}