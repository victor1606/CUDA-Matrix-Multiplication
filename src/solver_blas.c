/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"
#include "cblas.h"

/*
 * Add your BLAS implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	printf("BLAS SOLVER\n");

	double *AB = calloc(N * N, sizeof(double));
	if (!AB)
	{
		printf("AB matrix malloc failed!");
		exit(-1);
	}

	double *ABAt = calloc(N * N, sizeof(double));
	if (!ABAt)
	{
		printf("ABAt matrix malloc failed!");
		exit(-1);
	}

	double *Bt2 = calloc(N * N, sizeof(double));
	if (!Bt2)
	{
		printf("Bt2 matrix malloc failed!");
		exit(-1);
	}

	// Copy B matrix into AB
	for (int i = 0; i < N * N; ++i) {
		AB[i] = B[i];
	}

	// A X B
	// CblasUpper ==> upper triangular
	// Stored result in AB matrix
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, AB, N);
	
	// A X B X At
	// CblasTrans ==> A is transposed
	// Stored result in ABAt matrix
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1, AB, N, A, N, 0, ABAt, N);

	// Bt X Bt
	// Stored result in Bt2 matrix
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasTrans, N, N, N, 1, B, N, B, N, 0, Bt2, N);

	// A X B X At + Bt X Bt
	// Stored result in ABAt matrix
	cblas_daxpy(N * N, 1, Bt2, 1, ABAt, 1);

	free(AB);
	free(Bt2);

	return ABAt;
}

