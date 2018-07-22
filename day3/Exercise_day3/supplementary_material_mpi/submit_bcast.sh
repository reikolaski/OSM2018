#!/bin/bash -l

#SBATCH --job-name=bcast-mpi

#SBATCH --ntasks=16

#SBATCH --output=mpi_bcast.out

#SBATCH --partition=sandyb

module load openmpi

### MPI executable
mpiexec -np $SLURM_NTASKS ./broadcast.exec
