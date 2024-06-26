/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 15 2024
 *
 * @brief Local search functions for the GRASP and GVNS algorithms.
 * 
 */
#ifndef LOCAL_SEARCH_H_
#define LOCAL_SEARCH_H_

#include "solution.h"
#include <bits/stdc++.h>

/**
 * @brief Build the initial solution for the GRASP algorithm.
 *  First, assign 'm' tasks with the lowest time for 'm' machines.
 *  For each remaining task, create the LRC and select a random one. This selected task will be added
 * to the machine and position that minimize the TCT of the assignment.
 * 
 * @param problem - Problem information
 * @param tasks - Task list
 * @param candidate_list_size - Maximum candidate list size
 */
Solution ConstructInitialSolution(Problem* problem, const vector<Task*>& tasks, unsigned candidate_list_size);

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
Solution LocalSearch(const Solution& solution, unsigned neighborhood, unsigned iterations_with_no_improvement = 5);

/**
 * @brief Perform local search to improve the given solution by moving one task from a machine to another position
 * in the same machine.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_InsertionIntra(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount);

/**
 * @brief Perform local search to improve the given solution by swapping one task from a machine with another task
 * assigned to the same machine.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_SwapIntra(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount);

/**
 * @brief Perform local search to improve the given solution by moving one task from a machine to another.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_InsertionInter(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount);

/**
 * @brief Perform local search to improve the given solution by swapping one task from a machine with another task
 * assigned to another machine.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_SwapInter(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount);

/**
 * @brief Select a random task from a list of candidates.
 * @param candidates - The list of candidate tasks.
 * @return A randomly selected task from the candidates.
 */
Task* SelectRandomTask(const vector<Task*>& candidates);

#endif /* LOCAL_SEARCH_H_ */