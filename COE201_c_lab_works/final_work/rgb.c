#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Color {
    int red;
    int green;
    int blue;
};

void store_color(struct Color* color, int red, int green, int blue) { 
    color->red = red;
    color->green = green;
    color->blue = blue;
}

void print_color(struct Color* color) { printf("red: %d green: %d blue: %d\n", color->red, color->green, color->blue); }

void ptg_main_colors(struct Color* color) {

    float sum = color->red + color->green + color->blue;

    printf("ptg red: %.2f\nptg green: %.2f\nptg blue: %.2f\n", color->red/sum, color->green/sum, color->blue/sum);

}

int main() {

    srand(time(0));

    int num_of_colors = 0;

    printf("Enter the number of colors: ");

    scanf("%d", &num_of_colors);

    struct Color* colors = (struct Color*) malloc(sizeof(struct Color) * num_of_colors);

    for (int i = 0; i < num_of_colors; i++) { store_color(&colors[i], rand() % 256, rand() % 256, rand() % 256); }

    float red_sum = 0, green_sum = 0, blue_sum = 0;
 
    for (int i = 0; i < num_of_colors; i++) {

        print_color(&colors[i]);
        ptg_main_colors(&colors[i]);

        red_sum += (&colors[i])->red;
        green_sum += (&colors[i])->green;
        blue_sum += (&colors[i])->blue;

    }

    printf("Percentage of each color to the number of colors:\n");

    printf("ptg red: %.2f\nptg green: %.2f\nptg blue: %.2f\n", red_sum/num_of_colors, green_sum/num_of_colors, blue_sum/num_of_colors);

    free(colors);

    colors = NULL;

    return 0;
}