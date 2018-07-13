#!/bin/bash

#SBATCH --job-name=compute_pi

#SBATCH --output=computePi.out

#SBATCH --ntasks=1

#SBATCH --partition=sandyb

./computePi
