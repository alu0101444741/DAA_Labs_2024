/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief Local search functions for the Maximum Diversity algorithms. Definition.
 * 
 */
#ifndef LOCAL_SEARCH_H_
#define LOCAL_SEARCH_H_

#include "solution.h"

/**
 * @brief Build the initial solution for the GRASP algorithm.
 * 
 * @param problem - Problem information
 * @param candidate_list_size - Maximum candidate list size
 */
Solution ConstructInitialSolution(Problem* problem, unsigned candidate_list_size);

/**
 * @brief Local search algorithm to improve a given solution.
 * @param solution - The initial solution to be improved.
 * @param neighborhood The neighborhood structure to be used:
 *                     1 for Insertion Intra (Intra-machine insertion),
 *                     2 for Insertion Inter (Inter-machine insertion),
 *                     3 for Swap Intra (Intra-machine swap),
 *                     any other value defaults to Swap Inter (Inter-machine swap).
 * @param iterations_with_no_improvement Number of iterations with no improvement to stop the search.
 * @return The local optimum solution found.
 */
Solution LocalSearch(const Solution& solution);

/**
 * @brief Select a random element from a list of candidates.
 * @param candidates The list of candidate elements.
 * @return A randomly selected element from the candidates.
 */
Element SelectRandomElement(const vector<Element>& candidates);

#endif /* LOCAL_SEARCH_H_ */