#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define  Max(a,b) ((a)>(b)?(a):(b))

void init(size_t n, float *** A)
{ 
	for (size_t i = 0; i < n; i++)
	    for (size_t j = 0; j < n; j++)
	        for (size_t k = 0; k < n; k++)
            {
	            if (i == 0 || i == n - 1 || j == 0 || j == n - 1 || k == 0 || k == n - 1)
	                A[i][j][k]= 0.;
	            else A[i][j][k]= (4. + i + j + k) ;
            }
} 

float relax(size_t n, float *** A)
{
    float eps = 0.;

	for (size_t k = 1; k < n - 1; k++)
	    for (size_t j = 1; j < n - 1; j++)
	        for (size_t i = 1; i < n - 1; i++)
	        {
		        A[i][j][k] = (A[i - 1][j][k] + A[i + 1][j][k]) / 2.;
	        }

	for (size_t k = 1; k < n - 1; k++)
	    for (size_t j = 1; j < n - 1; j++)
	        for (size_t i = 1; i < n - 1; i++)
	        {
		        A[i][j][k] = (A[i][j - 1][k] + A[i][j + 1][k]) / 2.;
	        }

	for (size_t k = 1; k < n - 1; k++)
	    for (size_t j = 1; j < n - 1; j++)
	        for (size_t i = 1; i < n - 1; i++)
	        {
		        float e;
		        e = A[i][j][k];
		        A[i][j][k] = (A[i][j][k - 1] + A[i][j][k + 1]) / 2.;
		        eps = Max(eps, fabs(e - A[i][j][k]));
	        }

}

float relax_parallel(size_t n, float *** A)
{
    float eps = 0.;
    #pragma omp parallel reduction(max: eps) 
    {
        #pragma omp for collapse(2)
        for (size_t k = 1; k < n - 1; k++)
            for (size_t j = 1; j < n - 1; j++)
                for (size_t i = 1; i < n - 1; i++)
                {
                    A[i][j][k] = (A[i - 1][j][k] + A[i + 1][j][k]) / 2.;
                }

        #pragma omp for collapse(2)
        for (size_t k = 1; k < n - 1; k++)
            for (size_t i = 1; i < n - 1; i++)
                for (size_t j = 1; j < n - 1; j++)
                {
                    A[i][j][k] = (A[i][j - 1][k] + A[i][j + 1][k]) / 2.;
                }

        #pragma omp for collapse(2)  
        for (size_t i = 1; i < n - 1; i++)
            for (size_t j = 1; j < n - 1; j++)
                for (size_t k = 1; k < n - 1; k++)
                {
                    float e;
                    e = A[i][j][k];
                    A[i][j][k] = (A[i][j][k - 1] + A[i][j][k + 1]) / 2.;
                    eps = Max(eps, fabs(e - A[i][j][k]));
                }
    }
    return eps;
}

void verify(size_t n, float *** A)
{
	float s = 0.;

	for (size_t i = 1; i < n - 1; i++)
	    for (size_t j = 1; j < n - 1; j++)
	        for (size_t k = 1; k < n - 1; k++)
	        {
		        s += A[i][j][k] * (i + 1) * (j + 1) * (k + 1) / (n * n * n);
	        }
	printf("S = %f\n", s);

}

int main (int argc, char * argv[])
{
    const float mineps = 0.1e-7;
    const size_t itmax = 100;

    size_t n = strtol(argv[1], NULL, 10);
    int num_threads = strtol(argv[2], NULL, 10);
    omp_set_num_threads(num_threads);

    float *** A = calloc(n, sizeof(*A));
    for (size_t i = 0; i < n; i++) {
        A[i] = calloc(n, sizeof(**A));
        for (size_t j = 0; j < n; j++) {
            A[i][j] = calloc(n, sizeof(***A));
        }
    }
    
    /*
    init(n, A);

    for(size_t it = 0; it < itmax; it++)
	{
		float eps = 0.;
		eps = relax(n, A);
		if (eps < mineps) break;
	}

    verify(n, A);
    */
    init(n, A);

    double start = omp_get_wtime();
	for(size_t it = 0; it < itmax; it++)
	{
		float eps = 0.;
		eps = relax_parallel(n, A);
		if (eps < mineps) break;
	}
    double end = omp_get_wtime();
    printf("%lf\n", end - start);

    //verify(n, A);

    for (size_t i = 0; i < n; i++) {;
        for (size_t j = 0; j < n; j++) {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);

	return 0;
}
