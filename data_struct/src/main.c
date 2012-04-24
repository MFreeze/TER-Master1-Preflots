#include "graph.h"
#include "algo.h"
#include "option.h"

#include <stdio.h>
#include <string.h>

int main (int argc, char ** argv) {    
	int print_graphviz = 0, ret_opt = 0, pref=0;
	FILE *stream = stdout;
	char *str = NULL, *fil = NULL;

	if ((ret_opt = treatOption(argc, argv, &print_graphviz, &fil, &str)) == -1) 
		return EXIT_FAILURE;

	if (str) {
		if (!strcmp (str, "stdout")) ;
		else if (!strcmp (str, "stderr"))
			stream = stderr;
		else
			if ((stream = fopen(str, "w")) == NULL)
				stream = stdout;
	}

  Graph *capa, *tmp;

	if (fil) 
		capa = createGraphFile (fil);
	else {
		capa = allocListGraph(10);
		tmp = allocGraph(capa);
  	/* http://en.wikipedia.org/wiki/Edmonds-Karp_algorithm#Example 
   	 * J'ai testé sur graph.h : testFill et celui là ^ ^ ^ ^ ^ ^ ^
   	 * J'ai vérifié que les chaines améliorantes sont bonnes.
   	 * Il faudrait peut etre tester un peu plus ? */
		randFill(capa, 20, 10, 1, tmp);
	}
  /* flow nul */
  Graph *flow = allocGraph(capa);
  Graph *flowbis = allocGraph(capa);
	Graph *flowter = allocGraph(capa);
  /* ecart = capacité */
  Graph *diff = allocGraph(capa);
  Graph *diffbis = allocGraph(capa);
	/* Ensemble des plus courts chemins */
	Graph *shpath = setShortPath(capa, 0, 1);
	/* Test du graphe de couche */
	printf("\n\nDinic : \n\n");
	int fbis = algoDinic (capa, flowbis, 0, 1);
	printf("\n\nFIFO : \n\n");
	int fter = algoFIFO (capa, diffbis, flowter, 0, 1);
	printf("\n\nLabel : \n\n");
	int f = algoLabel (capa, diff, flow, 0, 1);
	printf ("Max Flow = %3d\n, Max Flow = %3d\n, Max Flow = %3d\n", f, fbis, fter);
  printGraph(stream, diff, print_graphviz, &pref);
  printGraph(stream, flow, print_graphviz, &pref);
	printGraph(stream, shpath, print_graphviz, &pref);
  printGraph(stream, flowbis, print_graphviz, &pref);
  printGraph(stream, flowter, print_graphviz, &pref);
  printGraph(stream, diffbis, print_graphviz, &pref);

	freeGraph(capa); freeGraph(diff);
	freeGraph(flow); freeGraph(shpath);
	freeGraph(flowbis);
	freeGraph(flowter); freeGraph (diffbis);
	freeGraph(tmp);

	if (stream != stdout && stream != stderr) {
		if (print_graphviz) 
			fprintf (stream, "}\n");
		fclose(stream);
	}
    return 0;
}
