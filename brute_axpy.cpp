#include<cstdio>
#include<vector>
#include<cblas.h>
#include<sys/time.h>
#include<cstdlib>
#include<ctime>
#define MAX_ITER 1
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
    //gettimeofday(&blas_start, NULL);
    blas_start = time(NULL);
    for(int j = 0 ;j < MAX_ITER;j++)
        cblas_daxpy( n, alpha, &x[0], in_x, &y[0], in_y);
    //gettimeofday(&blas_end, NULL);
    blas_end = time(NULL);
    printf("Done \n");fflush(stdout);

    printf("Starting brute operation .......");fflush(stdout);
    //gettimeofday(&brute_start, NULL);
    brute_start = time(NULL);
    for(int j = 0 ;j < MAX_ITER;j++)
        for(int i =0 ;i < n ; i++)
        {
            yb[i] = yb[i] + (xb[i]*alpha);
        }
    //gettimeofday(&brute_end, NULL);
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

    printf("Time for Blas = %lf\n",difftime(blas_end, blas_start));fflush(stdout);
    printf("Time for Brute = %lf\n",difftime(brute_end, brute_start));fflush(stdout);
    //printf("Time for Blas = %lf\n", (blas_end.tv_sec - blas_start.tv_sec)*1000000LL + (blas_end.tv_usec - blas_start.tv_usec));
    //printf("Time for Brut = %lf\n", (brute_end.tv_sec - brute_start.tv_sec)*1000000LL + (brute_end.tv_usec - brute_start.tv_usec));

    printf("\n");fflush(stdout);
}
