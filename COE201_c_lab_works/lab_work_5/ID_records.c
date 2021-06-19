#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct id_record {

    int id;
    int age;
    int license_id;
    char blood_type[5];
    char name[50];
    
    struct id_record* next;

};

typedef struct id_record id_rec;

char* get_input(FILE* text_file, char file_content[50], int int_values[3]) {

    char* ptr;

    for (int i = 0; i < 3; i++) {
        
        ptr = fgets(file_content, 50, text_file);
        
        if (ptr == NULL) { break; }

        int_values[i] = atoi(file_content);
    }

    return ptr;

}

id_rec* create_node(FILE* text_file, int int_values[3]) {

    id_rec* ptr = (id_rec*) malloc(sizeof(id_rec));
    
    ptr->id = int_values[0];
    ptr->age = int_values[1];
    ptr->license_id = int_values[2];
    fgets(ptr->blood_type, sizeof(ptr->blood_type), text_file);
    ptr->blood_type[strlen(ptr->blood_type)-1] = '\0';
    fgets(ptr->name, sizeof(ptr->name), text_file);
    ptr->name[strlen(ptr->name)-1] = '\0'; 

    return ptr;
}

void print_node(id_rec* node) { printf("%d\n%d\n%d\n%s\n%s\n\n", node->id, node->age, node->license_id, node->blood_type, node->name); }

int main() {

    char file_content[50];
    int int_values[3];

    FILE* text_file = fopen("IDs.txt", "r");

    if (text_file == NULL) { perror("An error occured while trying to read the file!\n"); exit(1); }

    id_rec* curr; id_rec* head; id_rec* id;

    if (get_input(text_file, file_content, int_values) != NULL) {
        head = create_node(text_file, int_values);
        curr = head;
    }

    while (get_input(text_file, file_content, int_values) != NULL) {
        id = create_node(text_file, int_values);
        curr->next = id;
        curr = curr->next;
    }

    curr = head;

    while (curr != NULL) {
        print_node(curr);
        curr = curr->next;
    }

    id_rec* prev_node;
    
    curr = head;

    while(curr != NULL) {
        prev_node = curr;
        curr = curr->next;
        free(prev_node);
    }

    prev_node = curr = head = NULL;

    fclose(text_file);

    return 0;
}