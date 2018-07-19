#!/bin/bash

#SBATCH --job-name=pi

#SBATCH --output=parallel_pi.out

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=8

#SBATCH --partition=sandyb

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./parallel_pi.exec
