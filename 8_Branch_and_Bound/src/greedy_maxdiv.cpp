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
  vector<Element> remaining_elements = problem_->GetElements();
  Solution solution(problem_);  
  Element current_center;
  //cout << "Going into loop...\n";
  while (solution.GetSolutionSize() < m_value_) {
    current_center = CalculateGravityCenter(remaining_elements);
    //cout << "Current center: "; current_center.Show(); // DEBUG
    Element furthest_element = GetFurthestElement(remaining_elements, current_center);
    solution.AddElement(furthest_element);
    EraseElement(remaining_elements, furthest_element);    
  }
  solution.UpdateDiversity();
  return solution;
}