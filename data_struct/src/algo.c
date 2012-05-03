#include "algo.h"

// {{{ Dinic set of functions
// {{{ Creation of a differential graph
Graph * diffGraph(Graph *capa, Graph *flow) {
  if (nbVert(capa) == 0 || nbVert(flow) != nbVert(capa)) return NULL;
  Graph *diff = copyGraph(capa);
  int i,j,c,f; for (i = 0; i < nbVert(capa); i++) {
    List *out = outNeighb(flow, i);
    Item *it = begin(out);
    while (it != NULL) {
      j = num(it);
      f = val(it);
      c = edgeVal(capa, i,j);
      setEdge(diff, i,j, c-f);
      setEdge(diff, j,i, f);
      it = next(it);
    }
    freeList(out);
  }
  return diff;
}
// }}}

// {{{Creation of a layer graph
/* Create a new layer graph */
Graph *updateLayGraph(Graph *diff, int s) {
	int n = nbVert(diff), k=s;
	int *visited = (int *) calloc (n, sizeof(int));
	int *order = (int *) calloc (n, sizeof(int));
	Graph *layer = allocGraph(diff);
	List *to_process = allocList();
	visited[s] = 1;
	pushTail(to_process, s, 1);
	/* Breadth-first traversal of the graph */
	while (nb(to_process)) {
		k = num(begin(to_process));
		List *out = outNeighb(diff, k);
		Item *it = begin(out);
		while (it) {
			/* If vertex isn't already visited, add it to the layer graph in the layer order[k]+1 */
			if (!visited[num(it)]) {
				pushTail(to_process, num(it), val(it));
				order[num(it)] = order[k] + 1;
				visited[num(it)] = 1;
				setEdge (layer, k, num(it), val(it));
			}
			/* If vertex is already visited, check if the new order of the vertex is the same
			 * as previously */
			else if (order[k] == order[num(it)] - 1)
				setEdge (layer, k, num(it), val(it));
			it = next(it);
		}
		freeList(out);
		popHead(to_process);
	}
	freeList(to_process);
	free(order); free(visited);
	return layer;
}
// }}}

// {{{ Update of a layer graph
void addPathToLayer(Graph *layer, List *path) {
  Item *it = begin(path);
  if (it) {
		int pval = val(it); int gval;
		while (next(it)) {
			gval = edgeVal(layer, num(it), num(next(it)));
			setEdge (layer, num(it), num(next(it)), (gval - pval) < 0 ? 0 : gval - pval);
			it = next(it);
		}
  }
}
// }}}

// {{{ Max Flow in a Layer Graph
/* Find the max flow in a layer graph */
int layerGraphFlow(Graph *layer, Graph *flow, int s, int p) {
	/* Search for the set of the shortest paths, if there is no path return 0 */
	Graph *setofpath = setShortPath(layer, s, p);
	if (!setofpath)
		return 0;
	int inc_flow = 0;

	List *pa = shortPath (setofpath, s, p);
	while (pa) {
		inc_flow += val(begin(pa));
		addPathToDiff (setofpath, pa);
		addPathToFlow (flow, pa);
		freeList (pa);
		pa = shortPath (setofpath, s, p);
	}

	freeGraph(setofpath);
	return inc_flow;
}
// }}}

