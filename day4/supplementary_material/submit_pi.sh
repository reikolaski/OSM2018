#!/bin/bash

#SBATCH --job-name=pi_hybrid

#SBATCH --output=hybrid_pi.out

#SBATCH --ntasks=4

#SBATCH --cpus-per-task=8

#SBATCH --partition=sandyb

module load openmpi

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

mpirun ./pi_openmp_parallel.exec
