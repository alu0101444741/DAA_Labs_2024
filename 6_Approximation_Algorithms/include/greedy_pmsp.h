/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Greesy PMSP solver class definition.
 * 
 */
#ifndef GREEDY_PMSP_H_
#define GREEDY_PMSP_H_

#include "pmsp.h"

/** @brief Greedy Parallel Machine Scheduling Problem solver. */
class GreedyPMSP: public PMSP {
public:  
  /** @brief Constructor for GreedyPMSP. */
  GreedyPMSP() { algorithm_name_ = "Greedy"; problem_ = new Problem(); }  

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a greedy algorithm.
   * @return Solution representing the assignment of tasks to machines.
   */
  Solution Solve();  
};

#endif /* GREEDY_PMSP_H_ */