// {{{ Shortest path in edge
List *shortPath(Graph *g, int s, int p) {
	if (!g) return NULL;
  int n = nbVert(g), k = s;
	int *visited = (int *) calloc (n, sizeof(int));
  Graph *tree = allocListGraph(n);
  List *to_process = allocList();
	/* Initialisation */
	visited[s] = 1; 
  pushTail(to_process, s, 1);
  while (nb(to_process)  && !visited[p]) {
    k = num(begin(to_process));
    List *out = outNeighb(g, k);
    Item * it = begin(out);
    while (it != NULL) {
      if (!visited[num(it)]) {
        setEdge(tree, k, num(it), val(it));
        visited[num(it)]++; 
        pushTail(to_process, num(it), val(it));
      }
      it = next(it);
    }
    freeList(out);
    popHead(to_process);
  }
  freeList(to_process);
  if (!visited[p]){
		free(visited); freeGraph(tree);
    return NULL;
	}

  List *path = allocList();
  int min = -1;
  k = p; while (k != s) {
    List *in = inNeighb (tree, k);
    Item *it = begin(in);
    pushHead(path, k, val(it));
    if (min == -1 || val(it) < min) min = val(it);
    k = num(it);
    freeList(in);
  }
	free(visited); freeGraph (tree); 
  pushHead(path, s, min);
  return path;
}
// }}}

// {{{ Set of shortest path in a graph
Graph *setShortPath(Graph *g, int s, int p) {
	int n = nbVert(g), k=0; 
	int *visited = (int *) calloc (n, sizeof(int)), *order = (int *) calloc (n, sizeof(n));
	List *to_process = allocList();
	Graph *tree = allocGraph (g);	
	pushTail (to_process, s, 1);
	visited[s] = 1;
	while (nb(to_process)) {
		k = num(begin(to_process));
		List *out = outNeighb(g,k);
		Item *it = begin(out);
		/* Breadth-first traversal from s to p */
		while (it) {
			if (!visited[num(it)]) {
				visited[num(it)] = 1; order[num(it)] = order[k] + 1;
				pushTail(to_process, num(it), val(it));
				setEdge(tree, k, num(it), val(it));
			}
			else if (order[num(it)] == order[k] + 1) 
				setEdge(tree, k, num(it), val(it));
			it = next(it);
		}
		freeList(out);
		popHead(to_process);
	}
	freeList(to_process);
	/* If no path return NULL */
	if (!visited[p]) {
		freeGraph(tree);
		free(visited); free(order);
		return NULL;
	}

	/* Graph Pruning */
	to_process = allocList();
	pushTail (to_process, p, 1);

	while (nb(to_process)) {
		k = num(begin(to_process));
		List *in = inNeighb(tree, k);
		Item *it = begin(in);
		while (it) {
			if (order[num(it)]) {
				pushTail(to_process, num(it), 1);
				order[num(it)] = 0;
			}
			it = next(it);
		}
		freeList(in);
		popHead(to_process);
	}
	freeList(to_process);
	int ref=order[p];
	while (--ref) {
		int i=0; for (i=0; i<n; i++) {
			if (order[i])
				if (order[i] == ref) {
					List *in = inNeighb(tree, i);
					Item *it = begin(in);
					while (it) {
						setEdge (tree, num(it), i, 0);
						it = next(it);
					}
					freeList(in);
				}
		}
	}
	free(order); free(visited);
	return tree;
}
// }}}

// {{{ Dinic algorithm
int algoDinic(Graph *capa, Graph *flow, int s, int p) {
	int max_flow = 0, inc_flow = 0;;
	do {
		Graph *diff = diffGraph(capa, flow);
		Graph *layer = updateLayGraph(diff, s);
		inc_flow = layerGraphFlow(layer, flow, s, p);
		max_flow += inc_flow;
		freeGraph(layer);
		freeGraph(diff);
	} while (inc_flow);

	return max_flow;
}
// }}}
// }}}

void addSeg(Graph *g, int i, int j, int val, int diff) {
	int pval = val, gval = edgeVal (g, i, j), gval2 = edgeVal(g, j, i);
	if (!diff) {
		if (gval2) {
			int sub = gval2 - pval;
			if (sub > 0)
				setEdge (g, j, i, sub);
			else {
				setEdge (g, j, i, 0);
				setEdge (g, i, j, -sub);
			}
		}
		else
			setEdge (g, i, j, gval + pval);
	}
	else {
		setEdge (g, i, j, gval - pval);
		setEdge (g, j, i, gval2 + pval);
	}
}

