#include "graph.h"
#include "algo.h"
#include "option.h"
#include "bench.h"

#include <stdio.h>
#include <string.h>

#define MAX_RATIO 200
#define SCALE 100
#define NOEUD 100

int main (int argc, char ** argv)
{    
  int max = NOEUD * NOEUD / SCALE + 2;
  int capa = 50;
  int ** tab = (int**) malloc (max * sizeof(int*));
  int i;
  for (i=SCALE; i<=NOEUD*NOEUD; i+=SCALE) {
		int j = (i/SCALE) - 1;
		tab[j] = (int *) malloc(2*sizeof(int));
		tab[j][0] = NOEUD;
		tab[j][1] = i;
	}

  for (i=SCALE; i<=NOEUD*NOEUD; i+=SCALE) {
		int j = (i/SCALE) - 1;
    stat_t s = elapsedTime(tab[j][0],tab[j][1],capa,20);
    printf("%d %d %lf %lf %lf \n",tab[j][0],tab[j][1],s._st1*1000,s._st2*1000,s._st3*1000);
  }

  /*Graph * mcEK = allocMatGraph(5);

    Graph * lcEK = allocListGraph(5);

    randFill(mcEK,15,5,1,lcEK);

    Graph * mcDinic = copyGraph(mcEK);
    Graph * lcDinic = copyGraph(lcEK);

    Graph * mdEK = copyGraph(mcEK);
    Graph * mfEK = allocGraph(mcEK);

    Graph * mdDinic = copyGraph(mcDinic);
    Graph * mfDinic = allocGraph(mcDinic);

    Graph * lfEK = allocGraph(lcEK);
    Graph * ldEK = copyGraph(lcEK);

    Graph * lfDinic = allocGraph(lcDinic);

    int mEK = algoEdmondKarp (lcEK,ldEK,lfEK,0,1);
    printf("EK    : Matrix = %d\n", mEK);

    int mDinic = algoDinic (mcDinic,mfDinic,0,1);
    printf("Dinic : Matrix = %d\n", mDinic);

    int lDinic = algoDinic (lcDinic,lfDinic,0,1);
    printf("Dinic : List   = %d\n", lDinic);

    int lEK = algoEdmondKarp (mcEK,mdEK,mfEK,0,1);
    printf("EK    : List   = %d\n", lEK);
    */

  for (i=0; i<max; free(*(tab+i++)));
	free(tab);

  argc++;argv--;/* Wall ... */
  return 0;
}
