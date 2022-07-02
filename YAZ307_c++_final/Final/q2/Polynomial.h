#include <vector>
#include <string>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {

    public:

        Polynomial();
        Polynomial(std::vector<double>* coeff, std::vector<int>* exp);
        ~Polynomial();

        std::vector<int>* get_exponents() const;
        std::vector<double>* get_coefficients() const;

        Polynomial operator+(const Polynomial &poly) const;
        Polynomial operator-(const Polynomial &poly) const;
        Polynomial operator*(const Polynomial &poly) const;
        void printPolynomial();

    private:

        std::vector<int>* exponents;
        std::vector<double>* coefficients;

};

#endif