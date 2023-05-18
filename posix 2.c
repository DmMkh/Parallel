#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4
typedef struct _thread_data_t {
    int tid;
    int N;
    double summ;

} thread_data_t;

void* thr_func(void* arg)
{
    int i;
    thread_data_t *data = (thread_data_t *) arg;
    data->summ = 0;
    for (i = (data->tid)*data->N / (NUM_THREADS) + 1; i <= (data->tid + 1)* data->N / (NUM_THREADS); i++)
    {
                                //printf("i == %d", i);
        data->summ +=(double) 1/ (double) i;
    }
    printf("%f\n", data->summ);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    //int NUM_THREADS = 4;
    double summ;
    pthread_t thr[NUM_THREADS];
    int i, rc;
    thread_data_t thr_data[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++)
    {
        thr_data[i].tid = i;
        thr_data[i].N = atoi(argv[1]);
        if (rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))
        {
            fprintf(stderr, "error:pthread_create, rc:%d\n", rc);
            return EXIT_FAILURE;
        }
    }
    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(thr[i], NULL);
    for (i = 0; i < NUM_THREADS; i++)
        summ+= thr_data[i].summ;
    printf("summ is %f\n", summ);
    return 0;
}
