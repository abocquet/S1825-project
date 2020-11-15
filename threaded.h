#ifndef DEF_THREADED
#define DEF_THREADED

#define SEQ_MODE 0
#define SIMD_MODE 1

typedef struct naive_norm_args naive_norm_args;
struct naive_norm_args
{
    float *arr;
    int size;
};

void *naive_norm_pthread_wrapper(void *args);
void *simd_norm_pthread_wrapper(void *args);
float pthread_norm(float arr[], int n, int n_threads, int mode);

#endif