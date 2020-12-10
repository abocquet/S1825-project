#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#include "naive.h"
#include "threaded.h"
#include "simd.h"

#define SAMPLES 100

void fill_array(float *array, int size);

/**
 * On macOS, run with `gcc *.c -lm -mavx2 -lpthread -O3 -o main.out && main.out 800000 4` 
 */
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

	printf("     Version    |     Time     |  Samples  |     Result      |       Speedup\n");
	printf("------------------------------------------------------------------------------\n");

	clock_t begin;
	clock_t end;

	double r1, r2, r3, r4;

	timeit("naive", SAMPLES) r1 = naive_norm(array, array_size);
	end_timeit;
	printf("| %*f | %*f ", 15, r1, 15, 1.0);

	double t1 = delta;
	printf("\n");

	timeit("SIMD", SAMPLES) r2 = simd_norm(array, array_size);
	end_timeit;
	double t2 = delta;
	printf("| %*f | %*f ", 15, r2, 15, t1 / t2);

	printf("\n");

	timeit("pthread naive", SAMPLES) r3 = pthread_norm(array, array_size, 4, SEQ_MODE);
	end_timeit;
	double t3 = delta;
	printf("| %*f | %*f ", 15, r3, 15, t1 / t3);

	printf("\n");

	timeit("pthread simd", SAMPLES) r4 = pthread_norm(array, array_size, 4, SIMD_MODE);
	end_timeit;
	double t4 = delta;
	printf("| %*f | %*f ", 15, r4, 15, t1 / t4);

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