#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct{int N,ini,fim;double *A,*B,*C;} Args;
static double elapsed(struct timespec a,struct timespec b){return (b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;}
static void *worker(void *ptr){Args *d=ptr;int N=d->N;for(int i=d->ini;i<d->fim;i++)for(int j=0;j<N;j++){double s=0.0;for(int k=0;k<N;k++)s+=d->A[(size_t)i*N+k]*d->B[(size_t)k*N+j];d->C[(size_t)i*N+j]=s;}return NULL;}
int main(int argc,char **argv){
    int N=(argc>1)?atoi(argv[1]):1536,T=(argc>2)?atoi(argv[2]):4;if(T<1)return 1;
    size_t total=(size_t)N*N;double *A=malloc(total*sizeof(double)),*B=malloc(total*sizeof(double)),*C=calloc(total,sizeof(double));if(!A||!B||!C)return 1;
    for(int i=0;i<N;i++)for(int j=0;j<N;j++){A[(size_t)i*N+j]=(double)(i+j);B[(size_t)i*N+j]=(double)(i*j);}
    pthread_t *th=malloc((size_t)T*sizeof(*th));Args *a=malloc((size_t)T*sizeof(*a));int base=N/T,rem=N%T,cur=0;struct timespec ini,fim;clock_gettime(CLOCK_MONOTONIC,&ini);
    for(int t=0;t<T;t++){int q=base+(t<rem);a[t]=(Args){N,cur,cur+q,A,B,C};pthread_create(&th[t],NULL,worker,&a[t]);cur+=q;}for(int t=0;t<T;t++)pthread_join(th[t],NULL);clock_gettime(CLOCK_MONOTONIC,&fim);
    double checksum=0.0;for(size_t p=0;p<total;p++)checksum+=C[p];printf("[Pthreads] N=%d | T=%d | tempo=%.6f s | checksum=%.3f\n",N,T,elapsed(ini,fim),checksum);
    free(th);free(a);free(A);free(B);free(C);return 0;
}
