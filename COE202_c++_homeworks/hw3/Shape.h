#include <string>

#ifndef SHAPE_H
#define SHAPE_H

class Shape {

    public:

        Shape() = default;
        Shape(double* x_axis, double* y_axis, std::string shape_color);
        virtual ~Shape() = default;
        virtual void toString() {};
        virtual double area() = 0;

    private:

        double* x;
        double* y;
        std::string color;

};

class Line : public Shape {
    
    public:

        Line();
        Line(double* x_axis, double* y_axis, std::string shape_color);
        ~Line() override;
        void toString() override;
        double area() override;

    private:

        double* x;
        double* y;
        std::string color;

};

class VerticalLine : public Line {
    
    public:

        VerticalLine();
        VerticalLine(double* y_axis, std::string shape_color);
        ~VerticalLine() override;
        void toString() override;
        double area() override;

    private:

        double* y;
        std::string color;

};

class HorizontalLine : public Line {
    
    public:

        HorizontalLine();
        HorizontalLine(double* x_axis, std::string shape_color);
        ~HorizontalLine() override;
        void toString() override;
        double area() override;

    private:

        double* x;
        std::string color;

};

class Triangle : public Shape {
    
    public:

        Triangle();
        Triangle(double* x_axis, double* y_axis, std::string shape_color);
        ~Triangle() override;
        void toString() override;
        double area() override;

    private:

        double* x;
        double* y;
        std::string color;

};

class Parallelogram : public Shape {
    
    public:

        Parallelogram();
        Parallelogram(double* x_axis, double* y_axis, std::string shape_color);
        ~Parallelogram() override;
        void toString() override;
        double area() override;

    private:

        double* x;
        double* y;
        std::string color;

};

class Rectangle : public Parallelogram {

    public:

        Rectangle();
        Rectangle(double* x_axis, double* y_axis, std::string shape_color);
        ~Rectangle() override;
        void toString() override;
        double area() override;

    private:

        double* x;
        double* y;
        std::string color;

};

#endif