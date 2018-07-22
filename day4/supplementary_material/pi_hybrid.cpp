#include <iostream>
#include <cmath>
#include <mpi.h>
#include <omp.h>

#define _USE_MATH_DEFINES

const int num_steps = 5000000;

int main(int argc, char *argv[]){
    int num_procs, rank, tag, proc, num;
    int i;
    double ai, x;
    int master = 0;
    double sum = 0.0;
    double pi  = 0.0;
    num = num_steps / num_procs;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    tag = 123;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &num_procs);
    MPI_Comm_rank(comm, &rank);

//    std::cout << "using " << omp_get_max_threads() << " OpenMP threads" << std::endl;

    ai = rank / num_procs;
    const double w = 1.0/double(num_steps);

    double time = -omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<num; ++i) {
        x = ai + (i+0.5)*w;
        sum += 4.0/(1.0+x*x);
    }

    MPI_Send(&sum, 1, MPI_DOUBLE, master, tag, comm);

    if(rank == master){
        for(proc=0; proc<num_procs; proc++) {
            MPI_Recv(&sum, 1, MPI_DOUBLE, proc, tag, comm, &status);
            pi += sum;
        }
        pi *= w/double(num_procs);
        time += omp_get_wtime();

        std::cout << num_steps
              << " steps approximates pi as : "
              << pi
              << ", with relative error "
              << std::fabs(M_PI-pi)/M_PI
              << std::endl;
        std::cout << "the solution took " << time << " seconds" <<std::endl;

    }
    MPI_Finalize();

}
