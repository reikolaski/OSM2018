#!/bin/bash -l

#SBATCH --job-name=allreduce_mpi

#SBATCH --ntasks=16

#SBATCH --output=mpi_allreduce.out

#SBATCH --partition=sandyb

module load openmpi

### MPI executable
mpiexec -np $SLURM_NTASKS ./allreduce.exec
