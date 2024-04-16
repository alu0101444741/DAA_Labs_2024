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
#include "solution.h"

using namespace std;

/** @brief Base class for any other Parallel Machine Scheduling Problem (PMSP) solver. */
class PMSP {
protected:
  Problem* problem_;
  Solution* solution_;
  string algorithm_name_;
  double tct_improvement_average_;
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
   * @param filename - The name of the file containing the problem data.
   */
  void InitializeProblem(const string& filename) { problem_->CreateFromFile(filename); }

  /** @brief Prints the PMSP information: machine amount, tasks and setup times */
  void ShowInfo() { problem_->ShowInfo(); }

  /**
   * @brief Get the name of the algorithm.
   * @return The name of the algorithm.
   */
  string GetAlgorithmName() { return algorithm_name_; }

  /**
   * @brief Setter for the problem.
   * @param problem - The name of the algorithm.
   */
  void SetProblem(Problem* problem) { problem_ = problem; }

  Problem* GetProblem() const { return problem_; }

  double GetAverageLocalSearchImprovement() const { return tct_improvement_average_; }
};
#endif // PMSP_H_