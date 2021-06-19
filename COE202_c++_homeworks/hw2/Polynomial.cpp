#include <algorithm>
#include "Polynomial.h"

Polynomial::Polynomial() {

    std::vector<int>* coefficients = new std::vector<int>;
    std::vector<int>* exponents = new std::vector<int>;

}

Polynomial::Polynomial(std::vector<int>* coeff, std::vector<int>* exp) : coefficients{coeff}, exponents{exp} {}

Polynomial::~Polynomial() {

    delete coefficients;
    delete exponents;

}

std::vector<int>* Polynomial::get_coefficients() {

    return coefficients;

}

std::vector<int>* Polynomial::get_exponents() {

    return exponents;

}

Polynomial* Polynomial::add(Polynomial* poly1, Polynomial* poly2) {

    std::vector<int>* coefficients = new std::vector<int>;
    std::vector<int>* exponents = new std::vector<int>;

    Polynomial* poly3 = new Polynomial(coefficients, exponents);

    int match = 0;

    for (int i = 0; i < poly1->get_coefficients()->size(); i++) {

        for (int j = 0; j < poly2->get_coefficients()->size(); j++) {

            if (poly1->get_coefficients()->at(i) == 0 || poly2->get_coefficients()->at(j) == 0) { continue; }

            if (poly1->get_exponents()->at(i) == poly2->get_exponents()->at(j)) {
                
                poly3->get_exponents()->push_back(poly1->get_exponents()->at(i));
                poly3->get_coefficients()->push_back(poly1->get_coefficients()->at(i)+poly2->get_coefficients()->at(j));

                match = 1;
            }

        }

        if (match == 0) {
            poly3->get_exponents()->push_back(poly1->get_exponents()->at(i));
            poly3->get_coefficients()->push_back(poly1->get_coefficients()->at(i));
        }

        match = 0;

    }

    for (int j = 0; j < poly2->get_coefficients()->size(); j++) {

        for (int i = 0; i < poly1->get_coefficients()->size(); i++) {

            if (poly2->get_exponents()->at(j) == poly1->get_exponents()->at(i)) {
                match = 1;
            }

        }

        if (match == 0) {
            poly3->get_exponents()->push_back(poly2->get_exponents()->at(j));
            poly3->get_coefficients()->push_back(poly2->get_coefficients()->at(j));
        }

        match = 0;

    }

    return poly3;

}

Polynomial* Polynomial::subtract(Polynomial* poly1, Polynomial* poly2) {

    std::vector<int>* coefficients = new std::vector<int>;
    std::vector<int>* exponents = new std::vector<int>;

    Polynomial* poly3 = new Polynomial(coefficients, exponents);

    int match = 0;

    for (int i = 0; i < poly1->get_coefficients()->size(); i++) {

        for (int j = 0; j < poly2->get_coefficients()->size(); j++) {

            if (poly1->get_coefficients()->at(i) == 0 || poly2->get_coefficients()->at(j) == 0) { continue; }

            if (poly1->get_exponents()->at(i) == poly2->get_exponents()->at(j)) {
                
                poly3->get_exponents()->push_back(poly1->get_exponents()->at(i));
                poly3->get_coefficients()->push_back(poly1->get_coefficients()->at(i)-poly2->get_coefficients()->at(j));

                match = 1;
            }

        }

        if (match == 0) {
            poly3->get_exponents()->push_back(poly1->get_exponents()->at(i));
            poly3->get_coefficients()->push_back(poly1->get_coefficients()->at(i));
        }

        match = 0;

    }

    for (int j = 0; j < poly2->get_coefficients()->size(); j++) {

        for (int i = 0; i < poly1->get_coefficients()->size(); i++) {

            if (poly2->get_exponents()->at(j) == poly1->get_exponents()->at(i)) {
                match = 1;
            }

        }

        if (match == 0) {
            poly3->get_exponents()->push_back(poly2->get_exponents()->at(j));
            poly3->get_coefficients()->push_back(poly2->get_coefficients()->at(j));
        }

        match = 0;

    }

    return poly3;

}

Polynomial* Polynomial::multiply(Polynomial* poly1, Polynomial* poly2) {
    
    std::vector<int>* coefficients = new std::vector<int>;
    std::vector<int>* exponents = new std::vector<int>;

    Polynomial* poly3 = new Polynomial(coefficients, exponents);


    for (int i = 0; i < poly1->get_coefficients()->size(); i++) {

        for (int j = 0; j < poly2->get_coefficients()->size(); j++) {

            poly3->get_coefficients()->push_back((poly1->get_coefficients()->at(i))*(poly2->get_coefficients()->at(j)));
            poly3->get_exponents()->push_back((poly1->get_exponents()->at(i))+(poly2->get_exponents()->at(j)));

        }
        
    }

    for (int i = 0; i < poly3->get_exponents()->size(); i++) {
        
        for (int j = 0; j < poly3->get_exponents()->size(); j++) {

            if((poly3->get_exponents()->at(i) == poly3->get_exponents()->at(j)) && (i != j)) {

                poly3->get_coefficients()->at(i) = poly3->get_coefficients()->at(i) + poly3->get_coefficients()->at(j);

                poly3->get_exponents()->erase(poly3->get_exponents()->begin() + (j));
                poly3->get_coefficients()->erase(poly3->get_coefficients()->begin() + (j));

            }
        
        }

    }

    return poly3;

}

std::string Polynomial::toString() {

    std::string polynomial;

    std::vector<std::pair<int,int>> exp_coeff; // first elements correspond to exponents

    for (int i = 0; i < this->get_coefficients()->size(); i++) { exp_coeff.push_back(std::make_pair(this->get_exponents()->at(i),this->get_coefficients()->at(i))); }

    std::sort(exp_coeff.begin(), exp_coeff.end());

    for (int i = 0; i < this->get_coefficients()->size(); i++) {

        while (true) {

            if (exp_coeff[i].second == 0) { break; }

            else if (exp_coeff[i].first == 1 && exp_coeff[i].second == 1) {
                polynomial += "+ " + std::string("x") + " ";
                break;
            }

            else if (exp_coeff[i].first == 0 && exp_coeff[i].second == 1) {
                polynomial += "+ " + std::string("1") + " ";
                break;
            }

            else if (exp_coeff[i].second == 1) {
                polynomial += "+ " + std::string("x") + std::string("^") + std::to_string(exp_coeff[i].first) + " ";
                break;
            }

            else if (exp_coeff[i].first == 0) {
                polynomial += "+ " + std::to_string(exp_coeff[i].second) + std::string(" ");
                break;
            }

            else if (exp_coeff[i].first == 1) {
                polynomial += "+ " + std::to_string(exp_coeff[i].second) + std::string("*") + std::string("x") + " ";
                break;
            }

            else {
                polynomial += "+ " + std::to_string(exp_coeff[i].second) + std::string("*") + std::string("x") + std::string("^") + std::to_string(exp_coeff[i].first) + " ";
                break;
            }

        }

    }

    polynomial.erase(0,2);

    return polynomial;

}