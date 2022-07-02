#include "IShape.h"

#ifndef SQUARE_H
#define SQUARE_H

class Square : public IShape {

    public:
        std::string get_type() const override;
        void set_size() override;
        double calc_area() const override;
        double calc_perimeter() const override;
        ~Square() override {};
        double get_side() const;

    private:
        double side;

};

#endif