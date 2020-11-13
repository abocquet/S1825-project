#ifndef timer_utils

#define timer_utils
#include <time.h>

static clock_t begin;
static clock_t end;

#define start_timer begin = clock();
#define end_timer  \
    end = clock(); \
    printf("Fragment ran in %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

#endif