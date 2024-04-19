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
public:  
  /** @brief Constructor for the MGreedyMaxDiversity solver. */
  GreedyMaxDiversity() { algorithm_name_ = "Greedy"; problem_ = new Problem(); }  

  /**
   * @brief Solve the Maximum Diversity using a greedy algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();  
};

#endif /* GREEDY_MAX_DIV_H_ */