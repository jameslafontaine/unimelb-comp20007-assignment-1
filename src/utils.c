/*
utils.c

Implementations for helper functions to do with reading and writing.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "utils.h"

struct graphProblem {
  int antennaCost;
  int numHouses;
  int numConnections;
  struct graph *graph;
};

struct graphProblem *readProblem(FILE *file){
  int i;
  int startHouse;
  int endHouse;
  int cost;
  /* Allocate space for problem specification */
  struct graphProblem *problem = (struct graphProblem *)
    malloc(sizeof(struct graphProblem));
  assert(problem);

  /* First line of input is antenna cost. */
  assert(scanf("%d", &(problem->antennaCost)) == 1);
  /* Next line comprises number of houses and number of connections. */
  assert(scanf("%d %d", &(problem->numHouses), &(problem->numConnections))
    == 2);

  /* Build graph number of houses + 1 because of datacentre. */
  problem->graph = newGraph(problem->numHouses + 1);
  /* Add all edges to graph. */
  for(i = 0; i < problem->numConnections; i++){
    assert(scanf("%d %d %d", &startHouse, &endHouse, &cost) == 3);
    addEdge(problem->graph, startHouse, endHouse, cost);
  }

  return problem;
}

struct solution *findSolution(struct graphProblem *problem,
  enum problemPart part){
  return graphSolve(problem->graph, part, problem->antennaCost,
    problem->numHouses);
}

void freeProblem(struct graphProblem *problem){
  /* No need to free if no data allocated. */
  if(! problem){
    return;
  }
  freeGraph(problem->graph);
  free(problem);
}

void freeSolution(struct solution *solution){
  /* No need to free if no data allocated. */
  if(! solution){
    return;
  }
  free(solution);
}
