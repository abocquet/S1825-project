#ifndef timer_utils

#define timer_utils
#include <sys/time.h>

static struct timeval stop, start;
static long int delta;

#define start_timer gettimeofday(&start, NULL);

#define end_timer                                                                  \
    gettimeofday(&stop, NULL);                                                     \
    delta = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec; \
    printf("Fragment ran in %lf ms\n", ((double)delta) / 1000);

#endif