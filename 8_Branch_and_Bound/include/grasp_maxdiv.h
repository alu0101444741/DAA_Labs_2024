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
public:  
  /** 
   * @brief Constructor for the GraspMaxDiversity solver.
   * @param maximum_iterations - Number of iterations for the grasp algorithm
   * @param candidate_list_size - Size of the list of candidates (LRC)
   */
  GraspMaxDiversity(
    unsigned maximum_iterations,
    unsigned candidate_list_size
  )
  {
    algorithm_name_ = "GRASP";
    maximum_iterations_ = maximum_iterations;
    candidate_list_size_ = candidate_list_size;
    problem_ = new Problem();
  }  

  /**
   * @brief Solve the Maximum Diversity using a GRASP algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();  
};

#endif /* GREEDY_MAX_DIV_H_ */