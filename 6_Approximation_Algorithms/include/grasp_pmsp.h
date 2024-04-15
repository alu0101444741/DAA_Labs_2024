/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief GRASP PMSP solver class definition.
 * 
 */
#ifndef GRASP_PMSP_H_
#define GRASP_PMSP_H_

#include "pmsp.h"
#include "local_search.h"

/** @brief GRASP Parallel Machine Scheduling Problem solver. */
class GraspPMSP: public PMSP {
private:
  unsigned maximum_iterations_, candidate_list_size_;
  bool perform_local_search_;
  unsigned iterations_with_no_improvement_ = 5;
public:  
  /**
   * @brief Constructor for GraspPMSP.
   * @param maximum_iterations - number of iterations for the grasp algorithm
   * @param candidate_list_size - size of the list of candidates (LRC)
   * @param perform_local_search - won't perform any local search if set to 'false'
   */
  GraspPMSP(unsigned maximum_iterations , unsigned candidate_list_size, bool perform_local_search)
  : maximum_iterations_(maximum_iterations),
    candidate_list_size_(candidate_list_size),
    perform_local_search_(perform_local_search) { algorithm_name_ = "GRASP"; problem_ = new Problem(); }

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a GRASP algorithm.
   * @return A 2D vector representing the assignment of tasks to machines.
   */
  Solution Solve();
};

#endif /* GRASP_PMSP_H_ */