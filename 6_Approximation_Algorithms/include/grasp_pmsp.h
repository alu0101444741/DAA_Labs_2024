/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief GRASP PMSP solver class definition.
 * 
 */
#ifndef GRASP_PMSP_H_
#define GRASP_PMSP_H_

#include "pmsp.h"

/** @brief GRASP Parallel Machine Scheduling Problem solver. */
class GraspPMSP: public PMSP {
private:
  unsigned maximum_iterations_, candidate_list_size_;
public:  
  /**
   * @brief Constructor for GraspPMSP.
   * @param maximum_iterations - number of iterations for the grasp algorithm
   * @param candidate_list_size - size of the list of candidates (LRC)
   */
  GraspPMSP(unsigned maximum_iterations , unsigned candidate_list_size)
  : maximum_iterations_(maximum_iterations),
    candidate_list_size_(candidate_list_size) { algorithm_name_ = "GRASP"; problem_ = new Problem(); }

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a GRASP algorithm.
   * @return A 2D vector representing the assignment of tasks to machines.
   */
  Solution Solve();

private:
  /**
   * @brief Select a random task from a list of candidates.
   * @param candidates The list of candidate tasks.
   * @return A randomly selected task from the candidates.
   */
  Task* SelectRandomTask(const vector<Task*>& candidates);

  /**
   * @brief Build the initial solution for the GRASP algorithm.
   *  First, assign 'm' tasks with the lowest time for 'm' machines.
   *  For each remaining task, create the LRC and select a random one. This selected task will be added
   * to the machine and position that minimize the TCT of the assignment.
   * 
   * @param current_solution - reference to an empty solution
   * @param tasks - task list
   */
  void ConstructInitialSolution(vector<vector<Task*>>& current_solution, const vector<Task*>& tasks);

  /**
   * @brief Perform local search to improve the given solution (empty implementation).
   * @param solution The solution to be improved.
   */
  void LocalSearch(vector<vector<Task*>>& solution);
};

#endif /* GRASP_PMSP_H_ */