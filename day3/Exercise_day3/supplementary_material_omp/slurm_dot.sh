#!/bin/bash

#SBATCH --job-name=dot_prod

#SBATCH --output=dot_prod.out

#SBATCH --ntasks=8

#SBATCH --cpus-per-task=1

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./dot_prod.exec
