#include <iostream>
#include <vector>
#include "Polynomial.h"

int main() {

    // 1x^3 + 2x^2

    std::vector<double>* coeff_1 = new std::vector<double>;
    std::vector<int>* exp_1 = new std::vector<int>;

    *coeff_1 = {1,2};
    *exp_1 = {3,2};

    Polynomial poly1{coeff_1, exp_1};

    // 2x^5 + 4x^2
    
    std::vector<double>* coeff_2 = new std::vector<double>;
    std::vector<int>* exp_2 = new std::vector<int>;

    *coeff_2 = {2,4};
    *exp_2 = {5,2};

    Polynomial poly2{coeff_2, exp_2};

    Polynomial poly3 = poly1+poly2;
    Polynomial poly4 = poly1-poly2;
    Polynomial poly5 = poly1*poly2;

    std::cout << "First Polynomial:\n";
    poly1.printPolynomial();
    std::cout << "#################\n";
    
    std::cout << "Second Polynomial:\n";
    poly2.printPolynomial();
    std::cout << "#################\n";
    
    std::cout << "Third Polynomial (First Poly + Second Poly):\n";
    poly3.printPolynomial();
    std::cout << "#################\n";
    
    std::cout << "Fourth Polynomial (First Poly - Second Poly):\n";
    poly4.printPolynomial();
    std::cout << "#################\n";
    
    std::cout << "Fifth Polynomial (First Poly * Second Poly):\n";
    poly5.printPolynomial();

    return 0;

}