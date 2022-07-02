#include <iostream>
 
int compare(int* array, int left_index, int right_index, int searching) {
 
    int middle_index = (left_index+right_index)/2;

    if (left_index == right_index) {

        if (array[left_index] == searching) { return 1; }
        
        else if (array[left_index] != searching) { return 0; }
        
    }

    return compare(array, left_index, middle_index, searching)
           + compare(array, middle_index+1, right_index, searching);
}

bool equality_testing(int* array, int left_index, int right_index, int array_size) {
    
    int element_count = 0;
    
    for (int index = 0; index < array_size; index++) {
        element_count = compare(array, 0, array_size-1, array[index]);
        if (element_count > array_size/2) { return true; }
    }
    
    return false;
    
}

int main() {
    
    int array[] = {2,2,1,3,2,2};
    int array_size = sizeof(array)/sizeof(int);

    std::cout << equality_testing(array, 0, array_size-1, array_size);
    //returns true since 2 is repeated 4 times and array_size/2 is 3
 
    return 0;
}