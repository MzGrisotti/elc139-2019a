#!/bin/bash
#SBATCH -J sum           # job name
#SBATCH -o sum.out     # output file name (%j expands to jobID), this file captures standered output from the shell
#SBATCH -e sum.err     # error file name (%j expands to jobID), this file captures errors generated from the program
#SBATCH  --nodes  1           # total number of nodes requested
#SBATCH --ntasks-per-node 1   # total number of proccess per node.
#SBATCH -p qCDER              # partition --qCDER (to find out available partitions please run 'sinfo' command)
#SBATCH --mem-per-cpu=1000    # request specific amount of RAM per CPU, now since we request 16 cores, the total amount of memory avilable for the program is 48GB

#SBATCH -t 00:10:00           # run time (hh:mm:ss) - 10 minutes
 
 
# execute any program
make -f Makefile
srun ./sum < sum.in
