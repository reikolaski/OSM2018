#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, proc, totalCount, tag, npoints, num, count;
    double x, y, z, pi;
    int master = 0;
    MPI_Comm comm;
    MPI_Status status;
    
    comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    npoints = 100000; 
    num = npoints / size;
    int i;
    count=0;
    tag = 123;
    //main loop
    for (i=0; i<num; ++i)
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

    MPI_Send(&count, 1, MPI_DOUBLE, master, tag, comm);

    if(rank == master){
        totalCount = 0;
        for (proc=0; proc<size; proc++) {
            MPI_Recv(&count, 1, MPI_DOUBLE, proc, tag, comm, &status); 
            totalCount += count;
        }
        pi = ((double)totalCount/(double)npoints)*4.0;          //p = 4(m/n)
        printf("Pi: %f\n", pi); 
    }
    MPI_Finalize();
    return 0;
}

