#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <windows.h>

using namespace std;

class Hungarian
{
    public:
        
        Hungarian() {};

        vector<string> read_file(string filename) {
            
            int n = -1, m = -1;

            ifstream matrix;
            matrix.open(filename);
            matrix >> n >> m;
            string matrix_row;
            vector<string> matrix_rows;
            
            while(getline(matrix,matrix_row)) {
                
                string row;
                
                for (char x: matrix_row) {
                    
                    if (x != ' ') {
                        row.push_back(x);
                    }
                }
                
                matrix_rows.push_back(row);
            }

            return matrix_rows;

        }

        vector<vector<int>> preprocess_matrix(vector<string> matrix_rows) {
            
            vector<vector<int>> matrix;
            vector<int> preprocessed_row;
            string space_matrix;
            
            for(string row: matrix_rows) {
                
                stringstream str(row);

                while(getline(str,space_matrix,' ')) {
                    preprocessed_row.push_back((stoi(space_matrix)));
                }
                
                matrix.push_back(preprocessed_row);
                preprocessed_row.clear();
            }

            return matrix;
        }

        int find_min_row(vector<int> num_list) {

            int min_val = INT32_MAX;

            for (int number : num_list) {
                
                if(number < min_val) {
                    min_val = number;
                }
                
            }
            
            return min_val;
        }
                

        int find_min_column(vector<vector<int>> matrix, int column) {

            int min_val = INT32_MAX;

            for (vector<int> row : matrix) {
                
                if (row[column] < min_val) {
                    min_val = row[column];
                }

            }

            return min_val;
        }

        vector<vector<int>> subtract_min_from_row(vector<vector<int>> matrix) {

            int min_value = -1;

            for(int i = 0; i < matrix.size(); i++) {
                
                min_value = find_min_row(matrix[i]);
                
                for(int j = 0; j < matrix[i].size(); j++) {
                    matrix[i][j] = matrix[i][j] - min_value;
                }
            }

            return matrix;
        }

        vector<vector<int>> subtract_min_from_column(vector<vector<int>> matrix) {

            int min_value = -1;

            for(int i = 0; i < matrix.size(); i++) {
                
                min_value = find_min_column(matrix,i);
                
                for(int j = 0; j < matrix.size(); j++) {
                    matrix[j][i] = matrix[j][i] - min_value;
                }
            }

            return matrix;

        }


        int find_min_in_matrix(vector<vector<int>> matrix) {
            
            int min_val = INT32_MAX;
            vector<int> nonzero_nums_in_row;
            int val;
            
            for (vector<int> row: matrix) {
                for (int num : row) {
                    if(num > 0) {
                        val = find_min_row(nonzero_nums_in_row);
                        if(val < min_val)
                            min_val = val;
                    } else {
                        continue;
                    }
                }
                
            }
            
            return min_val;

        }

        vector<vector<int>> transpose_matrix(vector<vector<int>> matrix) {

            vector<vector<int>> transposed;

            for (int j = 0; j < matrix.size(); j++)  {
                
                for (int i = 0; i < matrix.size(); i++) {
                    transposed[j][i] = matrix[i][j];
                }
            }
            
            return transposed;
        }

        vector<vector<int>> add_to_indices(vector<vector<int>> matrix, vector<vector<int>> indices, int value) {

            for(vector<int> index_pair : indices) {
                matrix[index_pair.at(0)][index_pair.at(1)] += value;
            }

            return matrix;
        }

        bool zero_check(vector<vector<int>> matrix) {

            for (vector<int> row : matrix) {
                
                for (int number: row) {

                    if (number == 0) {

                        return true;
                    }

                }

            }

            return false;
        }

        vector<int> get_remaining_indices(vector<vector<int>> matrix) {
            
            vector<int> remaining_indices;
            
            for(int row_index = 0; row_index < matrix.size(); row_index++) {
                
                for(int column_index = 0; column_index < matrix[0].size(); column_index++) {
                    
                    if (matrix[row_index][column_index] > 0) {
                        remaining_indices.push_back((row_index,column_index));
                    }

                }
            }
            return remaining_indices;
        }

        vector<vector<int>> remove_column(vector<vector<int>> matrix, int column_index) {
            
            vector<vector<int>> modified_matrix;
            
            for (vector<int> row : matrix) {
                row[column_index] = -1;
                modified_matrix.push_back(row);
            }
            
            return modified_matrix;
        }

        int count(vector<int> row, int value) {

            int occurrence_count = 0;

            for (int i = 0; i < row.size(); i++) {
                
                if (row[i] == value) {
                    occurrence_count++;
                }

            }

            return occurrence_count;

        }

