#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 2
#define PROCESS_COUNT 2
#define TURN_INDEX 0
#define SIGNAL_ // find name for signals

void* process_A(void* turn, void* flags);
void* process_B(void* turn, void* flags);

int main(int arg_count, char* argv[]){
    
    int flags[PROCESS_COUNT];
    pthread_t* thread_handles;

    printf("This program demonstrate dekker's algorithm for achieve mutual exclusion on two process with a critical section");

    thread_handles = malloc(THREAD_COUNT * sizeof(pthread_t));

    pthread_create(&thread_handles[0], NULL, (void*) Hello, (void *) 0);
    
    for(thread = 0; thread < THREAD_COUNT; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);
    return 0;
}

void* process_A(void* turn, void* flags){
    long _thread_rank = (long) thread_rank;
    printf("hello from %ld thread out of %d threads\n",_thread_rank,THREAD_COUNT);
    return NULL;
}

void* process_B(void* turn, void* flags){
    long _thread_rank = (long) thread_rank;
    printf("hello from %ld thread out of %d threads\n",_thread_rank,THREAD_COUNT);
    return NULL;
}