#!/bin/bash -l

#SBATCH --job-name=pi-mpi

#SBATCH --ntasks=10

#SBATCH --output=mpi_pi.out

#SBATCH --partition=sandyb

module load openmpi

### MPI executable
mpiexec -np $SLURM_NTASKS ./pi.exec
