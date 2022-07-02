#include <string>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {

    public:

        struct polynomial_linked_list {
            int coefficient;
            int exponent;
            struct polynomial_linked_list* next;
        };

        Polynomial();
        Polynomial(polynomial_linked_list* polynomial);
        ~Polynomial();

        Polynomial* add(Polynomial* poly1, Polynomial* poly2);
        Polynomial* subtract(Polynomial* poly1, Polynomial* poly2);
        Polynomial* multiply(Polynomial* poly1, Polynomial* poly2);
        std::string toString();

        int get_size() const;
        polynomial_linked_list* find_node(int index) const;
        void insert_node(int index, int coef, int exp);
        void delete_node(int index);
        void retrieve_node(int index, int& coef, int& exp) const;

    private:
        polynomial_linked_list* head = new polynomial_linked_list;
        int size = 0;

};

#endif