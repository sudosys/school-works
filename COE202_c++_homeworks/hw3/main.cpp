#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Shape.h"

int main() {

    srand(time(0));

    std::cout << std::fixed << std::setprecision(2);

    std::vector<Shape*> shapes;
    std::vector<std::string> colors = {"red","green","blue","yellow","orange","black","white"};

    int color_rand;
    int shape_rand;
    double coord1_rand;
    double coord2_rand;
    double coord3_rand;
    double coord4_rand;
    double coord5_rand;
    double coord6_rand;
    double coord7_rand;
    double coord8_rand;

    for(int i = 0; i < 10000; i++) {
    
        color_rand = rand() % 7;
        shape_rand = rand() % 5;
        coord1_rand = double(rand())/RAND_MAX;
        coord2_rand = double(rand())/RAND_MAX;
        coord3_rand = double(rand())/RAND_MAX;
        coord4_rand = double(rand())/RAND_MAX;
        coord5_rand = double(rand())/RAND_MAX;
        coord6_rand = double(rand())/RAND_MAX;
        coord7_rand = double(rand())/RAND_MAX;
        coord8_rand = double(rand())/RAND_MAX;

        if (shape_rand == 0) {
            double* x = new double[2]{coord1_rand,coord2_rand};
            double* y = new double[2]{coord3_rand,coord4_rand};
            shapes.push_back(new Line(x, y, colors.at(color_rand)));
        } else if (shape_rand == 1) {
            double* y = new double[2]{coord1_rand,coord2_rand};
            shapes.push_back(new VerticalLine(y, colors.at(color_rand)));
        } else if (shape_rand == 2) {
            double* x = new double[2]{coord1_rand,coord2_rand};
            shapes.push_back(new HorizontalLine(x, colors.at(color_rand)));
        } else if (shape_rand == 3) {
            double* x = new double[3]{coord1_rand,coord2_rand,coord3_rand};
            double* y = new double[3]{coord4_rand,coord5_rand,coord6_rand};
            shapes.push_back(new Triangle(x, y, colors.at(color_rand)));
        } else if (shape_rand == 4) {
            double* x = new double[4]{coord1_rand,coord2_rand,coord3_rand};
            double* y = new double[4]{coord4_rand,coord5_rand,coord6_rand};
            shapes.push_back(new Parallelogram(x, y, colors.at(color_rand)));
        } else if (shape_rand == 5) {
            double* x = new double[4]{coord1_rand,coord2_rand};
            double* y = new double[4]{coord3_rand,coord4_rand};
            shapes.push_back(new Rectangle(x, y, colors.at(color_rand)));
        }

    }
    
    int index_rand;

    for (int i = 0; i < 3; i++) {

        index_rand = rand() % 10000;
        // I only printed 3 random shapes' areas by calling the area function here
        // I didn't call the toString function or anything else since that is what you asked in the homework.
        // But in case you want to see the output returned by the toString function, I commented the statement down below (line 77).
        // Then I printed the total number of triangles and the average area of them (line 96 and 97).
        std::cout << "Area of shape " << i+1 << " = " << shapes.at(index_rand)->area() << "\n";
        // shapes.at(index_rand)->toString();
    }

    int tri_count = 0;
    double tri_area_avg = 0;

    for (Shape* MyShape : shapes) {

        Triangle* MyTriangle = dynamic_cast<Triangle*>(MyShape);

        if (MyTriangle != nullptr) {
            tri_count++;
            tri_area_avg += MyTriangle->area();
        }

    }

    tri_area_avg /= tri_count;

    std::cout << "Total number of triangles (out of 10,000): " << tri_count << "\n";
    std::cout << "Average area value of the triangles: " << std::setprecision(4) << tri_area_avg << "\n";
    // The average area value of the triangles converges to 0.08

    for (Shape* Shape_to_Delete : shapes) { delete Shape_to_Delete; }

    return 0;
}