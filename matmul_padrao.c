#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double elapsed(struct timespec a, struct timespec b) {
    return (b.tv_sec-a.tv_sec) + (b.tv_nsec-a.tv_nsec)/1e9;
}

int main(int argc, char **argv) {
    int N=(argc>1)?atoi(argv[1]):512;
    size_t total=(size_t)N*N;
    double *A=malloc(total*sizeof(double)), *B=malloc(total*sizeof(double)), *C=calloc(total,sizeof(double));
    if(!A||!B||!C){free(A);free(B);free(C);return 1;}
    for(int i=0;i<N;i++) for(int j=0;j<N;j++){A[(size_t)i*N+j]=(double)(i+j);B[(size_t)i*N+j]=(double)(i*j);}
    struct timespec ini,fim; clock_gettime(CLOCK_MONOTONIC,&ini);
    for(int i=0;i<N;i++) for(int j=0;j<N;j++){
        double s=0.0; for(int k=0;k<N;k++) s+=A[(size_t)i*N+k]*B[(size_t)k*N+j];
        C[(size_t)i*N+j]=s;
    }
    clock_gettime(CLOCK_MONOTONIC,&fim);
    double checksum=0.0; for(size_t p=0;p<total;p++) checksum+=C[p];
    printf("[Matmul Padrao] N=%d | tempo=%.6f s | checksum=%.3f\n",N,elapsed(ini,fim),checksum);
    free(A);free(B);free(C);return 0;
}
