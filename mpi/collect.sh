#!/bin/bash

rm -f time.dat

for i in {5..8}
do
    for j in {5..9}
    do
        ((n=2**${i}))
        ((p=2**${j}))
        printf "${p} ${n} " >> time.dat
        cat res/res_${p}_${n}.txt >> time.dat
    done
done


