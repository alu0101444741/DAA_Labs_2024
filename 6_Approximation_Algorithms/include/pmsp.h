/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief PMSP (Parallel Machine Scheduling Problem) interface definition.
 */

#ifndef PMSP_H_
#define PMSP_H_

#include <bits/stdc++.h>
#include <algorithm>
#include <sstream>
#include <regex>

#include "pmsp_utilities.h"
#include "problem.h"
#include "solution.h"

using namespace std;

/** @brief Base class for any other Parallel Machine Scheduling Problem (PMSP) solver. */
class PMSP {
protected:
  Problem* problem_;
  Solution* solution_;
  string algorithm_name_;
public:
  /** @brief Constructor for the Parallel Machine Scheduling Problem (PMSP) solver. */
  PMSP() : algorithm_name_("PMSP") { }

  /**
   * @brief Solve the problem and return the assignment of tasks to machines.
   * @return Solution representing the assignment of tasks to machines.
   */
  virtual Solution Solve() = 0;

  /**
   * @brief Initializes the problem by creating it from a file. 
   * @param filename The name of the file containing the problem data.
   */
  void InitializeProblem(const string& filename) { problem_->CreateFromFile(filename); }

  /** @brief Prints the PMSP information: machine amount, tasks and setup times */
  void ShowInfo() { problem_->ShowInfo(); }

  /**
   * @brief Get the name of the algorithm.
   * @return The name of the algorithm.
   */
  string GetAlgorithmName() { return algorithm_name_; }

protected:
  /**
   * @brief Get the index of a task with the given ID in the task list.
   * @param id The ID of the task to find.
   * @return The index of the task in the list if found, otherwise -1.
   */
  int GetTaskIndex(int id) const;

  /**
   * @brief Calculate the completion time of an assignment.
   * @param assignment The list of tasks assigned to each machine.
   * @return The completion time of tasks on the machine.
   */
  int CalculateTCT(vector<vector<Task*>> assignment);
};
#endif // PMSP_H_