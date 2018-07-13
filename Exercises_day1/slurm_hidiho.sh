#!/bin/bash

#SBATCH --job-name=hidiho

#SBATCH --output=hidiho.out

#SBATCH --ntasks=1

#SBATCH --partition=sandyb

./hidiho.exec
