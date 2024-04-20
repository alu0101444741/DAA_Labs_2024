/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Greedy Maximum Diversity solver class definition.
 * 
 */
#ifndef GREEDY_MAX_DIV_H_
#define GREEDY_MAX_DIV_H_

#include "max_div.h"

/** @brief Greedy Parallel Machine Scheduling Problem solver. */
class GreedyMaxDiversity: public MaximumDiversity {
private:  
  bool perform_local_search_;
public:  
  /** @brief Constructor for the MGreedyMaxDiversity solver. */
  GreedyMaxDiversity(bool perform_local_search = false)
  : perform_local_search_(perform_local_search) {
    algorithm_name_ = "Greedy";
    if (perform_local_search_) algorithm_name_ += " (with local search)";
    problem_ = new Problem();
  }  

  /**
   * @brief Solve the Maximum Diversity using a greedy algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();  
};

#endif /* GREEDY_MAX_DIV_H_ */