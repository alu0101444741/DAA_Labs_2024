/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief GRASP Maximum Diversity solver class implementation.
 * 
 */

#include "grasp_maxdiv.h"

/**
 * @brief Solve the Maximum Diversity using a GRASP algorithm.
 * @return Solution representing a set of k-dimensional elements.
 */
Solution GraspMaxDiversity::Solve() {
  Solution best_solution(problem_);
  Solution current_solution(problem_);  

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++ iteration) {

    current_solution = ConstructInitialSolution(candidate_list_size_);

    current_solution = LocalSearch(current_solution);
    
    if (current_solution.GetDiversity() > best_solution.GetDiversity()) {
      best_solution = current_solution;
    }
  }
  return best_solution;
}