#include <iostream>

using namespace std;

void draw_pyramid() {

    int height = 0;

    cout << "Please enter the height of the pyramid (between 1 and 40): ";

    cin >> height;

    if (height < 1 || height > 40) {
        cout << "You have entered an invalid value for height.\n";
        height = 0;
        draw_pyramid();
    }

    for (int i = 0; i < height; i++) {

        for (int b = height-1; b > i; b--) {
            cout << " ";
        }

        for (int j = 1; j <= (2*i)+1; j++) {
            cout << "*";
        }

        cout << "\n";

    }

}

void draw_star() {

    int size = 0;

    cout << "Please enter the size of the star (between 1 and 20): ";

    cin >> size;

    if (size < 1 || size > 20) {
        cout << "You have entered an invalid value for size.\n";
        size = -1;
        draw_star();
    }

    for (int i = 1; i <= (2*size+1); i++) {

        for (int j = 1; j <= (2*size+1); j++) {

            if (i == j || j == (2*size+2)-i) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        
        cout << "\n";

    }

}

void compute_fibonacci() {

    // When the index is bigger than 46, it causes an arithmetic overflow.

    int index = 0, temp = 0, fnum = 0, snum = 1; // fnum = first number, snum = second number

    cout << "Please enter the index of the Fibonacci number to be computed: ";

    cin >> index;

    if (index < 0) {
        cout << "You have entered an invalid value for index.\n";
        compute_fibonacci();
    }

    for (int i = 0; i <= index; i++) {
        cout << fnum << " ";
        temp = fnum;
        fnum = snum;
        snum = temp + fnum;
    }

    cout << "\n";
}

int main(void) {

    cout << "Welcome to my first C++ program!\n";

    int selection = 0;

    while (selection != -1) {

        cout << "Please select a task to perform (-1 to exit):\n1) Draw a pyramid\n2) Draw a star\n3) Compute the Fibonacci numbers\n";
        cin >> selection;

        if (selection == 1) {
            draw_pyramid();
        } else if (selection == 2) {
            draw_star();
        } else if (selection == 3) {
            compute_fibonacci();
        } else if (selection != -1) {
            cout << "You have entered an invalid value for selection.\n";
            continue;
        }

    }

    return 0;
}