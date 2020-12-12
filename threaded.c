#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "threaded.h"
#include "simd.h"
#include "naive.h"
#include "arithmetic.h"

/**
 * thread and SIMDed version of `naive_norm`, accepts an array of any size.
 * mode:
 * - SIMD_MODE (0): will spawn `simd_norm` jobs
 * - SEQ_MODE (1): will spawn `naive_norm` jobs
 */
float pthread_norm(float arr[], int n, int n_threads, int mode)
{
    // Make sure n is divisible by both the number of threads and 8, which is the number of parallel execution we do with SIMD
    int remainder = n % ppcm(n_threads, 8);
    n = n - remainder;

    pthread_t thread_ids[n_threads];
    naive_norm_args thread_arguments[n_threads];
    void *(*wrapper_function)(void *);

    if (mode == SIMD_MODE)
    {
        wrapper_function = &simd_norm_pthread_wrapper;
    }
    else
    {
        wrapper_function = &naive_norm_pthread_wrapper;
    }

    int load_per_thread = n / n_threads;
    for (int i = 0; i < n_threads - 1; i++) // We use the main thread to make a part of the work to avoid spawning a thread for nothing
    {
        thread_arguments[i].arr = arr + load_per_thread * i;
        thread_arguments[i].size = load_per_thread;
        int code = pthread_create(&thread_ids[i], NULL, wrapper_function, &thread_arguments[i]);
        if (code != 0)
        {
            printf("Error while creating a thread, aborting...\n");
            abort();
        }
    }

    float res = 0.0;
    naive_norm_args this_thread_arguments;
    if (mode == SIMD_MODE)
    {
        res += simd_norm(arr + load_per_thread * (n_threads - 1), load_per_thread);
    }
    else
    {
        res += naive_norm(arr + load_per_thread * (n_threads - 1), load_per_thread);
    }

    // The last elements of the array are dealt with `naive_norm` since if will be an array of size 0 to 7
    // and thus cannot be dealt with using SIMD (designed for arrays of size multiple of 8 only)
    res += naive_norm(arr + n, remainder);

    for (int i = 0; i < n_threads - 1; i++)
    {
        float *ret_value;
        int code = pthread_join(thread_ids[i], (void *)&ret_value);
        if (code != 0)
        {
            // This is exceptional behaviour so we allow for crashing.
            // It could be recovered but this is not the point of the assignment.
            printf("Error while joining a thread, aborting...\n");
            abort();
        }

        res += *ret_value;
        free(ret_value); // `ret_value` must be freed manually since we use `malloc` in `naive_norm_pthread_wrapper` and `simd_norm_pthread_wrapper`
    }

    return res;
}

/**
 * Simple wrapper for `naive_norm` around a pthread
 */
void *naive_norm_pthread_wrapper(void *args)
{
    naive_norm_args *cast_args = (naive_norm_args *)args;
    float *res = malloc(sizeof(float));
    *res = naive_norm(cast_args->arr, cast_args->size);
    pthread_exit((void *)res);
}

/**
 * Simple wrapper for `simd_norm` around a pthread
 */
void *simd_norm_pthread_wrapper(void *args)
{
    naive_norm_args *cast_args = (naive_norm_args *)args;
    float *res = malloc(sizeof(float));
    *res = simd_norm(cast_args->arr, cast_args->size);
    pthread_exit((void *)res);
}
