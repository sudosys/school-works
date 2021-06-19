#include <stdio.h>

int main() {

    int op_num, number, result;

    printf("Start entering the series with an operator.\n");
    printf("Operators allowed are -1(multiplication) and -2(summation).\n");
    printf("Enter -3 to stop the series.\n");

    scanf("%d", &op_num);

    if (op_num == -1) {
        multip:
        result = 1;
        printf("Enter the numbers for multiplication.\n");
        while(1) {
            scanf("%d", &number);
            result *= number;
            if (number == -3) {
                result /= -3;
                printf("result: %d.\n", result);
                break; 
            } else if (number == -1) {
                result /= -1;
                printf("result: %d.\n", result);
                goto multip;
            } else if (number == -2) {
                result /= -2;
                printf("result: %d.\n", result);
                goto sum;
            } else if (number < 0 && number != -3) {
                result /= number;
                printf("result: %d.\n", result);
                printf("You entered an invalid operator.\n");
                break;
            }
        }
    } else if (op_num == -2) {
        sum:
        result = 0;
        printf("Enter the numbers for summation.\n");
        while(1) {
            scanf("%d", &number);
            result += number;
            if (number == -3) {
                result += 3;
                printf("result: %d.\n", result);
                break;
            } else if (number == -1) {
                result += 1;
                printf("result: %d.\n", result);
                goto multip;
            } else if (number == -2) {
                result += 2;
                printf("result: %d.\n", result);
                goto sum;
            } else if (number < 0 && number != -3) {
                result -= number;
                printf("result: %d.\n", result);
                printf("You entered an invalid operator.\n");
                break;
            }
        }
    } else {
        printf("You have to start with a valid operator.\n");
    }

    return 0;
}