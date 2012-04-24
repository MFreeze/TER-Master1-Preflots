#!/usr/bin/gnuplot

fil="ratio200"
dir="results/"
ext=".png"

ana=dir.fil
fout=dir.fil.ext

set term png
set output fout

plot ana using 1:3 with lines, ana using 1:4 with lines, ana using 1:5 with lines
