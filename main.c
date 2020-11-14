#include <stdio.h>
#include <math.h>
#include "timer.h"
#include "naive.h"
#include "threaded.h"
#include "simd.h"

#define N 1600000
#define gamma 0.5772156649

int main()
{

	float array[N] __attribute__((aligned(32)));
	for (int i = 0; i < N; i++)
	{
		float tmp = 1 / (float)(N - i);
		array[i] = tmp * tmp;
	}

	clock_t begin;
	clock_t end;

	printf("Running naive version\n");
	start_timer;
	printf("expected: %f, got: %f\n", log(N) + gamma, naive_norm(array, N));
	end_timer;
	double t1 = delta;

	printf("\n");

	printf("Running SIMD version\n");
	start_timer;
	printf("expected: %f, got: %f\n", log(N) + gamma, simd_norm(array, N));
	end_timer;
	double t2 = delta;
	printf("Speedup : %f\n", t1 / t2);

	printf("\n");

	printf("Running pthread naive version\n");
	start_timer;
	printf("expected: %f, got: %f\n", log(N) + gamma, pthread_norm(array, N));
	end_timer;
	double t3 = delta;
	printf("Speedup : %f", t1 / t3);

	return 0;
}
