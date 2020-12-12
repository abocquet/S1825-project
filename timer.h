#ifndef timer_utils

#define timer_utils
#include <sys/time.h>

static struct timeval stop, start;
static long int delta;
static int repetitions;

/** 
 * Simple macros to measure the time of execution of a block of code
 * To use it, simply write:
 * ```
 *  timeit("label", 17) {yourcode} end_timeit
 * ```
 * It it will display the mean time to execute {yourcode} 17 times
 */

#define timeit(label, r)                     \
    printf("%-15s |", label);                \
    repetitions = r;                         \
    gettimeofday(&start, NULL);              \
    for (int _i = 0; _i < repetitions; _i++) \
    {

#define end_timeit                                                                 \
    }                                                                              \
    gettimeofday(&stop, NULL);                                                     \
    delta = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec; \
    printf("%*lf ms | %*d ", 10, ((double)delta) / 1000 / repetitions, 9, repetitions);

#endif