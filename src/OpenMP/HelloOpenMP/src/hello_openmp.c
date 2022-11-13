// OpenMP header
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void Hello(void);

int main(int argc, char* argv[])
{
    
    int nthreads;                               // specify number of thread you wants to create

    if(argv[1] == NULL){
        printf("Invalid input. should run as ./program_name <num_of_threads>\n");
        exit(0);
    }

    nthreads = strtol(argv[1], NULL, 10);

    #pragma omp parallel num_threads(nthreads)
    Hello();                                    // Parallel region with specified number of threads 

    return 0;
}

void Hello(void){

    int thread_rank = omp_get_thread_num();     // to get thread id
    int thread_count = omp_get_num_threads();   // to get num of threads

    printf("Hello from thread %d of %d\n", thread_rank, thread_count);

}

// compiling - gcc -g -Wall hello_openmp.c -o hello_openmp -fopenmp