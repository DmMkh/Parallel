#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

typedef struct _thread_data_t {
    int tid;
    double a;
    double b;
    double summ;

} thread_data_t;

double eps;

double f(double x)
{
    return cos(1/x);
}

void* thr_func(void* arg)
{
    int i;
    double x, h;
    thread_data_t *data = (thread_data_t *) arg;
    data->summ = 0;

    h = sqrt(eps*4*data->a*data->a*data->a/10/(data->b-data->a));
    x = data->a;
    while(x < data->b - h)
    {
        data->summ += (f(x) + f(x+h))*h/2;
        x += h;
    }
    data->summ += (f(x) + f(data->b))*(data->b-x)/2;
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int NUM_THREADS;
    NUM_THREADS = atoi(argv[1]);
    time_t t0 = time(0);
    clock_t begin = clock();
    double summ, h;
    double a = 0.01;
    double b = 5;
    eps = strtod(argv[2], &(argv[2]));
    pthread_t thr[NUM_THREADS];
    int i, rc;
    thread_data_t thr_data[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++)
    {
        thr_data[i].tid = i;
        thr_data[i].a = a + (b-a)*i/NUM_THREADS;
        thr_data[i].b = a + (b-a)*(i+1)/NUM_THREADS;
        if (rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))
        {
            fprintf(stderr, "error:pthread_create, rc:%d\n", rc);
            return EXIT_FAILURE;
        }
    }
    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(thr[i], NULL);
    for (i = 0; i < NUM_THREADS; i++)
        summ += thr_data[i].summ;
    time_t t1 = time(0);
    clock_t end = clock();
    printf("%le %f %f\n", summ, (double)(end - begin) / CLOCKS_PER_SEC, 5.12/((double)(end - begin)*NUM_THREADS / CLOCKS_PER_SEC));

    //FILE *file;
    //file = fopen("D:/data.txt", "wb");
    //fprintf(file, "%f %f %f\n", NUM_THREADS, (double)(end - begin) / CLOCKS_PER_SEC, 5.12/((double)(end - begin)*NUM_THREADS / CLOCKS_PER_SEC));
    return 0;
}
