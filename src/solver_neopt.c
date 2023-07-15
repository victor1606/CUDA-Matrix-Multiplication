/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	printf("NEOPT SOLVER\n");

	double *C = calloc(N * N, sizeof(double));
	if (!C)
	{
		printf("C matrix malloc failed!");
		exit(-1);
	}

	// A X B
	for (int row = 0; row < N; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			double current_sum = 0;
			int current_row = row * N;

			for (int ct = 0; ct < N; ++ct)
			{
				// Check if column index is greater than the row index
				if (ct >= row)
				{
					int first = current_row + ct;
					int second = ct * N + column;
					current_sum += A[first] * B[second];
				}
			}

			C[current_row + column] = current_sum;
		}
	}

	// A X B X A^t
	for (int row = 0; row < N; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			double current_sum = 0;
			int current_row = row * N;

			for (int ct = 0; ct < N; ++ct)
			{
				if (ct >= column)
				{
					int first = current_row + ct;

					// Extract transposed elements: A^t
					int second = column * N + ct;
					current_sum += C[first] * A[second];
				}
			}

			C[current_row + column] = current_sum;
		}
	}

	// A X B X A^t + B^t + B^t
	for (int row = 0; row < N; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			double current_sum = 0;
			int current_row = row * N;

			for (int ct = 0; ct < N; ++ct)
			{
				// Extract transposed elements: B^t
				int first = ct * N + row;
				int second = column * N + ct;
				current_sum += B[first] * B[second];
			}

			// Add B^t X B^t to the previous result
			C[current_row + column] += current_sum;
		}
	}

	return C;
}

