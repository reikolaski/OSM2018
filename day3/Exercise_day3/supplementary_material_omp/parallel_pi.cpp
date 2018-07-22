#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <iostream>

using namespace std; 
double pi(int N)
{
    double x,y;
    int i;
    int count=0;
    double z;
    srand(time(0));
    double time = -omp_get_wtime();
    //main loop
    #pragma omp parallel for reduction(+:count)
    for (i=0; i<N; ++i)
    {
        //get random points
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));
       //check to see if point is in unit circle
        if (z<=1)
       	{
            count++;
       	}
    }
    time += omp_get_wtime();
    cout << "the solution took " << time << " seconds\n";
    return ((double)count/(double)N)*4.0;          //p = 4(m/n)
}

int main()
{
    printf("Pi: %f\n", pi(100)); 
    printf("Pi: %f\n", pi(1000)); 
    printf("Pi: %f\n", pi(10000)); 
    printf("Pi: %f\n", pi(100000)); 
    return 0;
}
