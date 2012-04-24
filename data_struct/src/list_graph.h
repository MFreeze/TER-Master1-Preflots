#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H 1

#include "list.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


// {{{ Structure
/**
 * \brief Implementation of a graph data strucuture represented by incidence list
 * */
typedef struct {
  List **_inNeighb; /*!<Represents incoming neighbourhood */
  List **_outNeighb; /*!<Represents outgoing neighbourhood */
  int _nbVert; /*!<Stores the number of nodes in the graph */
  int _nbEdge; /*!<Stores the number of edges in the graph */
} ListGraph;
// }}}

// {{{ Graph informations
/**
 * \brief Allows users to know value of the edge between i and j
 * \param g pointer on the graph which is supposed to contain the edge
 * \param i a node
 * \param j another node
 * \return value of the edge, 0 if it doesn't exist*/
int l_edgeVal(ListGraph *lg, int i, int j);
/**
 * \brief Allows user to change the value of the edge between i and j
 * \param g pointer on the graph which is supposed to contain the edge
 * \param i a node
 * \param j another node
 * \param val new value of the edge
 * */
void l_setEdge(ListGraph *lg, int i, int j, int val);

/**
 * \brief Allows user to get incoming neighbourhood of the selected node
 * \param g pointer on the graph which is supposed to contain the edge
 * \param k node for which the incoming neighbourhood is desired
 * \return pointer on the desired Neghibourhood if exists, NULL else*/
List *l_inNeighb(ListGraph *lg, int k);
/**
 * \brief Allows user to get outgoing neighbourhood of the selected node
 * \param g pointer on the graph which is supposed to contain the edge
 * \param k node for which the outgoing neighbourhood is desired
 * \return pointer on the desired Neghibourhood if exists, NULL else*/
List *l_outNeighb(ListGraph *lg, int k);
// }}}

// {{{ Memory management
/**
 * \brief Allows the user to copy a list-represented graph
 * \param g pointer on the graph which will be copied
 * \return pointer on the created graph
 * */
ListGraph *l_copyGraph(ListGraph *lg);
/**
 * \brief Implements memory allocation for a list represented graph with n nodes
 * \param n number of nodes in the graph
 * \return a pointer on allocated memory space*/
ListGraph *l_allocGraph(int n);
/**
 * \brief Implements the memory release of a list represented graph structure
 * \param g pointer on the graph to destroy*/
void l_freeGraph (ListGraph *lg);
// }}}

// {{{ Display functions
/**
 * \brief Allows users to print on given stream
 * \param g the graph to print */
void l_printListGraph (FILE *f, ListGraph *lg, int graphviz, int pref);
// }}}

#endif /* LIST_GRAPH_H */
