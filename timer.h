#ifndef timer_utils

#define timer_utils
#include <sys/time.h>

static struct timeval stop, start;
static long int delta;
static int repetitions;

#define start_timer gettimeofday(&start, NULL);

#define end_timer                                                                  \
    gettimeofday(&stop, NULL);                                                     \
    delta = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec; \
    printf("Fragment ran in %lf ms\n", ((double)delta) / 1000);

#define timeit(label, r)                     \
    printf("%-15s |", label);                \
    repetitions = r;                         \
    start_timer gettimeofday(&start, NULL);  \
    for (int _i = 0; _i < repetitions; _i++) \
    {

#define end_timeit                                                                 \
    }                                                                              \
    gettimeofday(&stop, NULL);                                                     \
    delta = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec; \
    printf("%*lf ms | %*d ", 10, ((double)delta) / 1000 / repetitions, 9, repetitions);

#endif