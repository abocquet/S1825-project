#ifndef DEF_THREADED
#define DEF_THREADED

typedef struct naive_norm_args naive_norm_args;struct naive_norm_args
{
    float *arr;
    int size;
};

void *naive_norm_pthread_wrapper(void *args);
float pthread_norm(float arr[], int n);

#endif