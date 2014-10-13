#include<stdio.h>
#include<stdlib.h>
#include<flint/nmod_mat.h>
#include<flint/nmod_vec.h>
#include<omp.h>
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
	int n = inp(), mo = inp(), i, j;
	double mul_start, mul_end;
    nmod_mat_t A, B, C;
    nmod_mat_init(A, n, n, mo);
    nmod_mat_init(B, n, n, mo);
    nmod_mat_init(C, n, n, mo);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            nmod_mat_entry(A, i, j) = inp();
            nmod_mat_entry(B, i, j) = inp();
        }
    }

    mul_start = omp_get_wtime();
    //Main Operation Here
    nmod_mat_mul(C, A, B);
    mul_end = omp_get_wtime();

    FILE* fp = fopen("./outputs/mat_mul_output.out","w");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(j > 0) fprintf(fp," ");
            fprintf(fp,"%d", (int) nmod_mat_entry(C, i, j));
        }
        fprintf(fp,"\n");
    }

    printf("Time Taken for Mat Mul Flint = %lf\n", mul_end - mul_start);

	return 0;
}
