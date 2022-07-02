from cmath import inf
import copy, time, os, psutil

def read_matrix(file_path):

    file = open(file_path, "r")

    matrix_rows = []

    for row in file.readlines():

        matrix_rows.append(row.replace("\n", ""))
    
    file.close()
    
    return matrix_rows

def preprocess_matrix(matrix_rows):

    matrix = []

    preprocessed_row = []

    for row in matrix_rows:

        for number in row.split(" "):

            preprocessed_row.append(int(number))
        
        matrix.append(preprocessed_row)
        preprocessed_row = []
    
    return matrix

def find_min_row(num_list):

    min_val = inf

    for number in num_list:
        if number < min_val:
            min_val = number
    
    return min_val

def find_min_column(matrix, column):

    min_val = inf

    for row in matrix:

        if row[column] < min_val:
            min_val = row[column]
    
    return min_val

def subtract_min_from_row(matrix):

    for i in range(len(matrix)):

        min_value = find_min_row(matrix[i])

        for j in range(len(matrix[i])):
            matrix[i][j] = matrix[i][j] - min_value
    
    return matrix

def subtract_min_from_column(matrix):

    for i in range(len(matrix)):

        min_value = find_min_column(matrix,i)

        for j in range(len(matrix)):
            matrix[j][i] = matrix[j][i] - min_value
    
    return matrix

def find_min_in_matrix(matrix):
    
    min_val = inf

    nonzero_nums_in_row = []

    for row in matrix:

        nonzero_nums_in_row = [num for num in row if num > 0]

        if (len(nonzero_nums_in_row) > 0):
            val = find_min_row(nonzero_nums_in_row)
            if (val < min_val):
                min_val = val
        else:
            continue
    
    return min_val

def transpose_matrix(matrix):

    transposed = [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]

    return transposed

def add_to_indices(matrix, indices, value):

    for row_index, column_index in indices:
        matrix[row_index][column_index] += value

    return matrix

def zero_check(matrix):

    for row in matrix:

        if 0 in row:
            return True
        
    return False

def get_remaining_indices(matrix):

    remaining_indices = []

    for row_index in range(len(matrix)):
        for column_index in range(len(matrix[0])):
            if matrix[row_index][column_index] > 0:
                remaining_indices.append((row_index, column_index))
    
    return remaining_indices

def remove_column(matrix, column_index):

    modified_matrix = []

    for row in matrix:
        row[column_index] = -1
        modified_matrix.append(row)
    
    return modified_matrix

def scan_rows(matrix):

    inside_copy_matrix = copy.deepcopy(matrix)

    removed_rows = []
    marked_indices = []

    for row_index in range(len(inside_copy_matrix)):

        row = inside_copy_matrix[row_index]

        if row.count(0) > 1:
            continue

        try:
            index = row.index(0)
            marked_indices.append((row_index, index))
            removed_rows.append(index)
            inside_copy_matrix = remove_column(inside_copy_matrix, index)
        except Exception:
            continue
        
    return inside_copy_matrix, removed_rows, marked_indices

def scan_columns(matrix):
    
    transposed_matrix = transpose_matrix(matrix)

    scanned_columns, removed_columns, marked_indices = scan_rows(transposed_matrix)

    original_matrix = transpose_matrix(scanned_columns)

    reverse_marked_indices = []

    for index in marked_indices:
        reverse_marked_indices.append((index[1], index[0]))

    return original_matrix, removed_columns, reverse_marked_indices

def scan_matrix(matrix):

    rows_scanned_matrix, removed_rows, marked_row_indices = scan_rows(matrix)

    if zero_check(rows_scanned_matrix):
        columns_scanned_matrix, removed_columns, marked_column_indices = scan_columns(rows_scanned_matrix)
    
    return (columns_scanned_matrix, [(column, row) for row in removed_rows for column in removed_columns], marked_row_indices+marked_column_indices)

def hungarian(matrix):
    
    subtracted_matrix = subtract_min_from_column(subtract_min_from_row(matrix))
    scanned_matrix, marked_indices, zeros = scan_matrix(matrix)

    if len(zeros) != len(matrix):
        min_in_matrix = find_min_in_matrix(scanned_matrix)
        remaining_indices = get_remaining_indices(scanned_matrix)
        updated_matrix = add_to_indices(subtracted_matrix, marked_indices, min_in_matrix)
        updated_matrix2 = add_to_indices(updated_matrix, remaining_indices, -min_in_matrix)
        return hungarian(updated_matrix2)
    
    return zeros

############# TEST #############

def print_assignments(assignments):
    
    assignments.sort(key = lambda tup: tup[0])
    
    for assignment in assignments:
        print("worker {} -> job {}".format(assignment[0] + 1,assignment[1] + 1))

test_data = open("test_data_py.txt", "w")

matrix_list = ["5x5","10x10","100x100","1000x1000"]

for matrix in matrix_list:
    start = time.time()
    original_matrix = preprocess_matrix(read_matrix(f"matrices/5x5.txt"))
    solution = hungarian(original_matrix)
    end = time.time()

    execution_time = end - start

    process = psutil.Process(os.getpid())

    exec_time = "Execution Time (seconds): " + str(execution_time) + "\n"

    ram_usage = "Total RAM Usage (bytes):" + str(process.memory_info().rss)

    matrix_header = matrix + " matrix:" +"\n"

    test_data.write(matrix_header)

    test_data.write(exec_time)

    test_data.write(ram_usage)
    
    test_data.write("\n****************\n")

print_assignments(solution)