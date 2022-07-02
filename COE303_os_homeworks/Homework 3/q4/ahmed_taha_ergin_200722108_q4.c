#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

/*
Thread A -> A1, A2, A3
Thread B -> B1, B2, B3, B4
Thread C -> C1, C2, C3
*/

/*
A1 BEFORE C1
B1 BEFORE A2
B2 BEFORE C2
A2 BEFORE B3
C2 BEFORE A3
B4 LAST
*/

sem_t mutex;

void* show(void* data_param) {

    sem_wait(&mutex);

    const char* data = (const char*) data_param;

    for (int i = 0; i < 5; i++) {
        write(STDOUT_FILENO, data, strlen(data));
        sleep(lrand48()%3);
    }

    sem_post(&mutex);

}

int main() {

    sem_init(&mutex, 0, 1);
    pthread_t A;
    pthread_t B;
    pthread_t C;
    
    char* A_blocks[3] = {"A1","A2","A3"};
    char* B_blocks[4] = {"B1","B2","B3","B4"};
    char* C_blocks[3] = {"C1","C2","C3"};

    pthread_create(&A, NULL, &show, A_blocks[0]);
    sleep(lrand48()%3);
    pthread_create(&C, NULL, &show, C_blocks[0]);
    sleep(lrand48()%3);
    pthread_create(&B, NULL, &show, B_blocks[0]);
    sleep(lrand48()%3);
    pthread_create(&A, NULL, &show, A_blocks[1]);
    sleep(lrand48()%3);
    pthread_create(&B, NULL, &show, B_blocks[1]);
    sleep(lrand48()%3);
    pthread_create(&C, NULL, &show, C_blocks[1]);
    sleep(lrand48()%3);
    pthread_create(&A, NULL, &show, A_blocks[2]);
    sleep(lrand48()%3);
    pthread_create(&B, NULL, &show, B_blocks[2]);
    sleep(lrand48()%3);
    pthread_create(&B, NULL, &show, B_blocks[3]);
    sleep(lrand48()%3);

    pthread_join(A,NULL);
    pthread_join(B,NULL);
    pthread_join(C,NULL);

    sem_destroy(&mutex);
    return 0;
}