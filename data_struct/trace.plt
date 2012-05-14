#!/usr/bin/gnuplot

fil="result_arete"
dir="results/"
ext=".png"

ana=dir.fil
fout=dir.fil.ext

set term png
set output fout

plot ana using 2:3 with lines title "FIFO", ana using 2:4 with lines title "High Label", ana using 2:5 with lines title "Dinic"
