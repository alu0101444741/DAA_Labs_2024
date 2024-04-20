/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief GRASP Maximum Diversity solver class definition.
 * 
 */
#ifndef GRASP_MAX_DIV_H_
#define GRASP_MAX_DIV_H_

#include "max_div.h"

/** @brief GRASP Maximum Diversity Problem solver. */
class GraspMaxDiversity: public MaximumDiversity {
private:
  unsigned maximum_iterations_, candidate_list_size_;
  bool perform_local_search_;
public:  
  /** 
   * @brief Constructor for the MGreedyMaxDiversity solver.
   * @param maximum_iterations - Number of iterations for the grasp algorithm
   * @param candidate_list_size - Size of the list of candidates (LRC)
   * @param perform_local_search - Will not perform any local search if set to 'false'
   */
  GraspMaxDiversity(unsigned maximum_iterations, unsigned candidate_list_size, bool perform_local_search = false)
  : maximum_iterations_(maximum_iterations), candidate_list_size_(candidate_list_size),
    perform_local_search_(perform_local_search)
  {
    algorithm_name_ = "GRASP";
    //if (perform_local_search_) algorithm_name_ += " (with local search)";
    problem_ = new Problem();
  }  

  /**
   * @brief Solve the Maximum Diversity using a GRASP algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();  
};

#endif /* GREEDY_MAX_DIV_H_ */