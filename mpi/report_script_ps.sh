#!/bin/bash

cd res

gcc -o command_file_gen command_file_gen.c -std=c99

for i in {5..8}
do
    for j in {1..4}
    do
        ((n=2**${i}))
        ((p=2**${j}))
        bsub -n ${p} ../adi_3d ${n} "res_${p}_${n}.txt"
    done
done


