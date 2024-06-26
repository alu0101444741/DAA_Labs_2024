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

/**
 * @brief Local search algorithm to improve a given solution.
 * @param solution - The initial solution to be improved.
 * @return The local optimum solution found.
 */
Solution LocalSearch(const Solution& solution) {
  Solution current_solution = solution;
  Solution best_solution = solution;
  unsigned solution_size = solution.GetSolutionSize();

  vector<unsigned> all_elements_indexes(solution_size, 0);
  vector<bool> elements_included = vector<bool>(solution_size, false);
  
  for (unsigned i = 0; i < solution_size; ++i) {
    all_elements_indexes[i] = i;
    // Check every element that is included in the current solution
    elements_included[i] = solution.HasElement(all_elements_indexes[i]);
  }
  
  // Para cada elemento de la solucion actual, intercambiarlo por uno de los restantes
  bool improved = true;
  while (improved) {
    improved = false;
    for (unsigned solution_index = 0; solution_index < solution_size; ++ solution_index) {
      for (unsigned element_index = 0; element_index < solution_size; ++ element_index) {        
        if (elements_included[element_index]) continue; // Si el elemento está incluido, se ignora

        current_solution.RemoveElement(current_solution.GetElementAtIndex(solution_index));
        current_solution.AddElement(all_elements_indexes[element_index], solution_index);

        elements_included[solution_index] = false;
        elements_included[element_index] = true;

        if (current_solution.GetDiversity() > best_solution.GetDiversity()) {
          best_solution = current_solution;
          improved = true;
        } else {
          current_solution.RemoveElement(all_elements_indexes[element_index]);
          current_solution.AddElement(solution.GetElementAtIndex(solution_index), solution_index);
          elements_included[solution_index] = true;
          elements_included[element_index] = false;
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
 * @return Index of a randomly selected element from the candidates.
 */
unsigned SelectRandomElement(const vector<unsigned>& candidates) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, candidates.size() - 1);
  return candidates[dis(gen)];
}