#include "IShape.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public IShape {

    public:
        std::string get_type() const override;
        void set_size() override;
        double calc_area() const override;
        double calc_perimeter() const override;
        ~Rectangle() override {};
        double get_short_side() const;
        double get_long_side() const;

    private:
        double short_side;
        double long_side;

};

#endif