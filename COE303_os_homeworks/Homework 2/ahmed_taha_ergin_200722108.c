#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 100
#define TRUE 1

char* reverse_str(char* str) {

    int i = strlen(str)-1, j = 0;

    char ch;
    
    while (i > j) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        ++j;
        --i;
    }
    
    return str;
}

int main(void) {
  
    int fd1[2], fd2[2];
    
    pid_t child;
  
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Creation of one of the pipes has failed! Aborting...");
        exit(EXIT_FAILURE);   
    }
  
    child = fork();
    
    if (child < 0) {
        perror("Forking has failed! Aborting...");
        exit(EXIT_FAILURE);
    }
    
    if (child == 0) {
        close(fd1[1]);
        close(fd2[0]);
    } else if (child > 0) {
        close(fd1[0]);
        close(fd2[1]);
    }
    
    while (TRUE) {
      
        if (child == 0) {
            
            char output_str[SIZE];
        
            read(fd1[0], output_str, SIZE);

            if (strcmp(output_str, "-1") == 0) { exit(EXIT_SUCCESS); }
      
            write(fd2[1], reverse_str(output_str), SIZE);
            
        } else if (child > 0) {

            char input_str[SIZE];
            char output_str[SIZE];

            printf("Enter the string: ");
            
            scanf("%s", input_str);
            
            if (strcmp(input_str, "-1") == 0) { 
                
                write(fd1[1], input_str, SIZE);
                
                break;
                
            }
    
            write(fd1[1], input_str, SIZE);
      
            read(fd2[0], output_str, SIZE);

            printf("Reversed string: %s\n", output_str);

        }
        
    }
  
    wait(NULL);
    exit(EXIT_SUCCESS);

}