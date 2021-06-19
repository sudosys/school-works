#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_OF_KEYWORDS 3

int sentence_counter(char file_char_content[]) {

    int sentence_count = 0;

    char* sentence = strtok(file_char_content, ".");

    while (sentence != NULL) {
        sentence_count++;
        sentence = strtok(NULL, ".");
    }

    return sentence_count;

}

int freq[NUM_OF_KEYWORDS];

void get_freq(char* curr_str, char keywords[NUM_OF_KEYWORDS][50]) {

    for (int i = 0; i < NUM_OF_KEYWORDS; i++) {

        if ((strstr(keywords[i], curr_str) != NULL) && ((strlen(curr_str) != 1) && (strlen(curr_str) != 2))) { freq[i]++; }

    }

}

void get_years(char* curr_str) {
	
	int index = 0;

	char* temp = curr_str;

	for (; *temp; temp++) { if(isalnum(*temp)) { curr_str[index++] = *temp; } }

	curr_str[index] = '\0';

	if(strlen(curr_str) == 4 && atoi(curr_str)) { printf("%s, ", curr_str); }

}

int main() {

    char file_char_content[1000],
    file_content[1000][50],
    file_name[50],
    book_info[NUM_OF_KEYWORDS][50];
    
    int paragraph_count = 0,
    curr_par_sen_count = 0,
    prev_par_sen_count = 0,
    highest_par_sen_count = 0,
    highest_sen_par_index = 0,
    word_index = 0;

    printf("Enter the name of the file: ");
    fgets(file_name, 50, stdin);

    file_name[strlen(file_name)-1] = '\0';
    
    FILE* text_file = fopen(file_name, "r");

    if (text_file == NULL) { perror("File not found!"); exit(1); }

    printf("Enter the name of the book, the author and the protagonist:\n");

    for (int i = 0; i < NUM_OF_KEYWORDS; i++) { fgets(book_info[i], 50, stdin); }

    while (fgets(file_char_content, 1000, text_file) != NULL) {
        
        file_char_content[strcspn(file_char_content, "\n")] = '\0';

        curr_par_sen_count = sentence_counter(file_char_content);
        
        if (curr_par_sen_count != 0) {
            printf("num of sentences in this paragraph: %d\n", curr_par_sen_count);
            paragraph_count++;
                
            if (curr_par_sen_count > prev_par_sen_count) {
                highest_par_sen_count = curr_par_sen_count;
                highest_sen_par_index++;
            }

            prev_par_sen_count = curr_par_sen_count;
        }

    }

    printf("There are %d paragraphs in total\n", paragraph_count);
    printf("paragraph %d has the most number of sentences: %d\n", highest_sen_par_index, highest_par_sen_count);

    rewind(text_file);

    while (fscanf(text_file, "%s", file_content[word_index]) != EOF) {
        get_freq(file_content[word_index], book_info);
        get_years(file_content[word_index]);
        word_index++;
    }

    printf("\nnum of Fahrenheit 451: %d\n", freq[0]);
    printf("num of Ray Bradbury: %d\n", freq[1]);
    printf("num of Guy Montag: %d\n", freq[2]);

    fclose(text_file);

    return 0;
}