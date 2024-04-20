/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief Local search functions for the Maximum Diversity algorithms. Implementation.
 */

#include "local_search.h"

Solution LocalSearch(const Solution& solution) {
  Solution current_solution = solution;
  Solution best_solution = solution;
  vector<Element> all_elements = solution.GetProblem()->GetElements();
  vector<bool> elements_included = vector<bool>(all_elements.size(), false);

  // Check every element that is included in the current solution
  for (unsigned i = 0; i < all_elements.size(); ++i) {
    if (solution.HasElement(all_elements[i])) elements_included[i] = true;
  }
  
  // Para cada elemento de la solucion actual
  // Intercambiarlo por uno de los restantes
  bool improved = true;
  while (improved) {
    improved = false;
    for (unsigned solution_index = 0; solution_index < all_elements.size(); ++ solution_index) {
      for (unsigned element_index = 0; element_index < all_elements.size(); ++ element_index) {
        // Si el elemento está incluido, se ignora
        if (elements_included[element_index]) continue;
        Element current_element = solution.GetElementAtIndex(solution_index);

        current_solution.RemoveElement(solution_index);
        current_solution.AddElement(all_elements[element_index], solution_index);
        current_solution.UpdateDiversity();

        if (current_solution.GetDiversity() > best_solution.GetDiversity()) {
          best_solution = current_solution;
          improved = true;
        } else {
          current_solution.RemoveElement(solution_index);
          current_solution.AddElement(current_element, solution_index);
          current_solution.UpdateDiversity();
        }
      }
      if (improved) break;
    }
    if (improved) break;
  }
  return best_solution;
}

/**
 * @brief Select a random element from a list of candidates.
 * @param candidates The list of candidate elements.
 * @return A randomly selected element from the candidates.
 */
Element SelectRandomElement(const vector<Element>& candidates) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, candidates.size() - 1);
  return candidates[dis(gen)];
}