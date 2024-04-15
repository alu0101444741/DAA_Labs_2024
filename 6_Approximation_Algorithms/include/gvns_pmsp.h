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
   * @param maximum_iterations - number of iterations for the grasp algorithm
   * @param candidate_list_size - size of the list of candidates (LRC)
   */
  GvnsPMSP(unsigned maximum_iterations, unsigned candidate_list_size)
  : maximum_iterations_(maximum_iterations),
    candidate_list_size_(candidate_list_size) { algorithm_name_ = "GVNS"; problem_ = new Problem(); }

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a GRASP algorithm.
   * @return A 2D vector representing the assignment of tasks to machines.
   */
  Solution Solve();

private:
  Solution Shaking(const Solution& solution, unsigned k);

  Solution VND(const Solution& solution);

  Solution LocalSearch(const Solution& solution, unsigned l);
};

#endif /* GVNS_PMSP_H_ */