#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#include "naive.h"
#include "threaded.h"
#include "simd.h"

#define EPS 0.0000000001

void fill_array(float *array, int size);

int main(int argc, char *argv[])
{
	// Parse input arguments
	if (argc < 3)
	{
		printf("You must provide the size of the array and the number of threads to use");
		exit(-1);
	}

	int array_size;
	int thread_number;

	if (sscanf(argv[1], "%i", &array_size) != 1)
	{
		fprintf(stderr, "array_size must be an integer");
		exit(-1);
	}

	if (sscanf(argv[2], "%i", &thread_number) != 1)
	{
		fprintf(stderr, "thread_number must be an integer");
		exit(-1);
	}

	printf("Array size: %d\nNumber of threads: %d\n\n", array_size, thread_number);

	float array[array_size];
	fill_array(array, array_size);

	float result = 0.0;

	clock_t begin;
	clock_t end;

	double r1, r2, r3, r4;

	timeit("Running naive version", 100, r1) r1 = naive_norm(array, array_size);
	end_timeit;
	printf("Result: %f\n", r1);

	double t1 = delta;
	printf("\n");

	timeit("Running SIMD version", 100, r2) r2 = simd_norm(array, array_size);
	end_timeit;
	double t2 = delta;
	printf("Result: %f\n", r2);
	printf("Speedup : %f\n", t1 / t2);

	printf("\n");

	timeit("Running pthread naive version", 100, r3) r3 = pthread_norm(array, array_size, 4, SEQ_MODE);
	end_timeit;
	double t3 = delta;
	printf("Result: %f\n", r3);
	printf("Speedup : %f\n", t1 / t3);

	printf("\n");

	timeit("Running pthread simd version", 100, r4) r4 = pthread_norm(array, array_size, 4, SIMD_MODE);
	end_timeit;
	double t4 = delta;
	printf("Result: %f\n", r4);
	printf("Speedup : %f\n", t1 / t4);

	if (fabs(r1 - r2) > EPS || fabs(r1 - r3) > EPS || fabs(r1 - r4) > EPS)
	{
		printf("\nAll results are not the same\n");
	}
	else
	{
		printf("\nAll results are equal (up to %f)\n", EPS);
	}

	return 0;
}

void fill_array(float *array, int size)
{
	/**
     * Fill an array with random numbers.
    */

	for (int i = 0; i < size; i++)
	{
		array[i] = (float)rand() / RAND_MAX - 0.5;
	}
}