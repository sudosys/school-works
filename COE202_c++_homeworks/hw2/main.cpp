#include <iostream>
#include <vector>
#include "Polynomial.h"

int main() {

    std::vector<int>* coeff_1 = new std::vector<int>;
    std::vector<int>* exp_1 = new std::vector<int>;

    *coeff_1 = {1,2,9,13,3};
    *exp_1 = {3,2,5,6,7};

    Polynomial* poly1 = new Polynomial(coeff_1, exp_1);
    
    std::vector<int>* coeff_2 = new std::vector<int>;
    std::vector<int>* exp_2 = new std::vector<int>;

    *coeff_2 = {2,4,9,11,2};
    *exp_2 = {1,2,5,6,7};

    Polynomial* poly2 = new Polynomial(coeff_2, exp_2);

    // Polynomial* poly3 = poly1->add(poly1, poly2);
    Polynomial* poly3 = poly1->subtract(poly1, poly2);
    // Polynomial* poly3 = poly1->multiply(poly1, poly2);

    std::cout << "Polynomial 1: " << poly1->toString() << std::endl;
    std::cout << "Polynomial 2: " << poly2->toString() << std::endl;
    std::cout << "Polynomial 3: " << poly3->toString() << std::endl;

    delete poly1;
    delete poly2;
    delete poly3;

    return 0;

}