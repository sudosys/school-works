#include <vector>
#include <string>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {

    public:

        Polynomial();
        Polynomial(std::vector<int>* coeff, std::vector<int>* exp);
        ~Polynomial();

        std::vector<int>* get_coefficients();
        std::vector<int>* get_exponents();

        Polynomial* add(Polynomial* poly1, Polynomial* poly2);
        Polynomial* subtract(Polynomial* poly1, Polynomial* poly2);
        Polynomial* multiply(Polynomial* poly1, Polynomial* poly2);
        std::string toString();

    private:

        std::vector<int>* coefficients;
        std::vector<int>* exponents;

};

#endif