#include "graph.h"

// {{{ Statistics
// {{{ Factorial
int fact (int n) {
	int result = 1;
	while (n > 1)
		result *= n--;
	return result;
}
// }}} 

// {{{ poisson
int poisson (int lambda) {
	int n = 0;
	double r = (1.*rand())/RAND_MAX, comp = exp( -1 * lambda) * ( pow(lambda, n) / fact(n));
	while (comp < r){
		comp += exp(-1*lambda)*(pow(lambda,n)/fact(n));
		n++;
	}

	return n;
}
// }}}

// {{{ Specific List function
int valRank (List *l, int rank) {
	if (l) {
  	if (nb(l) == 0 || rank < 0 || rank >= nb(l)) return 0;
  	Item * it = begin(l);
		int i = 0;
  	while (i++ < rank) it = next(it);
  	return val(it);
	}
  return 0;
}
// }}}
// }}}

// {{{ Memory management
// {{{ allocMatGraph
Graph *allocMatGraph(int n) {
  Graph *res = (Graph*)malloc(sizeof(Graph));
  mg(res) = m_allocGraph(n);
  lg(res) = NULL;	
	glab(res) = (int *) calloc (sizeof(int), n);
	if (!glab(res)) {
		fprintf (stderr, "calloc label");
		freeGraph (res);
		return NULL;
	}
	gexc(res) = (int *) calloc (sizeof(int), n);
	if (!gexc(res)){
		fprintf (stderr, "calloc excedent\n");
		freeGraph (res);
		free (glab(res));
		return NULL;
	}
  return res;
}
// }}}

// {{{ allocListGraph
Graph *allocListGraph (int n) {
  Graph *res = (Graph*)malloc(sizeof(Graph));
  lg(res) = l_allocGraph(n);
  mg(res) = NULL;
	glab(res) = (int *) calloc (sizeof(int), n);
	if (!glab(res)) {
		fprintf (stderr, "calloc label");
		freeGraph (res);
		return NULL;
	}
	gexc(res) = (int *) calloc (sizeof(int), n);
	if (!gexc(res)){
		fprintf (stderr, "calloc excedent\n");
		freeGraph (res);
		free (glab(res));
		return NULL;
	}
  return res;
}
// }}}

// {{{ allocGraph
Graph *allocGraph(Graph *g) {
  if (g == NULL) return NULL;
  if (mg(g) != NULL) return allocMatGraph(nbVert(g));
  if (lg(g) != NULL) return allocListGraph(nbVert(g));
  return NULL;
}
// }}}

// {{{ createGraphFile
Graph *createGraphFile (const char *fil) {
	int nodes=0, edges=0;
	float ratio;
	Graph *graph;
	FILE *file = fopen(fil, "r");
	if (!file)
		return NULL;

	fscanf (file, "%d %d\n", &nodes, &edges);
	if ((ratio = (1.*edges)/(1.*nodes)) >= 0.75*nodes)
		graph = allocMatGraph(nodes);
	else
		graph = allocListGraph(nodes);

	int a,b, val;
	while (fscanf(file, "%d %d %d\n", &a, &b, &val) != EOF)
  	setEdge(graph, a, b , val);

	fclose(file) ;

	return graph;
}
// }}}

// {{{ freeGraph
void freeGraph(Graph *g) {
  if (g) {
    if (mg(g)) m_freeGraph(mg(g));
    if (lg(g)) l_freeGraph(lg(g));
		if (glab(g)) free (glab(g));
		if (gexc(g)) free (gexc(g));
    free (g);
  }
}
// }}}

// {{{ copyGraph
Graph *copyGraph(Graph *g) {
  if (g == NULL) return NULL;
  Graph * res = (Graph*) malloc(sizeof(Graph));
  mg(res) = NULL; lg(res) = NULL;
  if (mg(g)) mg(res) = m_copyGraph(mg(g));
  if (lg(g)) lg(res) = l_copyGraph(lg(g));
	glab(res) = (int *) calloc (sizeof(int), nbVert(g));
	if (!glab(res)) {
		fprintf (stderr, "calloc label");
		freeGraph (res);
		return NULL;
	}
	int i = 0; 
	gexc(res) = (int *) calloc (sizeof(int), nbVert(g));
	if (!gexc(res)){
		fprintf (stderr, "calloc excedent\n");
		freeGraph(res);
		free (glab(res));
		return NULL;
	}
	for (i=0; i<nbVert(g); lab(res,i) = lab(g,i), exc(res,i) = exc(g,i), i++);
  return res;
}
// }}}

