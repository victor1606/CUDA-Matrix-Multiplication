/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
    printf("OPT SOLVER\n");

    double *C = calloc(N * N, sizeof(double));
    if (!C)
    {
        printf("C matrix malloc failed!");
        exit(-1);
    }

    // "register" keyword for current_sum (constant in loop) and i, j, k iterators (noticeable speedup)
    register double current_sum = 0;
    register int i, j, k;

    // A X B
    // Used pointers for speedup
    for (i = 0; i < N; ++i)
    {
        register int current_i = i * N;
        register double *orig_pa = &A[current_i + i];

        for (j = 0; j < N; ++j)
        {
            double *pa = orig_pa;
            double *pb = &B[j + i * N];

            // Constant in loop
            current_sum = 0;

            for (k = i; k < N; ++k)
            {
                current_sum += *pa * *pb;
                pa++;
                pb += N;
            }

            C[current_i + j] = current_sum;
        }
    }

    // A X B X A^t
    for (i = 0; i < N; ++i)
	{
        // Constant in loop
        register int current_i = i * N;

		for (j = 0; j < N; ++j)
		{
            // Constant in loop
			current_sum = 0;

			for (k = j; k < N; ++k)
			{
                current_sum += C[current_i + k] * A[j * N + k];
			}

			C[current_i + j] = current_sum;
		}
	}

    // A X B X A^t + B^t + B^t
    for (i = 0; i < N; ++i)
    {
        // Constant in loop
        register int current_i = i * N;
    	for (j = 0; j < N; ++j)
    	{
            // Constant in loop
    		current_sum = 0;

    		for (k = 0; k < N; ++k)
    		{
    			current_sum += B[k * N + i] * B[j * N + k];
    		}

    		// Add B^t X B^t to the previous result
    		C[current_i + j] += current_sum;
    	}
    }

    return C;
}

