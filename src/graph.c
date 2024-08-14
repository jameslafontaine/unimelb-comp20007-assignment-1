/*
graph.c

Set of vertices and edges implementation.

Implementations for helper functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "graph.h"
#include "utils.h"
#include "pq.h"

#define INITIALEDGES 32
#define MAXNUMVERTICES 20
#define MAXNUMEDGES 50

struct edge;

/* Definition of a graph. */
struct graph {
  int numVertices;
  int numEdges;
  int allocedEdges;
  struct edge **edgeList;
};

/* Definition of an edge. */
struct edge {
  int start;
  int end;
  int cost;
};

struct graph *newGraph(int numVertices){
  struct graph *g = (struct graph *) malloc(sizeof(struct graph));
  assert(g);
  /* Initialise edges. */
  g->numVertices = numVertices;
  g->numEdges = 0;
  g->allocedEdges = 0;
  g->edgeList = NULL;
  return g;
}

/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end, int cost){
  assert(g);
  struct edge *newEdge = NULL;
  /* Check we have enough space for the new edge. */
  if((g->numEdges + 1) > g->allocedEdges){
    if(g->allocedEdges == 0){
      g->allocedEdges = INITIALEDGES;
    } else {
      (g->allocedEdges) *= 2;
    }
    g->edgeList = (struct edge **) realloc(g->edgeList,
      sizeof(struct edge *) * g->allocedEdges);
    assert(g->edgeList);
  }

  /* Create the edge */
  newEdge = (struct edge *) malloc(sizeof(struct edge));
  assert(newEdge);
  newEdge->start = start;
  newEdge->end = end;
  newEdge->cost = cost;

  /* Add the edge to the list of edges. */
  g->edgeList[g->numEdges] = newEdge;
  (g->numEdges)++;
}

/* Frees all memory used by graph. */
void freeGraph(struct graph *g){
  int i;
  for(i = 0; i < g->numEdges; i++){
    free((g->edgeList)[i]);
  }
  if(g->edgeList){
    free(g->edgeList);
  }
  free(g);
}

struct solution *graphSolve(struct graph *g, enum problemPart part,
  int antennaCost, int numHouses){
  int cost[MAXNUMVERTICES];	
  int vertices[MAXNUMVERTICES];
  int i;
	
  struct solution *solution = (struct solution *)
    malloc(sizeof(struct solution));
  assert(solution);
  if(part == PART_A){
    /* IMPLEMENT 2A SOLUTION HERE */
    solution->antennaTotal = antennaCost * numHouses;
    solution->cableTotal = 0;
    
    /* perform a form of Prim's Algorithm on the graph to find the minimum 
    spanning tree total cost and thus the solution to the cableTotal */
    
    /* initialise costs to infinity (MAX_INT in C) */
    for (i=0; i < numHouses + 1; i++){
      cost[i] = INT_MAX;
    }
    /* initialise array containing vertex values */
    for (i=0; i < numHouses + 1; i++){
      vertices[i] = i;
    }
    cost[0] = 0;
    
    /* initialise priority queue */
    struct pq *pq = newPQ();
    for (i=0; i < numHouses + 1; i++){  
      enqueue(pq, (void*)&(vertices[i]), cost[i]);
    } 
    
    while (!empty(pq)){
      int u = *(int*)deletemin(pq);
      solution->cableTotal += cost[u];
      /* for each (u,w) contained in edgeList, check if w is still in the 
      priority queue and if the weight(u, w) < cost[w] */
      for (i=0; i < g->numEdges; i++){
        if ((g->edgeList)[i]->start == u){
          int w = (g->edgeList)[i]->end;
    	  if (isinPQ(pq, &w) && (g->edgeList)[i]->cost < cost[w]){
    	    cost[w] = (g->edgeList)[i]->cost;
    	    updatePQ(pq, &w, cost[w]);
          }
        /* check the other direction as this is an undirected graph */
        } else if ((g->edgeList)[i]->end == u){
          int w = (g->edgeList)[i]->start;
    	  if (isinPQ(pq, &w) && (g->edgeList)[i]->cost < cost[w]){
    	    cost[w] = (g->edgeList)[i]->cost;
    	    updatePQ(pq, &w, cost[w]);
          }
        }
      }
    }
  } else {
    /* IMPLEMENT 2C SOLUTION HERE */
    
    /* can utilise the exact same algorithm as in part 2a with the only
    difference being that we set the inital costs of all vertices to the 
    antenna cost as we can now choose to use an antenna when a cable connection
    would be more expensive */
    solution->mixedTotal = 0;
    
    /* initialise costs to antennaCost */
    for (i=0; i < numHouses + 1; i++){
      cost[i] = antennaCost;
    }
    /* initialise array containing vertex values */
    for (i=0; i < numHouses + 1; i++){
      vertices[i] = i;
    }
    cost[0] = 0;
    
    /* initialise priority queue */
    struct pq *pq = newPQ();
    for (i=0; i < numHouses + 1; i++){  
      enqueue(pq, (void*)&(vertices[i]), cost[i]);
    } 
    
    while (!empty(pq)){
      int u = *(int*)deletemin(pq);
      solution->mixedTotal += cost[u];
      /* for each (u,w) contained in edgeList, check if w is still in the 
      priority queue and if the weight(u, w) < cost[w] */
      for (i=0; i < g->numEdges; i++){
        if ((g->edgeList)[i]->start == u){
          int w = (g->edgeList)[i]->end;
    	  if (isinPQ(pq, &w) && (g->edgeList)[i]->cost < cost[w]){
    	    cost[w] = (g->edgeList)[i]->cost;
    	    updatePQ(pq, &w, cost[w]);
          }
        /* check the other direction as this is an undirected graph */
        } else if ((g->edgeList)[i]->end == u){
          int w = (g->edgeList)[i]->start;
    	  if (isinPQ(pq, &w) && (g->edgeList)[i]->cost < cost[w]){
    	    cost[w] = (g->edgeList)[i]->cost;
    	    updatePQ(pq, &w, cost[w]);
          }
        }
      }
    }
  }
  return solution;
}

