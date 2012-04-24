#!/bin/bash

for i in  1 2 5 10 25 50 75 100 130 170 200; do
	sed -e "s/\#define RATIO [0-9]*/\#define RATIO $i/g" src/test.c > /tmp/test.c
	sed -e "s/fil=\"ratio[0-9]*\"/fil=\"ratio$i\"/g" trace.plt > /tmp/trace.plt
	cp /tmp/trace.plt trace.plt
	cp /tmp/test.c src/test.c
	make bin/test
	bin/test > results/"ratio$i"
	gnuplot trace.plt
done
