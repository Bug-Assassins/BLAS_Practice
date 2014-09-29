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

int main()
{
    blasint n = 3;
    double A[] = {
    1, 2, 3,
    2, 4, 5,
    3, 5, 6
    };

    std::vector<double> p_x(n);
    std::vector<double> p_y(n);

    std::fill(p_x.begin(),p_x.end(),1.0);
    std::fill(p_y.begin(),p_y.end(),2.0);

    cblas_dsymv (CblasRowMajor, CblasUpper, n, 1.0, A, n, &p_x[0], 1, 1.0, &p_y[0], 1);

    for(int j=0;j<n;j++)
        std::cout << p_y[j] << "\t";

    std::cout << std::endl;

    return 0;
}