static int rand_init = 0;

// {{{ randFill
void randFill(Graph *g, int m, int cMax, int cMin, Graph *g2) {

  if (g == NULL) return;
  if (g2 != NULL && nbVert(g) != nbVert(g2)) g2 = NULL;
  if (m > (nbVert(g) * nbVert(g))) m = nbVert(g) * nbVert(g);
	if (m < nbVert(g) - 1 ) m = nbVert(g) - 1;
  if ( (cMax * cMin) == 0){ cMax++; cMin ++;} /* il y a 0 dans l'intervalle */
  if (cMax <= cMin) { int t = cMax; cMax = cMin; cMin = t; }
  if (rand_init == 0) {
    srand (time (NULL));
    rand_init = 1;
  }

  if (m > nbVert(g) * (nbVert(g)-2)) {
    int i,j,c;
		int to_remove = (nbVert(g)-2)*nbVert(g) - m;
    for (i=0; i < nbVert(g); i++) 
      for (j=0; j<nbVert(g); j++) {
        c = rand () % (cMax - cMin) + cMin;
        if (c <= 0) c = 1;
        /* if (c == 0) { printf ("c=0\n");} */ /* Test, 0 enleve des arretes */
        if (i != j && edgeVal(g, i, j) <= 0) {
          setEdge(g,  i, j, c);
          setEdge(g2, i, j, c);
        }
      }

		if (to_remove > 0) {
			for (i=0; i < to_remove; i++){
				int s1 = rand() % nbVert(g), s2 = rand() % nbVert(g);
				while (s1 == s2){
					s2 = rand() % nbVert(g);
					s1 = rand() % nbVert(g);
				}

				if (edgeVal(g, s1, s2) == 0)
					i --;
				else {
					setEdge(g, s1, s2, 0);
					setEdge(g2, s1, s2, 0);
				}
			}
		}
  }else {
		int deg_moyen = m/nbVert(g), i=0;
		List *connexe = allocList(), *non_connexe=allocList();

		for (i=0; i<nbVert(g); i++)
			pushTail(non_connexe, i, i);

		int rank = rand() % nb(non_connexe);
		int source = valRank(non_connexe, 0);

		popNum(non_connexe, source);
		pushTail(connexe, source, source);

		rank = rand() % nb(non_connexe);
		int dest = valRank(non_connexe, rank);

		while (dest == source) {
			rank = rand() % nb(non_connexe);
			int dest = valRank(non_connexe, rank);
		}

		popNum (non_connexe, dest);
		pushTail(connexe, dest, dest);

    int c = rand () % (cMax - cMin) + cMin;
    if (c <= 0) c=1;

		setEdge (g, source, dest, c);
		setEdge (g2, source, dest, c);
		m--;

		while (nb(non_connexe)) {
			rank = rand () % nb(non_connexe);
			dest = valRank(non_connexe, rank);

			rank = rand() % nb(connexe);
			source = valRank(connexe, rank);

			while (dest == source) {
				rank = rand () % nb(non_connexe);
				dest = valRank(non_connexe, rank);
			}

			c = rand () % (cMax - cMin) + cMin;
			if (c <= 0) c = 1;

			setEdge(g, source, dest, c);
			setEdge(g2, source, dest, c);
			m--;

			popNum(non_connexe, dest);
			pushTail(connexe, dest, dest);
		}

		Item *it = begin(connexe);
		while (it && m) {
			int nb_voisin = poisson(deg_moyen);
			nb_voisin = nb_voisin > m ? m : nb_voisin;
			int tmp = 0; int try = 0;
			while (tmp < nb_voisin && try < nbVert(g)) {
				rank = rand()%nb(connexe);
				dest = valRank (connexe, rank);
				if (num(it) == dest || edgeVal(g, source, dest) )
					try++;
				else { 
					c = rand () % (cMax - cMin) + cMin;
					if (c <= 0) c=1;

					try = 0;
					setEdge(g, source, dest, c);
					setEdge(g2, source, dest, c);
					m --;
					tmp ++;
				}
			}
			it = next(it);
		}
		int z = 0;
		while (m) {
			rank = rand() % nb(connexe);
			source = valRank (connexe, rank);
			rank = rand() % nb(connexe);
			dest = valRank (connexe, rank);

			if (source != dest && edgeVal(g, source, dest) == 0) {
				c = rand () % (cMax - cMin) + cMin;
				if (c == 0) c++;

				setEdge(g, source, dest, c);
				setEdge(g2, source, dest, c);
				m --;
			}
		}
		freeList(connexe);
		freeList(non_connexe);
  }
}
// }}}

