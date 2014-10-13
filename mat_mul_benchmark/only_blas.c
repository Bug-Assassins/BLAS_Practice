#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<cblas.h>
inline int inp()
{
    register int noRead=0;
    register char p=getchar_unlocked();
    for(;p<48 || p>57;p=getchar_unlocked());
    while(p>47 && p<58){ noRead = (noRead << 3) + (noRead << 1) + (p - '0');p=getchar_unlocked();}
    return noRead;
}

int main()
{
	long long int n = inp(), mo = inp(), i, j;

	double mul_start, mul_end, *A, *B, *C;

	A = (double *) malloc(n * n * sizeof(double));
	B = (double *) malloc(n * n * sizeof(double));
	C = (double *) malloc(n * n * sizeof(double));

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            A[(i*n) + j] = inp();
            B[(i*n) + j] = inp();
            //A[(i*n) + j] = 0.0;
            //B[(i*n) + j] = 0.0;
        }
    }

    mul_start = omp_get_wtime();
    //Main Operation Here
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, A, n, B, n, 0.0, C, n);
    mul_end = omp_get_wtime();

    FILE* fp = fopen("./outputs/mat_mul_only_blas.out","w");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(j > 0) fprintf(fp," ");
            fprintf(fp,"%lld",((int)C[(i*n) + j]) %mo );
        }
        fprintf(fp,"\n");
    }

    printf("Time Taken for Only BLAS     = %lf\n", mul_end - mul_start);

	return 0;
}
