/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 14 2024
 *
 * @brief GVNS PMSP solver class definition.
 * 
 */
#ifndef GVNS_PMSP_H_
#define GVNS_PMSP_H_

#include "grasp_pmsp.h"

/** @brief GVNS Parallel Machine Scheduling Problem solver. */
class GvnsPMSP: public PMSP {
private:
  unsigned maximum_iterations_, candidate_list_size_, k_maximum_ = 5;
  unsigned iterations_with_no_improvement_ = 5;
public:  
  /**
   * @brief Constructor for GvnsPMSP.
   * @param maximum_iterations - Number of iterations for the grasp algorithm
   * @param candidate_list_size - Size of the list of candidates (LRC)
   */
  GvnsPMSP(unsigned maximum_iterations, unsigned candidate_list_size)
  : maximum_iterations_(maximum_iterations),
    candidate_list_size_(candidate_list_size) { algorithm_name_ = "GVNS"; problem_ = new Problem(); }

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a GVNS algorithm.
   * @return A 2D vector representing the assignment of tasks to machines.
   */
  Solution Solve();

private:
  /**
   * @brief Shake the given solution to explore a set of diverse solutions.
   * @param solution The current solution to be shaken.
   * @param k The number of shaking movements to apply.
   * @return The shaken solution.
   */
  Solution Shaking(const Solution& solution, unsigned k);

  /**
   * @brief Perform Variable Neighborhood Descent (VND) local search to improve the given solution.
   * @param solution The initial solution to be improved.
   * @return The best neighbor solution found by VND.
   */
  Solution VND(const Solution& solution);
};
#endif /* GVNS_PMSP_H_ */