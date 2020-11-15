#include <stdio.h>
#include <math.h>
#include "timer.h"
#include "naive.h"
#include "threaded.h"
#include "simd.h"

#define N 1000000
#define gamma 0.5772156649

int main()
{

	float array[N];
	for (int i = 0; i < N; i++)
	{
		float tmp = 1 / (float)(N - i);
		array[i] = tmp * tmp;
	}

	clock_t begin;
	clock_t end;

	timeit("Running naive version", 100) naive_norm(array, N);
	end_timeit;

	double t1 = delta;
	printf("\n");

	timeit("Running SIMD version", 100) simd_norm(array, N);
	end_timeit;
	double t2 = delta;
	printf("Speedup : %f\n", t1 / t2);

	printf("\n");

	timeit("Running pthread naive version", 100) pthread_norm(array, N, 4, SEQ_MODE);
	end_timeit;
	double t3 = delta;
	printf("Speedup : %f\n", t1 / t3);

	printf("\n");

	timeit("Running pthread simd version", 100) pthread_norm(array, N, 4, SIMD_MODE);
	end_timeit;
	double t4 = delta;
	printf("Speedup : %f\n", t1 / t4);

	return 0;
}