        int find_index(vector<int> row, int value) {

            for (int i = 0; i < row.size(); i++) {
                
                if (row[i] == value) {
                    return i;
                }

            }

            return -1;

        }

        void scan_rows(vector<vector<int>> matrix, vector<vector<int>>& inside_copy_matrix, vector<int>& removed_rows, vector<vector<int>>& marked_indices) {

            for(size_t i = 0; i < matrix.size(); i++) {
                inside_copy_matrix[i] = matrix[i];
            }
            
            int row_index, index;
            vector<int> row;

            for (; row_index < inside_copy_matrix.size(); row_index++) {
                
                row = inside_copy_matrix[row_index];
                
                if (count(row, 0) > 1)
                    continue;
                try {
                    index = find_index(row, 0);
                    vector<int> index_couple = {row_index, index};
                    marked_indices.push_back(index_couple);
                    removed_rows.push_back(index);
                    inside_copy_matrix = remove_column(inside_copy_matrix, index);
                }
                catch (int e) {
                    cout << "An exception occurred. Exception Nr. " << e << '\n';
                    continue;
                }
                
            }

        }

        void scan_columns(vector<vector<int>> matrix, vector<int>& removed_columns, vector<vector<int>>& reverse_marked_indices, vector<vector<int>>& original_matrix) {
            
            vector<vector<int>> marked_indices;
            vector<vector<int>> scanned_columns;
            vector<vector<int>> transposed_matrix = transpose_matrix(matrix);
            scan_rows(transposed_matrix, scanned_columns, removed_columns, marked_indices);
            original_matrix = transpose_matrix(scanned_columns);
            
            for(vector<int> index : marked_indices) {
                vector<int> reverse_couple = {index[1], index[0]};
                reverse_marked_indices.push_back(reverse_couple);
            }
                
        }

        vector<char> scan_matrix(vector<vector<int>> matrix, vector<vector<int>> scanned_matrix, vector<vector<int>> marked_indices, vector<vector<int>> zeros) {

            vector<vector<int>> rows_scanned_matrix;
            vector<int> removed_rows;
            vector<vector<int>> marked_indices;
            vector<vector<int>> columns_scanned_matrix;
            vector<int> removed_columns;
            vector<vector<int>> marked_column_indices;

            scan_rows(matrix, rows_scanned_matrix, removed_rows, marked_indices);
            
            if(zero_check(rows_scanned_matrix)) {
                scan_columns(rows_scanned_matrix, removed_columns, marked_column_indices, columns_scanned_matrix);
            }

        }

        vector<vector<int>> hungarian(vector<vector<int>> matrix) {

            vector<vector<int>> scanned_matrix;
            vector<vector<int>> marked_indices;
            vector<vector<int>> zeros;

            vector<vector<int>> subtract_matrix = subtract_min_from_column(subtract_min_from_row(matrix));
            scan_matrix(matrix, scanned_matrix, marked_indices, zeros);
            
            if(zeros.size() != matrix.size()) {
                
                int min_in_matrix = find_min_in_matrix(scanned_matrix);
                
                vector<int> remaining_indices = get_remaining_indices(scanned_matrix);
                
                vector<vector<int>> updated_matrix = add_to_indices(subtract_matrix, remaining_indices, -min_in_matrix);
                
                vector<vector<int>> updated_matrix2 = add_to_indices(updated_matrix, remaining_indices, -min_in_matrix);
                
                return hungarian(updated_matrix2);
            } else {
                return zeros;
            }

        }

        void run() {

            vector<string> matrices = {"5x5","10x10","100x100","1000x1000"};
            vector<vector<int>> matrix;
            string filename;
            ofstream file;

            file.open("test_data_c++.txt");

            for (string matrix_name: matrices)
            {

                filename = "matrices/" + matrix_name + ".txt";

                auto algo_start = std::chrono::high_resolution_clock::now();         

                matrix = preprocess_matrix(read_file(filename));
                hungarian(matrix);

                auto algo_end = std::chrono::high_resolution_clock::now();

                auto algo_duration = std::chrono::duration_cast<std::chrono::microseconds>(algo_end-algo_start);

                MEMORYSTATUSEX memory_info;
                memory_info.dwLength = sizeof(MEMORYSTATUSEX);
                GlobalMemoryStatusEx(&memory_info);
                DWORDLONG total_ram_usage = memory_info.ullTotalPageFile;

                file << matrix_name << " matrix:\n";
                file << "Execution Time (seconds): " << algo_duration.count() << "\n";
                file << "Total RAM Usage (bytes): " << total_ram_usage << "\n";
                file << "****************\n";

            }

            file.close();

        }

};


int main() {

    Hungarian hng;

    hng.run();

    return 0;
}