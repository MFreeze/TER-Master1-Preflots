/*
 * =====================================================================================
 *
 *       Filename:  fifo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/04/2012 14:35:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DUVILLIE Guillerme (mfreeze), guillerme.duvillie@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list_graph.h"
#include "mat_graph.h"
#include "algo.h"
#include "option.h"

int main (int argc, char **argv) {
	int FIFO = 0, LABE = 0;
	while (FIFO == LABE) {
		Graph *random_fifo = allocListGraph(5);
		Graph *random_labe = allocListGraph(5);

		randFill (random_fifo, 10, 10, 1, random_labe);
		Graph *diff_FIFO = copyGraph(random_fifo);
		Graph *flot_FIFO = allocGraph(random_fifo);

		Graph *save = copyGraph(random_fifo);

			int f = 0;
			FILE* fil = fopen ("sauvegarde_graph_defaut.dot", "w");
			printGraph (fil, save, 1, &f);
			fclose (fil);

		Graph *diff_labe = copyGraph(random_labe);
		Graph *flot_labe = allocGraph(random_labe);

		FIFO = algoFIFO(random_fifo, diff_FIFO, flot_FIFO, 0, 1);
		LABE = algoLabel(random_labe, diff_labe, flot_labe, 0, 1);

		if (FIFO != LABE) {
		}

		freeGraph(random_labe);
		freeGraph(random_fifo);
		freeGraph(diff_labe);
		freeGraph(diff_FIFO);
		freeGraph(flot_labe);
		freeGraph(flot_FIFO);
		freeGraph(save);
	}

	return 1;

}

