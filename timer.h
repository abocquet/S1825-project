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

#define timeit(label, r, mem)                \
    printf("%s\n", label);                   \
    repetitions = r;                         \
    start_timer gettimeofday(&start, NULL);  \
    for (int _i = 0; _i < repetitions; _i++) \
    {

#define end_timeit                                                                 \
    }                                                                              \
    gettimeofday(&stop, NULL);                                                     \
    delta = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec; \
    printf("Ran in %lf ms / sample on a %d sample average\n", ((double)delta) / 1000 / repetitions, repetitions);

#endif