/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief Tabu search Maximum Diversity solver class definition.
 * 
 */
#ifndef TABU_MAX_DIV_H_
#define TABU_MAX_DIV_H_

#include "max_div.h"

/** @brief Tabu Search Maximum Diversity Problem solver. */
class TabuMaxDiversity: public MaximumDiversity {
private:
  bool perform_local_search_;
public:  
  /** 
   * @brief Constructor for the TabuMaxDiversity solver.
   * @param maximum_iterations - Number of iterations for the grasp algorithm
   * @param candidate_list_size - Size of the list of candidates (LRC)
   * @param perform_local_search - Will not perform any local search if set to 'false'
   */
  TabuMaxDiversity(
    unsigned maximum_iterations,
    unsigned candidate_list_size,
    bool perform_local_search = false
  ) : perform_local_search_(perform_local_search)
  {
    algorithm_name_ = "TabuSearch";
    maximum_iterations_ = maximum_iterations;
    candidate_list_size_ = candidate_list_size;
    problem_ = new Problem();
  }  

  /**
   * @brief Solve the Maximum Diversity using a Tabu Search algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();  
};

#endif /* TABU_MAX_DIV_H_ */