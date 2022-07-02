#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_OF_THREADS 4

int** matrix_array;
int matrix_sum = 0;
int matrix_size = 0;

void* sum_submatrix(void* region) {

    /*
    region 1 is top-left
    region 2 is top-right
    region 3 is lower-left
    region 4 is lower-right
    */
    
    int* regionc = (int*)region;

    for (int i = 0; i < matrix_size/2; i++) {
        for (int j = 0; j < matrix_size/2; j++) {
            if (*regionc == 1) { matrix_sum += matrix_array[i][j]; }
            else if (*regionc == 2) { matrix_sum += matrix_array[i][j+matrix_size/2]; }
            else if (*regionc == 3) { matrix_sum += matrix_array[i+matrix_size/2][j]; }
            else if (*regionc == 4) { matrix_sum += matrix_array[i+matrix_size/2][j+matrix_size/2]; }
        }
    }
    
}

int main() {

    FILE* matrix = fopen("matrix.txt", "r");
    char ch;
    char row[256];
    char* number;
    int row_index = 0, column_index = 0;
    int matrix_sum_mthread = 0;
    pthread_t thread;

    while ((ch = fgetc(matrix)) != EOF) {
        if (ch == '\n') { matrix_size++; }
    }

    matrix_size++;

    matrix_array = (int**)malloc(matrix_size * sizeof(int));
    for (int i = 0; i < matrix_size; i++) { matrix_array[i] = (int*)malloc(matrix_size * sizeof(int)); }

    rewind(matrix);

    while (fgets(row, sizeof(row), matrix) != NULL) {
        number = strtok(row, " ");
        while (number != NULL) {
            matrix_array[row_index][column_index] = atoi(number);
            number = strtok(NULL, " ");
            column_index++;
        }
        column_index = 0;
        row_index++;
    }

    for (int i = 1; i <= NUM_OF_THREADS; i++) {
        pthread_create(&thread, NULL, &sum_submatrix, &i);
        pthread_join(thread, NULL);
    }

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            matrix_sum_mthread += matrix_array[i][j];
        }
    }

    printf("Summation calculated by worker threads -> %d\n", matrix_sum);

    printf("Summation calculated by main thread -> %d\n", matrix_sum_mthread);

    if (matrix_sum == matrix_sum_mthread) {
        printf("Summation calculated by worker threads and main thread is equal!\n");
    }

    free(matrix_array);
    
    pthread_exit(NULL);

    fclose(matrix);

    return 0;
}
