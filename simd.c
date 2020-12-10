#include <stdio.h>
#include <immintrin.h>
#include "simd.h"

float sum8(__m256 x);

float simd_norm(float arr[], int n)
{
    int v = n / 8;
    __m256 res = _mm256_setzero_ps();
    __m256 mask = get_abs_mask();
    __m256 __attribute__((aligned(32))) vectorized;

    for (int i = 0; i < v; i++)
    {
        vectorized = _mm256_load_ps(&arr[8 * i]);
        vectorized = _mm256_abs_ps(vectorized, mask);
        vectorized = _mm256_sqrt_ps(vectorized);
        res += vectorized;
    }

    return sum8(res);
}

float sum8(__m256 x)
{
    // Taken from https://stackoverflow.com/questions/13219146/how-to-sum-m256-horizontally

    // hiQuad = ( x7, x6, x5, x4 )
    const __m128 hiQuad = _mm256_extractf128_ps(x, 1);
    // loQuad = ( x3, x2, x1, x0 )
    const __m128 loQuad = _mm256_castps256_ps128(x);
    // sumQuad = ( x3 + x7, x2 + x6, x1 + x5, x0 + x4 )
    const __m128 sumQuad = _mm_add_ps(loQuad, hiQuad);
    // loDual = ( -, -, x1 + x5, x0 + x4 )
    const __m128 loDual = sumQuad;
    // hiDual = ( -, -, x3 + x7, x2 + x6 )
    const __m128 hiDual = _mm_movehl_ps(sumQuad, sumQuad);
    // sumDual = ( -, -, x1 + x3 + x5 + x7, x0 + x2 + x4 + x6 )
    const __m128 sumDual = _mm_add_ps(loDual, hiDual);
    // lo = ( -, -, -, x0 + x2 + x4 + x6 )
    const __m128 lo = sumDual;
    // hi = ( -, -, -, x1 + x3 + x5 + x7 )
    const __m128 hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
    // sum = ( -, -, -, x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 )
    const __m128 sum = _mm_add_ss(lo, hi);
    return _mm_cvtss_f32(sum);
}

__m256 get_abs_mask()
{
    __m256i minus1 = _mm256_set1_epi32(-1);
    return _mm256_castsi256_ps(_mm256_srli_epi32(minus1, 1));
}

__m256 _mm256_abs_ps(__m256 v, __m256 mask)
{
    /**
     * Return the absolute value of `v`. `mask` should come from `get_abs_mask()`.
     */

    return _mm256_and_ps(v, mask);
}
