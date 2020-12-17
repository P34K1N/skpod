#!/bin/bash

rm *.dat

gcc -o adi_3d adi_3d.c -fopenmp -lm -std=c11
for i in {5..8}
do
    for j in {0..7}
    do
        ((n=2**${i}))
        ((p=2**${j}))
        for k in 1..5
        do
            ./adi_3d ${n} ${p} >> meas.txt
        done
        printf "${n} ${j} " >> grid.dat
        awk '{ total += $1; count++ } END  {print total / count}' meas.txt >> grid.dat
        rm meas.txt
    done
done
