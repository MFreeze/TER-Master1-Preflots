#ifndef ALGO_H
#define ALGO_H

#include <string.h>
#include "graph.h"
#include "heap.h"


// {{{ Dinic set of function
/**
 * \brief Generates the difference graph from the flow graph and capacity graph
 * \todo documentation
 */
Graph *diffGraph(Graph *capa, Graph *flow);

/**
 * \brief Returns a shortest path from s to p if exists one or NULL
 * \param g Pointer on a Graph.
 * \param s The source vertex of the graph.
 * \param p The sink vertex of the graph.
 * \return A shortest path from s to p. The first value does NOT reprensent an edge, 
 * and is set to the min flow of the path.
 */
List *shortPath(Graph *g, int s, int p);
Graph *setShortPath(Graph *g, int s, int p);

/**
 * \brief Creation of the layer graph from the differencial graph
 * \param diff differential graph
 * \param s vertex that represents first layer of the layer graph (for d=0)
 * \return the layer graph*/
Graph *updateLayGraph(Graph *diff, int s);

/**
 * \brief Implements the update of the layer graph after the saturation of
 * the edge with the lowest residual capacity
 * \param layer pointer on the layer graph
 * \param path pointer on the way which has lead to the update */
void addPathToLayer(Graph *layer, List *path);

/**
 * \brief Implements the research of the maximal flow in a layer graph and updates
 * the associated flowgraph
 * \param layer pointer on the layer graph
 * \param flow point on the flowgraph
 * \param s source vertex
 * \param p well vertex
 * \return flow increase */
int layerGraphFlow(Graph *layer, Graph *flow, int s, int p);

/**
 * \brief Implementation of the Dinic (Dinitz) algorithm which uses layer graph to 
 * accelerate the determination of flow
 * \param capa pointer on the graph on which we're searching flow
 * \param flow pointer on the network flow
 * \param s source vertex
 * \param p well vertex
 * \return maximal flow*/
int algoDinic(Graph *capa, Graph *flow, int s, int p);
// }}}

// {{{ Edmond Karp set of function
/**
 * \brief Add a path in a flow graph.
 * \param flow Pointer on a flow graph.
 * \param path Path to add.
 */
void addPathToFlow(Graph *flow, List *path);

/** 
 * \brief Add a path to a difference graph.
 * \param diff Pointer on a difference graph.
 * \param path Pointer on a path.
 */
void addPathToDiff(Graph *diff, List *path);

/** 
 * \brief Implements the Edmonds-Karps alogrithm.
 * \param capa A capacity graph (assumed to be coherent).
 * \param diff A difference graph (assumed to be initialized with capacity graph).
 * \param flow A flow graph (assumed to be empty).
 * \return The maxmum flow.
 */
int algoEdmondKarp(Graph *capa, Graph *diff, Graph *flow, int s, int p);
// }}}

// {{{ Preflow set of functions
/**
 * \brief Compute the distance of each node to the sink 
 * \param g Graph on which the computation will be done
 * \param p Sink node of the graph
 * */
void compLabel (Graph *g, int p);

/**
 * \brief Push preflow on the edge (i,j)
 * \param flow Preflow graph
 * \param diff Residual Network
 * \param i node 
 * \param j node
 * \param s source node
 * \param p sink node
 * \return The amount of pushed preflow */
int push (Graph *flow, Graph *diff, int i, int j, int s, int p);

/**
 * \brief Relabel an active node
 * \param diff A difference graph
 * \param k Node to relabel
 * */
void relabel (Graph *diff, int p);

/**
 * \brief Implements the FIFO variant of preflow-push algorithm
 * \param capa A capacity graph
 * \param diff A difference graph (assumed to be initialized with capacity graph
 * \param flow A preflow graph (assumed to be empty)
 * \param s The source node
 * \param p The sink node
 * \return Maximum flow value */
int algoFIFO (Graph *capa, Graph *diff, Graph *flow, int s, int p);

/**
 * \brief Implements the High-Label variant of preflow-push algorithm
 * \param capa A capacity graph
 * \param diff A difference graph (assumed to be initialized with capacity graph
 * \param flow A preflow graph (assumed to be empty)
 * \param s The source node
 * \param p The sink node
 * \return Maximum flow value */
int algoLabel (Graph *capa, Graph *diff, Graph *flow, int s, int p);
// }}}
#endif /* ALGO_H */
