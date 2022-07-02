#include <string>

#ifndef ISHAPE_H
#define ISHAPE_H

class IShape {

    public:
        virtual std::string get_type() const = 0;
        virtual void set_size() = 0;
        virtual double calc_area() const = 0;
        virtual double calc_perimeter() const = 0;
        virtual ~IShape() {}

};

#endif