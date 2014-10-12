#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double * house(const double x[], const int m, int *beta)
{
    double sig = 0, *vec;
    vec = (double *)malloc(sizeof(double) * m);
    vec[0] = 1;
    int i;
    for(i = 1; i < m; i++)
    {
        sig += x[i] * x[i];
        vec[i] = x[i];
    }

    if(sig == 0)
    {
        if(x[0] >= 0)
        {
            *beta = 0;
            return vec;
        }
        else
        {
            *beta = -2;
            return vec;
        }
    }
    else
    {
        double mu = sqrt((x[0]*x[0]) + sig);
        if(x[0] <= 0)
        {
            vec[0] = x[0] - mu;
        }
        else
        {
            vec[0] = (- sig) / (x[0] + mu);
        }
        *beta = (2*vec[0]*vec[0]) / (sig + (vec[0]*vec[0]));
        for(i = 0; i < m; i++)
            vec[i] = vec[i] / vec[0];
        return vec;
    }
}

void mat_mul_brute(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void hessenberg(int mat[][], int n)
{
    int k, j, i, m;
    double *v, b, *temp, **temp_mat;
    for(k = 1; k < n - 2; k++)
    {
        temp =  (double *)malloc(sizeof(double)*(n-k));
        for(j = 0; j < (n-k); j++)
            temp[j] = mat[j+k][k-1];
        v = house(temp, n-k, &b);

        temp_mat = (int**)malloc(sizeof(int*)*(n-k));

        for(i = 0; i < n - k; i++)
        {
            temp_mat[i] = (int *) malloc(sizeof(int)*(n-k+1));
        }

        for(i = 0; i < n - k ; i++)
            for(j = 0; j < n - k + 1; j++)
                for(m = 0; m < n - k; m++)
                {
                    temp_mat[i][j] += ((m==i?1:0) - (b*v[i]*v[m])) * (mat[m+k][j+k-1]);
                }
        for(i = 0; i < n - k ; i++)
            for(j = 0; j < n - k + 1; j++)
                mat[i+k][j+k-1] = temp_mat[i][j];

        for(i = 0; i < n - k; i++)
        {
            free(temp_mat[i]);
        }
        free(temp_mat);
        free(v);
        temp_mat = (double**)malloc(sizeof(double *)*n);
        for(i = 0; i < n; i++)
        {
            temp_mat = (double*)malloc(sizeof(double)*(n-k));
        }
        for(i = 0; i < n; i++)
            for(j = 0; j < n - k; j++)
                for(m = 0; m < n - k; m++)
                {
                }
                temp
    }
}

int main()
{
    return 0;
}
