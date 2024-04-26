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
 * @brief Local search algorithm to improve a given solution.
 * @param solution - The initial solution to be improved.
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