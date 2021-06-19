#include <stdio.h>

// Ahmed Taha Ergin [COE] 200722108

int main() {

    int pencil_num = 0, pen_choice, rubber_num = 0, noteb_num = 0;

    float pen_price_col = 2.0, pen_price_bl = 1.0, rubber_price = 1.50, noteb_price = 4.0, total_w_col = 0, total_w_bl = 0, discount_total_col = 0, discount_total_bl = 0;

    printf("--STOCK--\n1. Pencil: Colored 2.00, Black: 1.00\n2. Rubber: 1.50\n3. Notebook: 4.00\n");
    
    printf("Due to a system failure our shop accepts coupons only, your total must be at least 2.50\n");

    printf("Our pencils are either colored or black. If you're buying pencils please put 1 for colored and 0 for black\n");

    printf("You cannot buy both colored and black pencils at the same time.\n\n");

    printf("Please enter the number of items you will buy for all stock items.\n");

    printf("Enter 2 inputs for pencils -- number of pencils and type (1 for colored, 0 for black),\nnumber of rubbers and number of notebooks, a total of 4 inputs, 3 of them separated with commas.\n");

    printf("e.g. 2 1, 0, 2 for 2 colored pencils, no rubbers and 2 notebooks\n");

    scanf("%d %d, %d, %d", &pencil_num, &pen_choice, &rubber_num, &noteb_num);

    total_w_bl = pencil_num*pen_price_bl + rubber_num*rubber_price + noteb_num*noteb_price;

    total_w_col = pencil_num*pen_price_col + rubber_num*rubber_price + noteb_num*noteb_price;

    discount_total_col = total_w_col - (total_w_col*0.10);

    discount_total_bl = total_w_bl - (total_w_bl*0.10);

    if (pencil_num == 2 && pen_choice == 0 && rubber_num == 0 && noteb_num == 0) {
        printf("You bought only 2 black pencils. You should buy items worth at least 2.50\n");
    } else if (pencil_num == 1 && pen_choice == 1 && rubber_num == 0 && noteb_num == 0) {
        printf("You bought only 1 colored pencil. You should buy items worth at least 2.50\n");
    } else if (pencil_num == 0 && pen_choice == 0 && rubber_num == 1 && noteb_num == 0) {
        printf("You bought only 1 rubber. You should buy items worth at least 2.50\n");
    } else if (total_w_bl == 0 || total_w_col == 0) {
        printf("You changed your mind? Please come back some other time!\n");
    } else if (pencil_num < 0 || rubber_num < 0 || noteb_num < 0) {
        printf("You entered an invalid # of items for at least one of the stock items.\n");
    } else if (total_w_bl >= 10.0 && pen_choice == 0) {
        printf("Congratulations! You have a 10%% discount for spending at least 10.0!\n");
        printf("Your total is %.3f\n", discount_total_bl);
    } else if (total_w_col >= 10.0 && pen_choice == 1) {
        printf("Congratulations! You have a 10%% discount for spending at least 10.0!\n");
        printf("Your total is %.3f\n", discount_total_col);
    } else if (2.5 <= total_w_bl < 10 && pen_choice == 0) {
        printf("Your total is %.3f\n", total_w_bl);
    } else if (2.5 <= total_w_col < 10 && pen_choice == 1) {
        printf("Your total is %.3f\n", total_w_col);
    } 
   
    return 0;

}