#include <iostream>
#define MAX_SIZE 6

void selection_sort(int* array, int array_size) {

    int largest_index = 0, temp = 0;

    for (int i = array_size-1; i >= 1; --i) {
        
        largest_index = 0;
        
        for (int j = 0; j <= i; ++j) {

            if (array[j] > array[largest_index]) { largest_index = j; }

        }

        temp = array[largest_index];
        array[largest_index] = array[i];
        array[i] = temp;

    }

}

void insertion_sort(int* array, int array_size) {

    int current_element = 0, prev_index = 0;

    for (int i = 1; i < array_size; i++) {
        
        current_element = array[i];

        prev_index = i - 1;

        while (prev_index >= 0 && array[prev_index] > current_element) {
            array[prev_index+1] = array[prev_index];
            prev_index--;
        }

        array[prev_index+1] = current_element;

    }

}

void bubble_sort(int* array, int array_size) {

    bool is_sorted = false;
    int temp = 0;

    for (int i = 0; (i < array_size) && !is_sorted; ++i) {

        is_sorted = true;

        for (int j = 0; j < array_size-i; j++) {

            if (array[j] > array[j+1]) {

                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

                is_sorted = false;

            }

        }

    }


}

void merge(int* array, int left_index, int middle_index, int right_index) {
    
    int temp_array[MAX_SIZE];

    int left_first = left_index;
    int left_last = middle_index;
    int right_first = middle_index+1;
    int right_last = right_index;

    int arr_index = left_first;

    for (; (left_first <= left_last) && (right_first <= right_last); ++arr_index) {

        if (array[left_first] < array[right_first]) {
            temp_array[arr_index] = array[left_first];
            left_first++;
        } else {
            temp_array[arr_index] = array[right_first];
            right_first++;
        }
    
    }

    for (; left_first <= left_last; ++arr_index, ++left_first) { temp_array[arr_index] = array[left_first]; }
    
    for (; right_first <= right_last; ++arr_index, ++right_first) { temp_array[arr_index] = array[right_first]; }

    for (arr_index = left_index; arr_index <= right_index; ++arr_index) { array[arr_index] = temp_array[arr_index]; }

}

void merge_sort(int* array, int left_index, int right_index) {

    if (left_index == right_index) { return; }

    int middle_index = (left_index + right_index) / 2;

    merge_sort(array, left_index, middle_index);
    merge_sort(array, middle_index+1, right_index);

    merge(array, left_index, middle_index, right_index);

}

void swap(int* number1, int* number2) {

    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;

}

void partition(int* array, int first, int last, int &pivot_index) {

    int pivot = array[first];

    int last_S1 = first;
    int first_unknown = first+1;

    for (; first_unknown <= last; ++first_unknown) {

        if (array[first_unknown] < pivot) {
            ++last_S1;
            swap(&array[first_unknown], &array[last_S1]);
        }

    }

    swap(&array[first], &array[last_S1]);
    pivot_index = last_S1;

}

void quick_sort(int* array, int first, int last) {

    int pivot_index;

    if (first < last) {

        partition(array, first, last, pivot_index);

        quick_sort(array, first, pivot_index-1);
        quick_sort(array, pivot_index+1, last);

    }

}

int main() {

    int array_to_be_sorted[MAX_SIZE] = {12, 2, 45, 13, 97, 5};

    // selection_sort(array_to_be_sorted, MAX_SIZE);
    // insertion_sort(array_to_be_sorted, MAX_SIZE);
    // bubble_sort(array_to_be_sorted, MAX_SIZE);
    // merge_sort(array_to_be_sorted, 0, 5);
    quick_sort(array_to_be_sorted, 0, 5);

    for (int i = 0; i < MAX_SIZE; ++i) { std::cout << array_to_be_sorted[i] << " "; }

    return 0;
}