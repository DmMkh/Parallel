#include stdio.h
#include stdlib.h
#include pthread.h
typedef struct _thread_data_t {
    int tid;
} thread_data_t;

int shared = 0;
pthread_mutex_t lock_x;

void thr_func(void arg)
{
    thread_data_t data = (thread_data_t ) arg;
    pthread_mutex_lock(&lock_x);
    shared += 1;
    printf(thread %d int is %dn, data-tid, shared);
    pthread_mutex_unlock(&lock_x);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    int NUM_THREADS = 40;
    pthread_t thr[NUM_THREADS];
    int i, rc;
    thread_data_t thr_data[NUM_THREADS];
    for (i = 0; i  NUM_THREADS; i++)
    {
        thr_data[i].tid = i;
        if (rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))
        {
            fprintf(stderr, errorpthread_create, rc%dn, rc);
            return EXIT_FAILURE;
        }
    }
    for (i = 0; i  NUM_THREADS; i++)
        pthread_join(thr[i], NULL);
    return 0;
}
