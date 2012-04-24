#ifndef MAT_GRAPH_H
#define MAT_GRAPH_H 1

#include "list.h"
#include <stdlib.h>
 
// {{{ Structures
/**
 * \brief Implementation of a graph with help of an incidence matrix */
typedef struct {
    int ** _mat; /*!<Matrix containing value of edges of the graph */
    int _nbVert; /*!<Integer containing the number of nodes in the graph */
    int _nbEdge; /*!<Integer containing the number of edges in the graph*/
} MatGraph;
// }}}

// Graph Informations
/** 
 * \brief Allows user to get value of the edge between i and j
 * \param g pointer on a matrix-represented graph
 * \param i a node
 * \param j the other node
 * \return value of the (i,j) server
 * */
int  m_edgeVal(MatGraph *mg, int i, int j);
/**
 * \brief Allows user to change the value of the edge (i,j)
 * \param g pointer on a matrix-represented graph
 * \param i one of the extremity of the edge
 * \param j the other extremity of the edge 
 * */
void m_setEdge(MatGraph *mg, int i, int j, int val);

/**
 * \brief Allows user to get a copy of incoming neighbourhooh of a node
 * \param g pointer on the graph which is supposed to contain the desired node
 * \param k node for which the neighbourhood is asked
 * \return desired neighbourhood*/
List *m_inNeighb(MatGraph *mg, int k);
/**
 * \brief Allows user to get a copy of outgoing neighbourhooh of a node
 * \param g pointer on the graph which is supposed to contain the desired node
 * \param k node for which the neighbourhood is asked
 * \return desired neighbourhood*/
List * m_outNeighb(MatGraph *mg, int k);
// }}}

// {{{ Memory management
/**
 * \brief Allows user to create a new copy of desired matrix represented graph
 * \param g pointer on the matrix represented graph to copy
 * \return pointer on the new copy of graph*/
MatGraph * m_copyGraph(MatGraph *mg);
/**
 * \brief Implements memory allocation for a matrix-represented graph
 * \param n stands for the number of nodes which will be included in the graph
 * \return pointer on the new matrix-represented graph*/
MatGraph * m_allocGraph(int n);
/**
 * \brief Implements the memory release of a matrix-represented graph
 * \param g pointer on the graph to destroy*/
void m_freeGraph(MatGraph *mg);
// }}}

// {{{ Display Functions
/**
 * \brief Print a representation of the graph
 * \param stream Stream on which the graph will be displayed
 * \param g stands for the graph to display*/
void m_printGraph(FILE* stream, MatGraph *mg, int graphviz, int pref);
// }}}

#endif /* MAT_GRAPH_H */
