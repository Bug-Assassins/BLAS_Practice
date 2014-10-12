#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>
#include<ctime>
using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int n, mo = 1000;
	sscanf(argv[1],"%d",&n);
	printf("%d %d\n", n, mo);
	for(int i = 0; i < n; i++)
	{
        for(int j = 0; j < n; j++)
        {
            printf("%d %d\n",rand()%mo,rand()%mo);
        }
        printf("\n");
	}
	return 0;
}
