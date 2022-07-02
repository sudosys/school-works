#include "IShape.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public IShape {

    public:
        std::string get_type() const override;
        void set_size() override;
        double calc_area() const override;
        double calc_perimeter() const override;
        ~Circle() override {};
        double get_radius() const;

    private:
        double radius;

};

#endif