inline void addSegToFlow(Graph *g, int i, int j, int val) {
	addSeg(g,i,j,val,0);
}

inline void addSegToDiff(Graph *g, int i, int j, int val) {
	addSeg(g,i,j,val,1);
}

// {{{ Edmonds Karp set of functions
// {{{ Add a path to a graph
void addPath(Graph *g, List *path, int diff) {
  Item *it = begin(path);
  int pval = val(it); int gval;
  while (next(it) != NULL) {
    gval = edgeVal(g, num(it), num(next(it)));
    if (!diff) {
			int gval2 = edgeVal (g, num(next(it)), num(it));
			if (gval2) {
				int sub = gval2-pval;
				if (sub > 0)
					setEdge (g, num(next(it)), num(it), sub);
				else {
					setEdge (g, num(next(it)), num(it), 0);
					setEdge (g, num(it), num(next(it)), -sub);
				}
			}
			else
				setEdge (g, num(it), num(next(it)), gval + pval);
		}
    else {
      int gval2 = edgeVal(g, num(next(it)), num(it));
      setEdge (g, num(it), num(next(it)), gval - pval);
      setEdge (g, num(next(it)), num(it), gval2 + pval);
    }
    it = next(it);
  }
}
// }}}

// {{{ Add a path to flow graph
void addPathToFlow(Graph *flow, List *path) {
  addPath(flow, path, 0);
}
// }}}

// {{{ Add a path to a differential graph
void addPathToDiff(Graph *diff, List *path) {
  addPath(diff, path, 1);
}
// }}}

// {{{ Edmond Karp algorithm
int algoEdmondKarp(Graph *capa, Graph *diff, Graph *flow, int s, int p) {
  List *path = shortPath (diff, s, p);
  while (path != NULL) {
    /*printList(stdout, path);*/
    addPathToDiff(diff, path);
    addPathToFlow(flow, path);
    freeList(path);
    path = shortPath (diff, s, p);
  }
  List *l = outNeighb(flow, s);
  int f = 0;
  Item *it = begin(l);
  while(it != NULL) { f += val(it); it = next(it); }
  freeList(l);
  return f;
}
// }}}
// }}}

// {{{ Preflow set of functions
// {{{ compLabel
void compLabel (Graph *g, int p) {
	List *to_process  = allocList ();
	int n = nbVert (g), k = p;
	int *visited = (int *) calloc (n, sizeof(int));

	if (!visited) {
		fprintf (stderr, "calloc compLabel");
		return;
	}

	lab(g,p)=0;
	visited[p]++;
	pushTail (to_process, p, 0);
	while (nb(to_process)) {
		k = num(begin(to_process));
		lab(g,k) = val(begin(to_process));
		List *in = inNeighb (g, k);
	//	List *in = g->_lg->_inNeighb[k];
		Item *it = begin(in);
		while (it) {
			if (!visited[num(it)]) {
				visited[num(it)] ++;
				pushTail (to_process, num(it), val(begin(to_process))+1);
			}
			it = next(it);
		}
		freeList(in);
		popHead (to_process);
	}
	freeList(to_process);
	free (visited);
}
// }}}

// {{{ push_relab
void fifo_push_relab (Graph *flow, Graph *diff, List *excess, int s, int p) {
	int k = num(begin(excess));
	List *out = outNeighb(diff, k);
	Item *it = begin(out);
	int M= 2*nbVert(diff);
	while (it) {
		int i = num(it);
		if (lab(diff, k) == lab(diff, i) + 1) {
			int val = edgeVal(diff, k, i);
			int min = val < exc(diff, k) ? val : exc(diff, k);
			addSegToDiff(diff, k, i, min);
			addSegToFlow(flow, k, i, min);
			if (exc(diff,i) == 0 && i != s && i!= p)
				pushTail(excess, i, 0);
			exc(diff, i) += min;
			exc(diff, k) -= min;
		}
		else if (lab(diff, i) >= lab(diff, k))
			M = lab(diff, i) < M ? lab(diff, i) : M;
		it = next(it);
	}
	if (exc(diff, k) > 0)
		lab(diff, k) = M;

	popHead(excess);
	freeList(out);
}
// }}}

