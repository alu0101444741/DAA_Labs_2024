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
 * @param problem - problem information
 * @param tasks - task list
 * @param candidate_list_size
 */
Solution ConstructInitialSolution(Problem* problem, const vector<Task*>& tasks, unsigned candidate_list_size);

/**
 * @brief Perform local search to improve the given solution. (Inserción INTER)
 * @param solution The solution to be improved.
 */
void LocalSearch_InsercionInter(Solution& solution, Problem* problem, unsigned iterations_with_no_improvement);

/**
 * @brief Perform local search to improve the given solution. (Inserción INTRA)
 * @param solution The solution to be improved.
 */
void LocalSearch_InsercionIntra(Solution& solution, Problem* problem, unsigned iterations_with_no_improvement);

/**
 * @brief Perform local search to improve the given solution. (Swap INTER)
 * @param solution The solution to be improved.
 */
void LocalSearch_SwapInter(Solution& solution, Problem* problem, unsigned iterations_with_no_improvement);

/**
 * @brief Perform local search to improve the given solution. (Swap INTRA)
 * @param solution The solution to be improved.
 */
void LocalSearch_SwapIntra(Solution& solution, Problem* problem, unsigned iterations_with_no_improvement);

/**
 * @brief Select a random task from a list of candidates.
 * @param candidates The list of candidate tasks.
 * @return A randomly selected task from the candidates.
 */
Task* SelectRandomTask(const vector<Task*>& candidates);

#endif /* LOCAL_SEARCH_H_ */