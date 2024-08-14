/*
problem2a.c

Driver function for Problem 2 Part A.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdio.h>
#include "utils.h"
#include "graph.h"

int main(int argc, char **argv){
  /* Read the problem in from stdin. */
  struct graphProblem *problem = readProblem(stdin);
  /* Find the solution to the problem. */
  struct solution *solution = findSolution(problem, PART_A);

  /* Report solution */
  // printf("Cost of installation using antennas %d\n", solution->antennaTotal);
  // printf("Cost of installation using cables %d\n", solution->cableTotal); 

  /* Print better choice. */
  if(solution->cableTotal < solution->antennaTotal){
    /* printf("Cheapest technology: Cabled installation cheapest\n"); */
    printf("c\n");
  } else if (solution->cableTotal == solution->antennaTotal){
    /* printf("Cheapest technology: Both technologies equal cost\n"); */
    printf("b\n");
  } else {
    /* printf("Cheapest technology: Radio-based installation cheapest\n"); */
    printf("r\n");
  }

  freeProblem(problem);
  freeSolution(solution);

  return 0;
}

