#include<cstdio>
#include<vector>
#include<cblas.h>
#include<sys/time.h>
#include<cstdlib>
#include<ctime>
#include<omp.h>
#define MAX_ITER 20
#define MAX_SIZE 100000000
using namespace std;

int main()
{
    blasint n = MAX_SIZE;
    blasint in_x = 1;
    blasint in_y = 1;

    std::vector<double> x(n);
    std::vector<double> y(n);
    std::vector<double> xb(n);
    std::vector<double> yb(n);


    double alpha = 2;

    time_t blas_start, blas_end, brute_start, brute_end;

    std::fill(x.begin(),x.end(),1.0);
    std::fill(y.begin(),y.end(),2.0);
    std::fill(xb.begin(),xb.end(),1.0);
    std::fill(yb.begin(),yb.end(),2.0);


    printf("starting Blas Operation ...... ");fflush(stdout);
    blas_start = time(NULL);
    double bbst = omp_get_wtime();
    for(int j = 0 ;j < MAX_ITER;j++)
        cblas_daxpy( n, alpha, &x[0], in_x, &y[0], in_y);
    double bben = omp_get_wtime();
    blas_end = time(NULL);
    printf("Done \n");fflush(stdout);

    printf("Starting brute operation .......");fflush(stdout);
    brute_start = time(NULL);
    double brst = omp_get_wtime();
    for(int j = 0 ;j < MAX_ITER;j++)
        #pragma omp parallel for
        for(int i =0 ;i < n ; i++)
        {
            yb[i] = yb[i] + (xb[i]*alpha);
        }
    double bren = omp_get_wtime();
    brute_end = time(NULL);
    printf("Done\n");fflush(stdout);

    for(int i = 0; i < n; i++)
    {
        if(y[i] != yb[i])
        {
            printf("Wrong Values !!\n terminating !!\n");fflush(stdout);
            exit(0);
        }
    }

    printf("Time for Blas = %lf %lf\n",difftime(blas_end, blas_start), bben - bbst);fflush(stdout);
    printf("Time for Brute = %lf %lf\n",difftime(brute_end, brute_start), bren - brst);fflush(stdout);
    //printf("Time for Blas = %lf\n", (blas_end.tv_sec - blas_start.tv_sec)*1000000LL + (blas_end.tv_usec - blas_start.tv_usec));
    //printf("Time for Brut = %lf\n", (brute_end.tv_sec - brute_start.tv_sec)*1000000LL + (brute_end.tv_usec - brute_start.tv_usec));

    printf("\n");fflush(stdout);
}
