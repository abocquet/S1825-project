#include <stdio.h>
#include <math.h>

#include "timer.h"
#include "naive.h"
#include "threaded.h"
#include "simd.h"

#define N 800000
#define gamma 0.5772156649

int main()
{

	float array[N];
	for (int i = 0; i < N; i++)
	{
		float tmp = 1 / (float)(i + 1);
		array[i] = tmp * tmp;
	}

	clock_t begin;
	clock_t end;

	printf("Running naive version\n");
	start_timer;
	printf("expected: %f, got: %f\n", log(N) + gamma, naive_norm(array, N));
	end_timer;

	printf("\n");

	printf("Running SIMD version\n");
	start_timer;
	printf("expected: %f, got: %f\n", log(N) + gamma, simd_norm(array, N));
	end_timer;

	return 0;
}
