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
  unsigned maximum_iterations_;
public:  
  /** @brief Constructor for GreedyPMSP. */
  GraspPMSP(unsigned maximum_iterations) : maximum_iterations_(maximum_iterations) { algorithm_name_ = "GRASP"; }

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a GRASP algorithm.
   * @return A 2D vector representing the assignment of tasks to machines.
   */
  vector<vector<Task*>> Solve();

private:
  /**
   * @brief Select a random task from a list of candidates.
   * @param candidates The list of candidate tasks.
   * @return A randomly selected task from the candidates.
   */
  Task* SelectRandomTask(const vector<Task*>& candidates);

  /**
   * @brief Perform local search to improve the given solution (empty implementation).
   * @param solution The solution to be improved.
   */
  void LocalSearch(vector<vector<Task*>>& solution); // Método de búsqueda local (vacío)
};

#endif /* GRASP_PMSP_H_ */