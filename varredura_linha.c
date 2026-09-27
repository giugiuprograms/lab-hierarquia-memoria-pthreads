#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double elapsed(struct timespec a, struct timespec b) {
    return (b.tv_sec-a.tv_sec) + (b.tv_nsec-a.tv_nsec)/1e9;
}

int main(int argc, char **argv) {
    int N = (argc > 1) ? atoi(argv[1]) : 1024;
    size_t total = (size_t)N * N;
    double *A = malloc(total * sizeof(double));
    if (!A) return 1;
    for (int i=0;i<N;i++) for (int j=0;j<N;j++) A[(size_t)i*N+j]=(double)(i+j);
    long long pares=0; struct timespec ini,fim;
    clock_gettime(CLOCK_MONOTONIC,&ini);
    for (int i=0;i<N;i++) for (int j=0;j<N;j++) if (((int)A[(size_t)i*N+j])%2==0) pares++;
    clock_gettime(CLOCK_MONOTONIC,&fim);
    printf("[Linha] N=%d | pares=%lld | tempo=%.6f s\n",N,pares,elapsed(ini,fim));
    free(A); return 0;
}
