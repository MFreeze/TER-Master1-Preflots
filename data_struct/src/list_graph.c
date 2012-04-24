#include "list_graph.h"

#include <stdio.h>

//{{{ Macros
#define in(lm) lm->_inNeighb
#define out(lm) lm->_outNeighb
#define nbVert(lm) lm->_nbVert
#define nbEdge(lm) lm->_nbEdge
//}}}


// {{{ Graph Informations
// {{{ l_edgeVal
int  l_edgeVal(ListGraph *lg, int i, int j) {
	return valOfNum(out(lg)[i], j);
}
// }}}

// {{{ l_setEdge
void l_setEdge (ListGraph *lg, int i, int j, int val) {
  int before = nb(out(lg)[i]);
  insertNum(out(lg)[i], j, val);
  insertNum(in(lg)[j], i, val);
  int after = nb(out(lg)[i]);
  if (before < after) nbEdge(lg)++;
  if (after < before) nbEdge(lg)--;
}
// }}}

// {{{ l_inNeighb
List *l_inNeighb (ListGraph *lg, int k) {
  return copyList(in(lg)[k]);
}
// }}}

// {{{ l_outNeighb
List *l_outNeighb (ListGraph *lg, int k) {
  return copyList(out(lg)[k]);
}
// }}}
// }}}

// {{{ Memory management
// {{{ l_copyGraph
ListGraph *l_copyGraph(ListGraph *lg) {
  if (lg == NULL) return NULL;
  ListGraph * res = (ListGraph*) malloc (sizeof (ListGraph));
  nbEdge(res) = nbEdge(lg);
  int n = nbVert(lg), i = 0;
  nbVert(res) = n;
  out(res) = (List**) malloc (n * sizeof (List*));
  in(res) = (List**) malloc (n * sizeof (List*));
  for (i = 0; i < nbVert(lg); i++) {
    out(res)[i] = copyList(out(lg)[i]);
    in(res)[i] = copyList(in(lg)[i]);
  }
  return res;
}
// }}}

// {{{ l_allocGraph
ListGraph *l_allocGraph(int n) {
  ListGraph * res = (ListGraph*) malloc (sizeof (ListGraph));
  nbEdge(res) = 0;
  nbVert(res) = n;
  int i;
  out(res) = (List**) malloc (n * sizeof (List*));
  for (i = 0; i < n; i++) 
    out(res)[i] = allocList();
  in(res) = (List**) malloc (n * sizeof (List*));
  for (i = 0; i < n; i++)
    in(res)[i] = allocList();
  return res;
}
// }}}

// {{{ l_freeGraph
void l_freeGraph (ListGraph *lg) {
  if (lg != NULL) {
    int i;
    for (i = 0; i < nbVert(lg); i++) {
      freeList(out(lg)[i]);
      freeList(in(lg)[i]);
    }
		free(out(lg));
		free(in(lg));
    free (lg);
  }
}
// }}}
// }}}

// {{{ Display functions
// {{{ l_printListGraph
void l_printListGraph (FILE *f, ListGraph *lg, int graphviz, int pref) {
  if (lg == NULL) return;
	if (!graphviz) {
  	fprintf (f,"*** %3d vertices - %3d edges ***\n", nbVert(lg), nbEdge(lg));
  	int i;
  	for (i = 0; i < nbVert(lg); i++)
  	{
    	fprintf (f,"Out%3d : ", i);
    	printList(f, out(lg)[i]);
    	fprintf (f,"In %3d : ", i);
    	printList(f, in(lg)[i]);
    	fprintf (f, "\n");
  	}
  	fprintf (f, "*** *** *** ***\n");
	}
	else {
		if (pref == 1)
			fprintf (f, "digraph {\n");
		int i;
		for (i=0; i < nbVert(lg); i++) 
			fprintf (f, "%d%d [label=%d] \n", pref, i, i);	
		for (i=0; i< nbVert(lg); i++) {
			List *temp = l_outNeighb(lg, i);
			Item *it = begin(temp);
			while (it) {
				fprintf (f, "%d%d -> %d%d [label=%d]\n", pref, i, pref, num(it), val(it));
				it = next(it);
			}
		}
	}
}
//}}}
//}}}

