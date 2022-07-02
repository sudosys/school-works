#include "Polynomial.h"

Polynomial::Polynomial() : head{nullptr} {}

Polynomial::Polynomial(polynomial_linked_list* polynomial_ll) : head{polynomial_ll} {}

Polynomial::~Polynomial() { delete head; }

Polynomial* Polynomial::add(Polynomial* poly1, Polynomial* poly2) {

    Polynomial::polynomial_linked_list* poly3_ll = new Polynomial::polynomial_linked_list;

    Polynomial* poly3 = new Polynomial(poly3_ll);

    int coef1 = 0, exp1 = 0;
    int coef2 = 0, exp2 = 0;
    int index = 0;
    int match = 0;

    for (int i = 0; i < poly1->get_size(); i++) {

        poly1->retrieve_node(i, coef1, exp1);

        for (int j = 0; j < poly2->get_size(); j++) {

            poly2->retrieve_node(j, coef2, exp2);

            if (coef1 == 0 || coef2 == 0) { continue; }

            if (exp1 == exp2) {
                poly3->insert_node(index, coef1+coef2, exp1);
                index++;
                match = 1;
            }

        }

        if (match == 0) {
            poly3->insert_node(index, coef1, exp1);
            index++;
        }

        match = 0;

    }

    for (int i = 0; i < poly2->get_size(); i++) {

        poly2->retrieve_node(i, coef2, exp2);

        for (int j = 0; j < poly1->get_size(); j++) {

            poly1->retrieve_node(j, coef1, exp1);

            if (coef1 == 0 || coef2 == 0) { continue; }

            if (exp1 == exp2) { match = 1; }

        }

        if (match == 0) {
            poly3->insert_node(index, coef2, exp2);
            index++;
        }

        match = 0;

    }

    return poly3;

}

Polynomial* Polynomial::subtract(Polynomial* poly1, Polynomial* poly2) {

    Polynomial::polynomial_linked_list* poly3_ll = new Polynomial::polynomial_linked_list;

    Polynomial* poly3 = new Polynomial(poly3_ll);

    int coef1 = 0, exp1 = 0;
    int coef2 = 0, exp2 = 0;
    int index = 0;
    int match = 0;

    for (int i = 0; i < poly1->get_size(); i++) {

        poly1->retrieve_node(i, coef1, exp1);

        for (int j = 0; j < poly2->get_size(); j++) {

            poly2->retrieve_node(j, coef2, exp2);

            if (coef1 == 0 || coef2 == 0) { continue; }

            if (exp1 == exp2) {
                poly3->insert_node(index, coef1-coef2, exp1);
                index++;
                match = 1;
            }

        }

        if (match == 0) {
            poly3->insert_node(index, coef1, exp1);
            index++;
        }

        match = 0;

    }

    for (int i = 0; i < poly2->get_size(); i++) {

        poly2->retrieve_node(i, coef2, exp2);

        for (int j = 0; j < poly1->get_size(); j++) {

            poly1->retrieve_node(j, coef1, exp1);

            if (coef1 == 0 || coef2 == 0) { continue; }

            if (exp1 == exp2) { match = 1; }

        }

        if (match == 0) {
            poly3->insert_node(index, coef2, exp2);
            index++;
        }

        match = 0;

    }

    return poly3;

}

Polynomial* Polynomial::multiply(Polynomial* poly1, Polynomial* poly2) {

    Polynomial::polynomial_linked_list* poly3_ll = new Polynomial::polynomial_linked_list;

    Polynomial* poly3 = new Polynomial(poly3_ll);

    int coef1 = 0, exp1 = 0;
    int coef2 = 0, exp2 = 0;
    int index = 0;
    int match = 0;

    for (int i = 0; i < poly1->get_size(); i++) {

        poly1->retrieve_node(i, coef1, exp1);

        for (int j = 0; j < poly2->get_size(); j++) {
            
            poly2->retrieve_node(j, coef2, exp2);
            
            poly3->insert_node(index, coef1*coef2, exp1+exp2);
            index++;

        }

    }
    
    for (int i = 0; i < poly3->get_size(); i++) {

        poly3->retrieve_node(i, coef1, exp1);

        for (int j = 0; j < poly3->get_size(); j++) {

            poly3->retrieve_node(j, coef2, exp2);

            if((exp1 == exp2) && (i != j)) {
                poly3->insert_node(j, coef1+coef2, exp1);
                poly3->delete_node(j-1);
                poly3->delete_node(i);
            }

        }
    }

    return poly3;

}

std::string Polynomial::toString() {

    int coef = 0, exp = 0;
    int next_coef = 0, next_exp = 0;

    std::string poly_string;

    for (int i = 0; i < this->get_size(); i++) {
        
        this->retrieve_node(i, coef, exp);
        this->retrieve_node(i+1, next_coef, next_exp);

        if (coef == 0) { continue; }

        if (coef != 1 && coef > 0) { poly_string += std::to_string(coef); }
        else if (coef != 1 && coef < 0) { poly_string += std::to_string(coef*-1); }

        poly_string += "x";

        if (exp != 1) { poly_string += "^" + std::to_string(exp); }

        if (i != this->get_size()-1 && (next_coef > 0 || coef == 1)) { poly_string += " + "; }
        else if (i != this->get_size()-1 && next_coef < 0) { poly_string += " - "; }

    }

    return poly_string;

}

int Polynomial::get_size() const { return size; }

Polynomial::polynomial_linked_list* Polynomial::find_node(int index) const {

    polynomial_linked_list* cur = head;
    
    for (int inc = 0; inc < index; ++inc) { cur = cur->next; }
    
    return cur;

}

void Polynomial::insert_node(int index, int coef, int exp) {
    
    ++size;

    polynomial_linked_list* new_node = new polynomial_linked_list;
    new_node->coefficient = coef;
    new_node->exponent = exp;

    if (index == 0) {
        new_node->next = head;
        head = new_node;
    } else {
        polynomial_linked_list* cur = head;
        while (cur != nullptr) {
            if (cur->exponent > exp) {
                new_node->coefficient = cur->coefficient;
                new_node->exponent = cur->exponent;
                cur->coefficient = coef;
                cur->exponent = exp;
                break;
            }
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
    }
}

void Polynomial::delete_node(int index) {

    polynomial_linked_list* cur;

    --size;

    if (index == 0) {
        cur = head;
        head = head->next;
    } else {
        polynomial_linked_list* prev = find_node(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }

    cur->next = nullptr;
    delete cur;
    cur = nullptr;

}

void Polynomial::retrieve_node(int index, int& coef, int& exp) const {
    polynomial_linked_list* cur = this->find_node(index);
    coef = cur->coefficient;
    exp = cur->exponent;
}