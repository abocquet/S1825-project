#ifndef DEF_SIMD
#define DEF_SIMD

#include <immintrin.h>

float simd_norm(float arr[], int n);
__m256 get_abs_mask();
__m256 _mm256_abs_ps(__m256 v, __m256 mask);

#endif