#include "mat_graph.h"

// {{{ Macros
#define mat(mg) mg->_mat
#define nbVert(mg) mg->_nbVert
#define nbEdge(mg) mg->_nbEdge
// }}}

int  m_edgeVal(MatGraph *mg, int i, int j) {
  return mat(mg)[i][j];
}

void m_setEdge(MatGraph *mg, int i, int j, int val) {
  int prev = mat(mg)[i][j];
  mat(mg)[i][j] = val;
  if (prev == 0 && val != 0) nbEdge(mg)++;
  else if (prev != 0 && val == 0) nbEdge(mg)--;
}

List *m_inNeighb(MatGraph *mg, int k) {
  List *res = allocList();
  int i;
  for (i = 0; i < nbVert(mg); i++) {
    int val = mat(mg)[i][k];
    if (val != 0 && i != k) pushTail(res, i, val);
  }
  return res;
}

List *m_outNeighb(MatGraph *mg, int k) {
  List *res = allocList();
  int j;
  for (j = 0; j < nbVert(mg); j++)
  {
    int val = mat(mg)[k][j];
    if (val != 0 && j != k) pushTail(res, j, val);
  }
  return res;
}

MatGraph *m_copyGraph (MatGraph *mg) {
  if (mg == NULL) return NULL ;
  MatGraph * res = m_allocGraph (nbVert(mg));
  nbEdge(res) = nbEdge(mg);
  int i, j;
  for (i = 0; i < nbVert(mg); i++) 
    for (j = 0; j < nbVert(mg); j++)
      mat(res)[i][j] = mat(mg)[i][j];
  return res;
}

MatGraph *m_allocGraph (int n) {
  MatGraph * res = (MatGraph*) malloc (sizeof (MatGraph));
  nbVert(res) = n;
  nbEdge(res) = 0;
  mat(res) = (int**) malloc (n * sizeof (int*));
  int i;
  for (i=0; i < n; i++) 
    mat(res)[i] = (int*) calloc (n, sizeof (int));
  return res;
}

void m_freeGraph (MatGraph *mg) {
  if (mg == NULL) return ;
  int i;
  for (i = 0; i < nbVert(mg); i++)
    free (mat(mg)[i]);
	free (mat(mg));
  free (mg);
}

void m_printGraph (FILE *stream, MatGraph *g, int graphviz, int pref) {
	if (!g) return;
	if (!graphviz) {
		fprintf (stream, "*** %3d vertices - %3d edges ***\n", nbVert(g), nbEdge(g));
		int i, j, k;
		for (i=0; i<nbVert(g); i++) {
			fprintf (stream, "Out%3d : ", i);
			for (j=0; j<nbVert(g); j++)
				if ((k=m_edgeVal(g, i, j)) != 0)
					fprintf (stream, "%2d (%2d) - ", j, k);
			fprintf(stream, "\n");	
			fprintf (stream, "In%4d : ", i);
			for (j=0; j<nbVert(g); j++)
				if ((k=m_edgeVal(g, j, i)) != 0)
					fprintf (stream, "%2d (%2d) - ", j, k);
			fprintf(stream, "\n");	
		}
	}
	else {
		if (pref == 1)
			fprintf (stream, "digraph {\n");
		int i, j, k;
		for (i=0; i < nbVert(g); i++) 
			fprintf (stream, "%d%d [label=%d] \n", pref, i, i);	
		for (i=0; i< nbVert(g); i++) 
			for (j=0; j<nbVert(g); j++)
				if ((k = m_edgeVal(g, i, j)) != 0)
					fprintf (stream, "%d%d -> %d%d [label=%d]\n", pref, i, pref, j, k);
	}
}