// {{{ push_relab
void hl_push_relab (Graph *flow, Graph *diff, Heap *excess, int s, int p) {
	int k = h_remNode(excess);
	List *out = outNeighb(diff, k);
	Item *it = begin(out);
	int M= 2*nbVert(diff);
	while (it) {
		int i = num(it);
		if (lab(diff, k) == lab(diff, i) + 1) {
			int val = edgeVal(diff, k, i);
			int min = val < exc(diff, k) ? val : exc(diff, k);
			addSegToDiff(diff, k, i, min);
			addSegToFlow(flow, k, i, min);
			if (exc(diff,i) == 0 && i != s && i!= p)
				h_insertNode(excess, i);
			exc(diff, i) += min;
			exc(diff, k) -= min;
		}
		else if (lab(diff, i) >= lab(diff, k))
			M = lab(diff, i) < M ? lab(diff, i) : M;
		it = next(it);
	}
	if (exc(diff, k) > 0)
		lab(diff, k) = M;

	freeList(out);
}
// }}}

// {{{ algoFIFO 
int algoFIFO (Graph *capa, Graph *diff, Graph *flow, int s, int p) {
	int i = 0;
	// Initialization
	compLabel (diff, p);

	for (i=0; i< nbVert(diff); i++) 
		if (i!=p && !lab(diff,i))
			lab(diff,i) = -1;

	if (lab(diff,s) == -1)
		return 0;

	memset(gexc(diff), 0, nbVert(diff) * sizeof(int));
	List *excess_node = allocList();
	List *out = outNeighb(diff, s);
	//List *out = diff->_lg->_outNeighb[s];

	Item *it = begin(out);
	while (it != NULL) {
		int j = num(it);
		int delta = edgeVal(diff, s, j);
		addSegToFlow(flow, s, j, delta);
		addSegToDiff(diff, s, j, delta);
		if (j != s && j!= p)
			pushTail(excess_node, j, 0);
		exc(diff,j)+=delta;
		it = next(it);
	}
	freeList (out);

	lab(diff,s) = nbVert(diff);

	// Algorithm
	while (nb(excess_node)) 
		fifo_push_relab (flow, diff, excess_node, s, p);
	freeList (excess_node);
	return exc(diff,p);
}
// }}}

// {{{ algoLabel
int algoLabel (Graph *capa, Graph *diff, Graph *flow, int s, int p) {
	int i = 0;
	// Initialization
	compLabel (diff, p);

	for (i=0; i< nbVert(diff); i++) 
		if (i!=p && !lab(diff,i))
			lab(diff,i) = -1;

	if (lab(diff,s) == -1)
		return 0;

	memset(gexc(diff), 0, nbVert(diff) * sizeof(int));
	Heap *excess_node = allocHeap(nbVert(capa), glab(capa));
	List *out = outNeighb(diff, s);
	//List *out = diff->_lg->_outNeighb[s];
	
	Item *it = begin(out);
	while (it != NULL) {
		int j = num(it);
		int delta = edgeVal(diff, s, j);
		addSegToFlow(flow, s, j, delta);
		addSegToDiff(diff, s, j, delta);
		if (j != s && j!= p)
			h_insertNode(excess_node, j);
		exc(diff,j)+=delta;
		it = next(it);
	}
	freeList (out);

	lab(diff,s) = nbVert(diff);

	// Algorithm
	while (cur(excess_node)) 
		hl_push_relab (flow, diff, excess_node, s, p);

	freeHeap (excess_node);
	return exc(diff,p);
}
// }}}

// }}}
