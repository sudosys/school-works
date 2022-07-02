#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std::chrono;

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

void merge(int* array, int left_index, int middle_index, int right_index) {
    
    int temp_array[320000];

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

void partition(int* array, int first, int last, int& pivot_index) {

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

void partition_random(int* array, int first, int last, int& pivot_index) {
    
    srand(time(NULL));

    int random = first + rand() % 10 % (last - first);
    
    swap(&array[random], &array[first]);
 
    partition(array, first, last, pivot_index);
}

void quick_sort(int* array, int first, int last, bool random_pivot) {

    int pivot_index;

    if (first < last) {

        if (random_pivot) {
            partition_random(array, first, last, pivot_index);
                
            quick_sort(array, first, pivot_index-1, true);
            quick_sort(array, pivot_index+1, last, true);        
        } else {
            partition(array, first, last, pivot_index);
                
            quick_sort(array, first, pivot_index-1, false);
            quick_sort(array, pivot_index+1, last, false);

        }

    }

}

int main() {

    int sizes[6] = {10000, 20000, 40000, 80000, 160000, 320000};
    
    std::cout << "\nInsertion Sort Execution Times:\n";
    
    for (int index = 0; index < 6; index++) {
        
        int* array = new int[sizes[index]];
        
        for (int i = 0; i < sizes[index]; i++) { array[i] = rand() % 10 ; }
        
        auto starting_time = high_resolution_clock::now();
        insertion_sort(array, sizes[index]);
        auto ending_time = high_resolution_clock::now();
        
        auto elapsed_time = ending_time - starting_time;
    
        std::cout << "[size = " << sizes[index] << "] Time elapsed -> " << elapsed_time/std::chrono::milliseconds(1) << " ms\n";
        
        delete[] array;
    }
    
    std::cout << "\nMerge Sort Execution Times:\n";
    
    for (int index = 0; index < 6; index++) {
        
        int* array = new int[sizes[index]];
        
        for (int i = 0; i < sizes[index]; i++) { array[i] = rand() % 10 ; }
        
        auto starting_time = high_resolution_clock::now();
        merge_sort(array, 0, sizes[index]-1);
        auto ending_time = high_resolution_clock::now();
        
        auto elapsed_time = duration_cast<milliseconds>(ending_time - starting_time);
    
        std::cout << "[size = " << sizes[index] << "] Time elapsed -> " << elapsed_time.count() << " ms\n";
        
        delete[] array;
    }
    
    std::cout << "\nQuick Sort Execution Times (Random Pivot):\n";
    
    for (int index = 0; index < 6; index++) {
        
        int* array = new int[sizes[index]];
        
        for (int i = 0; i < sizes[index]; i++) { array[i] = rand() % 10 ; }
        
        auto starting_time = high_resolution_clock::now();
        quick_sort(array, 0, sizes[index]-1, true);
        auto ending_time = high_resolution_clock::now();
        
        auto elapsed_time = duration_cast<milliseconds>(ending_time - starting_time);
    
        std::cout << "[size = " << sizes[index] << "] Time elapsed -> " << elapsed_time.count() << " ms\n";
        
        delete[] array;
    }

    ////////

    std::cout << "\nInsertion Sort Execution Times (Sorted Array Given):\n";
    
    for (int index = 0; index < 6; index++) {
        
        int* array = new int[sizes[index]];
        
        for (int i = 0; i < sizes[index]; i++) { array[i] = rand() % 10 ; }

        insertion_sort(array, sizes[index]);
        
        auto starting_time = high_resolution_clock::now();
        insertion_sort(array, sizes[index]);
        auto ending_time = high_resolution_clock::now();
        
        auto elapsed_time = duration_cast<milliseconds>(ending_time - starting_time);
    
        std::cout << "[size = " << sizes[index] << "] Time elapsed -> " << elapsed_time.count() << " ms\n";
        
        delete[] array;
    }
    
    std::cout << "\nMerge Sort Execution Times (Sorted Array Given):\n";
    
    for (int index = 0; index < 6; index++) {
        
        int* array = new int[sizes[index]];
        
        for (int i = 0; i < sizes[index]; i++) { array[i] = rand() % 10 ; }

        insertion_sort(array, sizes[index]);
        
        auto starting_time = high_resolution_clock::now();
        merge_sort(array, 0, sizes[index]-1);
        auto ending_time = high_resolution_clock::now();
        
        auto elapsed_time = duration_cast<milliseconds>(ending_time - starting_time);
    
        std::cout << "[size = " << sizes[index] << "] Time elapsed -> " << elapsed_time.count() << " ms\n";
        
        delete[] array;
    }

    std::cout << "\nQuick Sort Execution Times (Pivot as the First Element, Sorted Array Given):\n";
    
    for (int index = 0; index < 6; index++) {
        
        int* array = new int[sizes[index]];
        
        for (int i = 0; i < sizes[index]; i++) { array[i] = rand() % 10 ; }

        insertion_sort(array, sizes[index]);
        
        auto starting_time = high_resolution_clock::now();
        quick_sort(array, 0, sizes[index]-1, false);
        auto ending_time = high_resolution_clock::now();
        
        auto elapsed_time = duration_cast<milliseconds>(ending_time - starting_time);
    
        std::cout << "[size = " << sizes[index] << "] Time elapsed -> " << elapsed_time.count() << " ms\n";
        
        delete[] array;
    }

    //insertion_sort(array, sizes[index]);
    // merge_sort(array, 0, size-1);
    // quick_sort(array, 0, size-1);
    
    return 0;
}