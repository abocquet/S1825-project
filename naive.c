#include "naive.h"
#include <math.h>


float naive_norm(float arr[], int n)
{
    float res = 0.0;
    for (int i = 0; i < n; i++)
    {
        res += sqrtf(arr[i]);
    }
    return res;
}
