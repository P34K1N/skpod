#!/bin/bash

cd res

gcc -o command_file_gen command_file_gen.c -std=c99

for i in {5..8}
do
    for j in {9..9}
    do
        ((n=2**${i}))
        ((p=2**${j}))
        ./command_file_gen command.jcf ${p} ${n} "res_${p}_${n}.txt"
        llsubmit command.jcf
    done
done


