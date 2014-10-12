#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#include<queue>
#include<utility>
#include<cblas.h>
#include<omp.h>
#define MAX_SIZE 10000
#define MAX_ITER 10

int main()
{
    blasint n = MAX_SIZE;
    blasint mat = n * n;
    int i,j,c,k;
    double t1,t2,alpha,beta;
    alpha = 1.0;
    beta = 1.0;

    std::vector<double> A(mat);
    std::vector<double> Ab(mat);
    std::vector<double> x(n);
    std::vector<double> y(n);
    std::vector<double> xb(n);
    std::vector<double> yb(n);
    std::vector<double> res(n);

    std::fill(A.begin(),A.end(),1.0);
    std::fill(Ab.begin(),Ab.end(),1.0);
    std::fill(x.begin(),x.end(),1.0);
    std::fill(y.begin(),y.end(),2.0);
    std::fill(xb.begin(),xb.end(),1.0);
    std::fill(yb.begin(),yb.end(),2.0);


    printf("BLAS Started...");
    t1 = omp_get_wtime();
    for(i = 0; i < MAX_ITER; i++)
    cblas_dsymv (CblasRowMajor, CblasUpper, n, alpha , &A[0], n, &x[0], 1, beta, &y[0], 1);
    t1 = omp_get_wtime() - t1;
    printf("Done\n");fflush(stdout);


    printf("Brute started..");
    t2 = omp_get_wtime();
    for(k = 0; k < MAX_ITER; k++)
    {
        #pragma omp parallel for private(c,j)
        for(i = 0; i < n; i++)
        {
            c = 0;
            for(j = 0; j < n; j++)
                c += Ab[i * n + j] * xb[j];
            res[i] = c;
        }
        #pragma omp parallel for
        for(i = 0; i < n ; i++)
        {
            yb[i] = alpha * res[i] + beta * yb[i];
        }
    }
    t2 = omp_get_wtime() - t2;
    printf("Done\n");fflush(stdout);

    for(i = 0; i < n; i++)
    {
        //printf("%lf %lf\n",y[i],yb[i]);
        if(y[i] != yb[i])
        {
            printf("Wrong Values !!\n terminating !!\n");fflush(stdout);
            exit(0);
        }

    }

    printf("Time for Blas = %lf\n",t1);fflush(stdout);
    printf("Time for Brute = %lf\n",t2);fflush(stdout);
    return 0;
}
