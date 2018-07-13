#include <cstdio>
#include <cstdlib>
#include <cmath>

double computePi(double n)
{
    double x, y, z; 
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        x = (double)random() / RAND_MAX;
        y = (double)random() / RAND_MAX;
        z = sqrt((x * x) + (y * y));
	if (z <= 1)
	{
	   count++;
	}
    }
    double pi = ((double)count / (double)n) * 4.0;    
    return pi;
}

int main()
{
    printf("Pi: %f\n", computePi(100));
    printf("Pi: %f\n", computePi(1000));    
    printf("Pi: %f\n", computePi(10000));
    printf("Pi: %f\n", computePi(10000000));

} 
