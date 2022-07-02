#include "IShape.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle : public IShape {

    public:
        std::string get_type() const override;
        void set_size() override;
        double calc_area() const override;
        double calc_perimeter() const override;
        ~Triangle() override {};
        double get_side1() const;
        double get_side2() const;
        double get_side3() const;

    private:
        double side1;
        double side2;
        double side3;

};

#endif