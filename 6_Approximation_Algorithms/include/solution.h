/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 5 2024
 *
 * @brief Solution class for the PMSP algorithm.
 */

#ifndef PMSP_SOLUTION_H_
#define PMSP_SOLUTION_H_

#include <algorithm>
#include <sstream>
#include <regex>
#include "pmsp_utilities.h"

using namespace std;

/** @brief Solution class for the Parallel Machine Scheduling Problem (PMSP) solver. */
class Solution {
private:
  vector<vector<Task*>> solution_;
public:
  /** @brief Constructor for the Problem class. */
  Solution(const vector<vector<Task*>>& solution) : solution_(solution) {}

  /**
   * @brief Display the solution of the parallel machine scheduling problem.
   * @param tag String that will preceed the total time console output
   * @param show_task_info Flag indicating whether to display task information.
  */
  void Show(const string& tag, bool show_task_info);
};
#endif // PMSP_SOLUTION_H_