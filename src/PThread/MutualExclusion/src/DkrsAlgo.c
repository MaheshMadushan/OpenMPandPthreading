#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 2
#define PROCESS_COUNT 2
#define PROCESS_A_ID 0
#define PROCESS_B_ID 1

int turn = PROCESS_A_ID;
int shared_variable = 0;

void* process_A(void* flags);
void* process_B(void* flags);

int main(int arg_count, char* argv[]){

    int flags[PROCESS_COUNT];
    pthread_t* thread_handles;

    printf("This program demonstrate dekker's algorithm for achieve mutual exclusion on two process with a critical section\n");

    thread_handles = malloc(THREAD_COUNT * sizeof(pthread_t));

    pthread_create(&thread_handles[0], NULL, (void*) process_A, (void *) &flags);
    pthread_create(&thread_handles[1], NULL, (void*) process_B, (void *) &flags);

    for(int thread = 0; thread < THREAD_COUNT; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    printf("%d\n",shared_variable);

    free(thread_handles);

    return 0;
}

void* process_A(void* flags){

    int * ptr_to_flags = (int*) flags;

    // non critical section
    ptr_to_flags[PROCESS_B_ID] = 0;
    while(turn == PROCESS_B_ID){
        ptr_to_flags[PROCESS_A_ID] = 0;
        while(ptr_to_flags[PROCESS_A_ID] == 0){
            
        }
    }

    // critical section
    printf("in As critical section\n");
    for (size_t i = 0; i < 100; i++)
    {
        shared_variable++;
    }
    printf("%d\n",shared_variable);
    

    turn = PROCESS_B_ID;
    ptr_to_flags[PROCESS_B_ID] = 1;
    return NULL;
}

void* process_B(void* flags){

    int * ptr_to_flags = (int*) flags;

    // non critical section
    ptr_to_flags[PROCESS_A_ID] = 0;

    while(turn == PROCESS_A_ID){
        ptr_to_flags[PROCESS_B_ID] = 0;
        while(ptr_to_flags[PROCESS_B_ID] == 0){
            
        }
    }

    // critical section
    printf("in Bs critical section\n");
    for (size_t i = 0; i < 100; i++)
    {
        shared_variable++;
    }
    printf("%d\n",shared_variable);

    turn = PROCESS_A_ID;
    ptr_to_flags[PROCESS_A_ID] = 1;
    return NULL;
}