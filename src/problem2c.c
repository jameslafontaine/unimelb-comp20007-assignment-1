/*
problem2c.c

Driver function for Problem 2 Part C.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdio.h>
#include "utils.h"

int main(int argc, char **argv){
  /* Read the problem in from stdin. */
  struct graphProblem *problem = readProblem(stdin);
  /* Find the solution to the problem. */
  struct solution *solution = findSolution(problem, PART_C);

  /* Report solution */
  /* printf("Cost of installation using mixed technologies %d\n",
    solution->mixedTotal); */
  printf("%d\n", solution->mixedTotal);

  freeProblem(problem);
  freeSolution(solution);

  return 0;
}

