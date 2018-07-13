#!/bin/bash

#SBATCH --job-name=monteCarloPi

#SBATCH --output=monteCarlo.out

#SBATCH --ntasks=1

#SBATCH --partition=sandyb

./monteCarlo.exe
