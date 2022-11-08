#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>













int thread_count;




void* Hello(void* thread_rank);


int main(int arg_count, char* argv[]){
    long thread;
    pthread_t* thread_handles;

    if(argv[1] == NULL){
        printf("Invalid input. should run as ./program_name <num_of_threads>\n");
        exit(0);
    }

    thread_count = strtol(argv[1], NULL, 10);
    
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for(thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, (void*) Hello, (void *) thread);
    }
    
    for(thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);
    return 0;
}

void* Hello(void* thread_rank){
    long _thread_rank = (long) thread_rank;
    printf("hello from %ld thread out of %d threads\n",_thread_rank,thread_count);
    return NULL;
}