// {{{ testFill
void testFill(Graph *g) {
  setEdge(g, 0, 1, 5);
  setEdge(g, 0, 2, 8);
  setEdge(g, 1, 3, 3);
  setEdge(g, 1, 2, 2);
  setEdge(g, 2, 3, 2);
  setEdge(g, 2, 4, 1);
  setEdge(g, 3, 4, 2);
  setEdge(g, 3, 5, 4);
  setEdge(g, 4, 5, 4);
}
// }}}

// }}}

// {{{ Graph informations
// {{{ edgeVal
int edgeVal(Graph *g, int i, int j) {
  if (g == NULL) return 0;
  if (mg(g) != NULL) return m_edgeVal(mg(g), i, j);
  if (lg(g) != NULL) return l_edgeVal(lg(g), i, j);
  return 0;
}
// }}}

// {{{ setEdge
void setEdge(Graph *g, int i, int j, int val) {
  if (g == NULL) return;
  if (mg(g) != NULL) return m_setEdge(mg(g), i, j, val);
  if (lg(g) != NULL) return l_setEdge(lg(g), i, j, val);
}
// }}}

// {{{ inNeighb
List *inNeighb(Graph *g, int k) {
  if (g == NULL) return NULL;
  if (mg(g) != NULL) return m_inNeighb(mg(g), k);
  if (lg(g) != NULL) return l_inNeighb(lg(g), k);
  return NULL;
}
// }}}

// {{{ outNeighb
List *outNeighb(Graph *g, int k) {
  if (g == NULL) return NULL;
  if (mg(g) != NULL) return m_outNeighb(mg(g), k);
  if (lg(g) != NULL) return l_outNeighb(lg(g), k);
  return NULL;
}
// }}}

// {{{ nbVert
int nbVert (Graph *g) {
  if (g == NULL) return 0;
  if (mg(g) != NULL) return mg(g)->_nbVert;
  if (lg(g) != NULL) return lg(g)->_nbVert;
  return 0;
}
// }}}

// {{{ nbEdge
int nbEdge (Graph * g) {
  if (g == NULL) return 0;
  if (mg(g) != NULL) return mg(g)->_nbEdge;
  if (lg(g) != NULL) return lg(g)->_nbEdge;
  return 0;
}
// }}}
// }}}

// {{{ Displaying functions
// {{{ printGraph
void printGraph (FILE *f, Graph * g, int graphviz, int *pref) {
	(*pref)++;
  if (g == NULL) return;
	if (lg(g)) l_printListGraph(f, lg(g), graphviz, *pref);
	else m_printGraph(f, mg(g), graphviz, *pref);
	// {{{ Old code
  /*  char *list = "list";
  		char *matrix = "matrix";
  		char *impl = mg(g) != NULL ? matrix : list;
  		fprintf (f,"*** %3d vertices - %3d edges *** implemetation : %s ***\n", nbVert(g), nbEdge(g), impl);
  		int i;
  		for (i = 0; i < nbVert(g); i++) {
    	int j;
    	for (j = 0; j < nbVert(g); j++) {
      int v = edgeVal(g,i,j);
      if (i == j) fprintf(f,"  +");
      else if (v == 0) fprintf(f," ..");
      else fprintf(f,"%3d", v);
    	}
    	fprintf(f,"\n");
  		}
  		fprintf(f,"*** *** *** ***\n\n");*/
	// }}}
	int i = 0;
	if (glab(g))
		for (i=0; i<nbVert(g); printf ("%2d : %2d - ", i, lab(g,i)), i++);
	if (gexc(g))
		for (i=0; i<nbVert(g); printf ("%2d : %2d - ", i, exc(g,i)), i++);
	printf("\n");
}
// }}}

// {{{ printGraphList
void printGraphList (FILE *f, Graph * g, int graphviz, int *pref) {
	(*pref)++;
  if (g == NULL) return;
  if (lg(g) != NULL) l_printListGraph(f, lg(g), graphviz, *pref);
  else {
    ; // refaire des listes avec la matrice ...
  }
}
// }}}
// }}}
