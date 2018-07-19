#!/bin/bash

#SBATCH --job-name=normalize

#SBATCH --output=normalize.out

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=8

#SBATCH --partition=sandyb

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./normalize_vec.exec
