set terminal svg size 600,500
set output 'plot.svg'
set title 'Time measurements'
set dgrid3d 10,8
set zrange [0.001:2.5]
splot 'grid.dat' u 2:1:3 with lines

