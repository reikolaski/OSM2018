#!/bin/bash -l

#SBATCH --job-name=scatter_mpi

#SBATCH --ntasks=16

#SBATCH --output=mpi_scatter.out

#SBATCH --partition=sandyb

module load openmpi

### MPI executable
mpiexec -np $SLURM_NTASKS ./scatter.exec
