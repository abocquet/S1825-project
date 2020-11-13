#include <stdio.h>
#include <math.h>
#include "timer.h"

#define N 1000000
#define gamma 0.5772156649

float naive_norm(float arr[], int n);

int main()
{

	float array[N];
	for (int i = 0; i < N; i++)
	{
		double tmp = 1 / (float)(i + 1);
		array[i] = tmp * tmp;
	}

	start_timer;
	printf("expected: %f, got: %f\n", log(N) + gamma, naive_norm(array, N));
	end_timer;

	return 0;
}

float naive_norm(float arr[], int n)
{
	float res = 0.0;
	for (int i = 0; i < n; i++)
	{
		res += sqrt(arr[i]);
	}
	return res;
}
