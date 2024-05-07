/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Greedy Maximum Diversity solver class implementation.
 * 
 */

#include "greedy_maxdiv.h"

/**
 * @brief Solve the Maximum Diversity using a greedy algorithm.
 * @return Solution representing a set of k-dimensional elements.
 */
Solution GreedyMaxDiversity::Solve() {
  Solution solution(problem_);
  vector<unsigned> remaining_elements = GetElementIndexes(problem_->GetElements());   
  Element current_center = CalculateGravityCenter(remaining_elements);

  while (solution.GetSolutionSize() < m_value_) {

    unsigned furthest_element = GetFurthestElement(remaining_elements, current_center);
    
    solution.AddElement(furthest_element);

    EraseElement(remaining_elements, furthest_element);

    current_center = CalculateGravityCenter(solution.GetElements());
  }
  //solution.UpdateDiversity();
  if (perform_local_search_) return LocalSearch(solution);
  return solution;
}