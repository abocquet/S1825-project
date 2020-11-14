#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "threaded.h"
#include "naive.h"

#define NB_THREADS 2



float pthread_norm(float arr[], int n)
{
    if (n % NB_THREADS != 0)
    {
        printf("The size of the array isn't a multiple of the number of threads, aborting...\n");
        abort();
    }

    pthread_t thread_ids[NB_THREADS];
    naive_norm_args *thread_arguments[NB_THREADS];

    for (int i = 0; i < NB_THREADS; i++)
    {
        thread_arguments[i] = malloc(sizeof(naive_norm_args));
        thread_arguments[i]->arr = arr + n / NB_THREADS * i;
        thread_arguments[i]->size = n / NB_THREADS;
        int code = pthread_create(&thread_ids[i], NULL, &naive_norm_pthread_wrapper, thread_arguments[i]);
        if (code != 0)
        {
            printf("Error while creating a thread, aborting...\n");
            abort();
        }
    }

    float res = 0.0;
    for (int i = 0; i < NB_THREADS; i++)
    {
        float *ret_value;
        int code = pthread_join(thread_ids[i], (void *)&ret_value);
        if (code != 0)
        {
            printf("Error while joining a thread, aborting...\n");
            abort();
        }

        res += *ret_value;

        free(thread_arguments[i]);
        free(ret_value);
    }

    return res;
}

void *naive_norm_pthread_wrapper(void *args)
{

    naive_norm_args *cast_args = (naive_norm_args *)args;
    float *res = malloc(sizeof(float));
    *res = naive_norm(cast_args->arr, cast_args->size);
    pthread_exit((void *)res);
}
