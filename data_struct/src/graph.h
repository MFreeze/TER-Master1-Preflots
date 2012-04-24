#ifndef GRAPH_H
#define GRAPH_H 1

// {{{ Included Library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "mat_graph.h"
#include "list_graph.h"
// }}}

// {{{ Data structure
/** 
 * \brief General graph structure
 *
 * The goal of this declaration is to manipulate a single data structure no matter which
 * representation of the graph is used. To do that, we use a data structure with only two pointers
 * on a different kind of graph. Depending on the non null pointer, the graph which will be
 * contained by this structure will be a matrix-represented or a list-represented graph.
 * */
typedef struct {
  MatGraph *_mg; /*!<pointer on a matrix-represented graph */
  ListGraph *_lg;   /**<pointer on a list-represented graph */
	int *_lab;
	int *_exc;
} Graph;
// }}}

// {{{ Macros
#define mg(g) g->_mg
#define lg(g) g->_lg
#define glab(g) g->_lab
#define lab(g,i) g->_lab[i]
#define gexc(g) g->_exc
#define exc(g,i) g->_exc[i]
// }}}

// {{{ Memory management
/**
 * \brief Implements the memory allocation for a graph structure containing a matrix represented
 * graph
 *
 * \param n number of nodes in the created matrix
 * \return pointer on the created graph */ 
Graph *allocMatGraph(int n);

/**
 * \brief Implements the memory allocation for a graph structure containing a list represented
 * graph
 *
 * \param n number of nodes in the created list
 * \return pointer on the created graph*/ 
Graph *allocListGraph (int n);

/**
 * \brief Allows user to copy an empty graph, its usefull to create a new graph which 
 * have the same representation as the given one
 *
 * \param g pointer on the graph which representation will be copy
 * \return pointer on an empty graph*/
Graph *allocGraph(Graph *g);

/**
 * \brief Create graph from a file
 *
 * \param file File containing the graph description
 * \return pointer on the desired graph
 * */
Graph *createGraphFile (const char *file);

/**
 * \brief Implements memory release for a graph structure
 *
 * \param g pointer on the graph to destroy
 * */
void freeGraph(Graph *g);

/**
 * \brief Allows user to simply copy a graph
 *
 * \param g pointer on the graph to copy
 * \return pointer on the created graph
 * */
Graph *copyGraph(Graph *g);

/**
 * Fill an empty graph randomly.
 * \param g Pointer to the graph to fill.
 * \param m Number of desired edges.
 * \param cMax Maximum capacity on edges.
 * \param cMin Minimum capacity on edges.
 * \param g2 (optional) If non-NULL the second graph will be filled
 * exactely the same way as the first.
 */
void randFill(Graph *g, int m, int cMax, int cMin, Graph *g2);
/**
 * Just a fixed graph for testing algo.
 */
void testFill(Graph *g);

// }}}


/**                              *
 * Interface of Graph structure  *
 *********************************/

// {{{ Graph information functions
/** 
 * \brief Allows users to easily get the value of the edge between i and j
 *
 * \param g pointer on the graph which contains the edge
 * \param i first extremity of the edge
 * \param j second extremity
 * \return value of the edge (i,j)
 * */
int edgeVal(Graph *g, int i, int j);
/**
 * \brief Allows user to modify the value of the edge (i,j)
 *
 * \param g pointer on the graph containing (i,j)
 * \param i first extremity of (i,j)
 * \param j second extremity of (i,j)
 * \param val new capacity of (i,j)
 * */
void setEdge(Graph *g, int i, int j, int val);

/**
 * Returns the number of vertices of a Graph
 */
int nbVert (Graph *g);
/**
 * Returns the number of edges of a Graph.
 */
int nbEdge (Graph * g);

/**
 * \brief allows user to get the incoming neighbourhood of node k
 *
 * \param g pointer on the graph containing k
 * \param k node for which the neighbourhood is desired
 * \return pointer on the requested neighbourhood
 * */
List *inNeighb(Graph *g, int k);
/**
 * \brief allows user to get the outcoming neighbourhood of node k
 *
 * \param g pointer on the graph containing k
 * \param k node for which the neighbourhood is desired
 * \return pointer on the requested neighbourhood
 * */
List *outNeighb(Graph *g, int k);
// }}}

// {{{ Print functions
/**
 * Print a Graph in as a matrix.
 * This will produce the same result with a matrix or list Graph
 */
void printGraph (FILE *f, Graph * g, int graphviz, int *pref);

/**
 * Print a Graph in as an adjacency list.
 * This will produce the same result with a matrix or list Graph
 */
void printGraphList (FILE *f, Graph * g, int graphviz, int *pref);
// }}}

#endif /* GRAPH_H */
