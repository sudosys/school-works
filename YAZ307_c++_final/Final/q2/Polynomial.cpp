#include <iostream>
#include "Polynomial.h"

Polynomial::Polynomial() {

    std::vector<double>* coefficients = new std::vector<double>;
    std::vector<int>* exponents = new std::vector<int>;

}

Polynomial::Polynomial(std::vector<double>* coeff, std::vector<int>* exp) : coefficients{coeff}, exponents{exp} {}

Polynomial::~Polynomial() {

    delete coefficients;
    delete exponents;

}

std::vector<double>* Polynomial::get_coefficients() const { return coefficients; }

std::vector<int>* Polynomial::get_exponents() const { return exponents; }

Polynomial Polynomial::operator+(const Polynomial &poly) const {

    std::vector<double>* coefficients = new std::vector<double>;
    std::vector<int>* exponents = new std::vector<int>;

    Polynomial poly3{coefficients, exponents};

    int match = 0;

    for (int i = 0; i < this->get_coefficients()->size(); i++) {

        for (int j = 0; j < poly.get_coefficients()->size(); j++) {

            if (this->get_coefficients()->at(i) == 0 || poly.get_coefficients()->at(j) == 0) { continue; }

            // if exponents are equal, add coefficients
            if (this->get_exponents()->at(i) == poly.get_exponents()->at(j)) {
                
                poly3.get_exponents()->push_back(this->get_exponents()->at(i));
                poly3.get_coefficients()->push_back(this->get_coefficients()->at(i)+poly.get_coefficients()->at(j));

                match = 1;
            }

        }

        if (match == 0) {
            poly3.get_exponents()->push_back(this->get_exponents()->at(i));
            poly3.get_coefficients()->push_back(this->get_coefficients()->at(i));
        }

        match = 0;

    }

    for (int j = 0; j < poly.get_coefficients()->size(); j++) {

        for (int i = 0; i < this->get_coefficients()->size(); i++) {
            
            if (poly.get_exponents()->at(j) == this->get_exponents()->at(i)) { match = 1; }

        }

        if (match == 0) {
            poly3.get_exponents()->push_back(poly.get_exponents()->at(j));
            poly3.get_coefficients()->push_back(poly.get_coefficients()->at(j));
        }

        match = 0;

    }

    return poly3;
}

Polynomial Polynomial::operator-(const Polynomial &poly) const {
    
    std::vector<double>* coefficients = new std::vector<double>;
    std::vector<int>* exponents = new std::vector<int>;

    Polynomial poly3{coefficients, exponents};

    int match = 0;

    for (int i = 0; i < this->get_coefficients()->size(); i++) {

        for (int j = 0; j < poly.get_coefficients()->size(); j++) {

            if (this->get_coefficients()->at(i) == 0 || poly.get_coefficients()->at(j) == 0) { continue; }

            if (this->get_exponents()->at(i) == poly.get_exponents()->at(j)) {
                
                poly3.get_exponents()->push_back(this->get_exponents()->at(i));
                poly3.get_coefficients()->push_back(this->get_coefficients()->at(i)-poly.get_coefficients()->at(j));

                match = 1;
            }

        }

        if (match == 0) {
            poly3.get_exponents()->push_back(this->get_exponents()->at(i));
            poly3.get_coefficients()->push_back(this->get_coefficients()->at(i));
        }

        match = 0;

    }

    for (int j = 0; j < poly.get_coefficients()->size(); j++) {

        for (int i = 0; i < this->get_coefficients()->size(); i++) {

            if (poly.get_exponents()->at(j) == this->get_exponents()->at(i)) { match = 1; }

        }

        if (match == 0) {
            poly3.get_exponents()->push_back(poly.get_exponents()->at(j));
            poly3.get_coefficients()->push_back(poly.get_coefficients()->at(j));
        }

        match = 0;

    }

    return poly3;

}

Polynomial Polynomial::operator*(const Polynomial &poly) const {

    std::vector<double>* coefficients = new std::vector<double>;
    std::vector<int>* exponents = new std::vector<int>;

    Polynomial poly3{coefficients, exponents};

    for (int i = 0; i < this->get_coefficients()->size(); i++) {

        for (int j = 0; j < poly.get_coefficients()->size(); j++) {

            // multiply the coefficients and add the exponents
            poly3.get_coefficients()->push_back((this->get_coefficients()->at(i))*(poly.get_coefficients()->at(j)));
            poly3.get_exponents()->push_back((this->get_exponents()->at(i))+(poly.get_exponents()->at(j)));

        }
        
    }

    return poly3;

}

void Polynomial::printPolynomial() {

    std::cout << "Coef Array = [ ";

    for (int i = 0; i < this->get_coefficients()->size(); i++) {
        std::cout << std::to_string(this->get_coefficients()->at(i)) << " ";
    }

    std::cout << "]\n";
    
    std::cout << "Expo Array = [ ";

    for (int i = 0; i < this->get_exponents()->size(); i++) {
        std::cout << std::to_string(this->get_exponents()->at(i)) << " ";
    }

    std::cout << "]\n";

}