#include "bench.h"
#include "graph.h"
#include "algo.h"

// {{{ elapsedTime
stat_t elapsedTime (int n, int m, int c, int nb_iter) {
	int i=0;
	stat_t result;
	GTimer *timer = g_timer_new();

	memset(&result, 0, sizeof(stat_t));

	for (i=0; i< nb_iter; i++) {

		// Graph Initialization
    Graph * lcLab = allocListGraph(n);
    Graph * lcFIFO = allocListGraph(n);
    randFill(lcLab,m,c,1,lcFIFO);
		Graph *lcDinic = copyGraph(lcLab);

    int f,g,h;

		// FIFO Algorithm
    Graph * lfFIFO = allocGraph(lcFIFO);
    Graph * ldFIFO = allocGraph(lcFIFO);

//		printf ("Entrée FIFO\n");
		g_timer_start(timer);
    h=algoFIFO (lcFIFO,ldFIFO,lfFIFO,0,1);
		g_timer_stop(timer);
//		printf ("Sortie FIFO\n");

		freeGraph(ldFIFO); freeGraph(lfFIFO); 

		if (h) {
			result._st1 += (double) g_timer_elapsed(timer, NULL);
			g_timer_reset(timer);

			// High Label Algorithm
			Graph * lfLab = allocGraph(lcLab);
			Graph * ldLab = allocGraph(lcLab);

//			printf ("Entrée High Label\n");
			g_timer_start(timer);
			g=algoLabel (lcLab,ldLab,lfLab,0,1);
			g_timer_stop(timer);
			result._st2 += (double) g_timer_elapsed(timer, NULL);
			g_timer_reset(timer);
//			printf ("Sortie High Label\n");

			freeGraph(lfLab); freeGraph(ldLab);


			// Dinic Algorithm
			Graph * lfDinic = allocGraph(lcLab);

//			printf("Entrée Dinic\n");
			g_timer_start(timer);
			f=algoDinic (lcDinic,lfDinic,0,1);
			g_timer_stop(timer);
			result._st3 += (double) g_timer_elapsed(timer, NULL);
			g_timer_reset(timer);
//			printf("Sortie Dinic\n");

			freeGraph (lfDinic);

//			printf ("%d %d %d \n", f, g, h);
			if (f!=g || g!=h)
				result._st4 ++;
		}
		else {
			printf ("Flot nul.\n");
			g_timer_reset(timer);
			i --;
		}

		if (f!=h || g!=h)
			printf ("Erreur\n");
    
		freeGraph (lcFIFO); 
		freeGraph (lcLab);
		freeGraph (lcDinic);
	}

	result._st1 /= nb_iter;
	result._st2 /= nb_iter;
	result._st3 /= nb_iter;
	result._st4 /= nb_iter;

	g_timer_destroy(timer);


	return result;
}
// }}}
