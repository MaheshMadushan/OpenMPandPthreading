
# Pthread and OpenMP Tutorial

This tutorial contains how to work with pthreads and OpenMP in c/c++ application.

## Folder Structure
```
| - src
    |- OpenMP                      : contains programs written using OpenMPI framework
        |- ComputingPI             : computes PI using pmultiple threads
            | - src
                | - PI             : executable
                | - PI.C           : source code
        | - HelloOpenMP            : contains helloworld program to OpenMPI
            | - src
                | - hello_openmp   : executable
                | - hello_openmp.C : source code
    | - Pthread                    : contains parallel programs written using pthreads
        | - HelloPthread           : contains helloworld program to pthreads
            | - src
                | - hello_pthread.C
            | - Makefile
        | - MutualExclusion        : Mutex examples
            | - src
                | - DkrsAlgo.c     : dekkers algorithm (WIP)
            | - Makefile
```

# Compiling OpenMPI programs
```
gcc -g -Wall <program_name>.c -o <program_name> -fopenmp
```
