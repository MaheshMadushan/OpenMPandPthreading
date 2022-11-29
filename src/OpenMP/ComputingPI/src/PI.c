#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void sum(long long * numOfSteps, double * sums);

int main(int argc, char* argv[])
{
    struct timeval te; 
    gettimeofday(&te, NULL); 
    long long start_time_in_ms = te.tv_sec*1000LL + te.tv_usec/1000; 

    long long numOfSteps = 0;                                           // specify number of steps in monte carlo PI alogrithm
    int numOfThreads = 0;                                               // specify number of thread you wants to create
    
    if(argv[1] == NULL){
        printf("Invalid input. should run as ./program_name <num_of_threads> <num_of_steps> \n");
        exit(0);
    }

    numOfThreads = strtol(argv[1], NULL, 10);
    numOfSteps = strtol(argv[2], NULL, 10);

    long long * p_numOfSteps = &numOfSteps;
    double sums[numOfThreads + 1];     
    double PI = 0;       
    sums[numOfThreads] = 1.0;  

    printf("OpenMP will use %d cores to map %lld steps of counting PI to %d threads with %d steps of work load per thread.\n",omp_get_max_threads(),numOfSteps,numOfThreads,(int) numOfSteps/numOfThreads);

    #pragma omp parallel num_threads(numOfThreads) shared(sums)         // Map
    sum(p_numOfSteps,sums);                                             // Parallel region with specified number of threads 

    gettimeofday(&te, NULL);                                        
    long long end_time_in_ms = te.tv_sec*1000LL + te.tv_usec/1000;  

    double reduced_sum;

    for (size_t i = 0; i < numOfThreads; i++)                           // Reduce
    {
        reduced_sum += sums[i];
    }
    PI = 4.0 * (reduced_sum);
    printf("PI = %lf\n",4.0 * (reduced_sum));

    printf("execution time %lld ms\n",end_time_in_ms - start_time_in_ms);
    return 0;
}

void sum(long long * numOfSteps, double * sums){

    long thread_rank = omp_get_thread_num();     // to get thread id
    long thread_count = omp_get_num_threads();   // to get num of threads

    long work_load = (*numOfSteps) / thread_count;
    
    long starting_num = thread_rank * work_load;
    long ending_num = starting_num + work_load;
    double factor = 0;

    double local_sum = 0;

    if(starting_num % 2 == 0){
        factor = 1;
    }else{
        factor = -1;
    }

    // printf("thread rank %d thread count %d work load %d starting num %d ending num %d\n", 
    //             thread_rank,     // to get thread id
    //             thread_count ,   // to get num of threads
    //             work_load,
    //             starting_num ,
    //             ending_num 
    //     );

    for(int i = starting_num; i < ending_num; i++, factor = -factor){
        local_sum += (factor / ((2 * i) + 1));
    }

    sums[thread_rank] = local_sum;
}

// compiling - gcc -g -Wall PI.c -o PI -fopenmp
