#include <stdio.h>

//There is no need to use storage class duration keywords and modifiers according to my tests but I felt obliged to use them.

static int equilateral, isosceles, scalene;

void classify_triangles(float side1, float side2, float side3) {    
        
        if ((side1+side2+side3) <= 12 && (side1 != -1 && side2 != -1 && side3 != -1)) {
            printf("You entered a small triangle.\n");
        }

        if (side1 == -1 && side2 == -1 && side3 == -1) { //This if statement is used to not to count "-1 -1 -1" as a equilateral triangle when the operation ends.
        } else if (side1 == side2 && side2 == side3) {
            equilateral = equilateral + 1;
        } else if ((side1 == side2 && side1 != side3) || (side2 == side3 && side2 != side1) || (side1 == side3 && side1 != side2)) {
            isosceles = isosceles + 1;
        } else {
            scalene = scalene + 1;
        }
}

int main() {

    static float side1, side2, side3;

    while(1) {
        
        printf("Enter the side lengths of the triangle\n");
        scanf("%f %f %f", &side1, &side2, &side3);
        classify_triangles(side1, side2, side3);
        if (side1 == -1 && side2 == -1 && side3 == -1) {
            printf("Equilateral Triangles: %d\n", equilateral);
            printf("Isosceles Triangles: %d\n", isosceles);
            printf("Scalene Triangles: %d\n", scalene);
            break;
        }
    }

    return 0;
}