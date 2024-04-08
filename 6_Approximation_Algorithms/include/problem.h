/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 5 2024
 *
 * @brief Problem class for the PMSP algorithm.
 */

#ifndef PMSP_PROBLEM_H_
#define PMSP_PROBLEM_H_

#include <algorithm>
#include <sstream>
#include <regex>
#include "pmsp_utilities.h"

using namespace std;

/** @brief Problem class for the Parallel Machine Scheduling Problem (PMSP) solver. */
class Problem {
private:
  unsigned machine_amount_;
  vector<Task*> tasks_;
  vector<vector<int>> setup_times_;
public:
  /** @brief Constructor for the Problem class. */
  Problem() {}

  /**
   * @brief Create the PMSP instance from a 'txt' file. 
   * @param filename - name/path of the file
   */
  void CreateFromFile(const string& filename);  

  /**
   * @brief Retrieves the number of machines.
   * @returns The number of machines.
   */
  unsigned GetNumberOfMachines() const { return machine_amount_; }

  /**
   * @brief Retrieves all tasks stored in the problem.
   * @returns A vector containing pointers to all tasks.
   */
  vector<Task*> GetAllTasks() const { return tasks_; }

  /**
   * @brief Retrieves the setup time for a specific row and column.
   * @param row - The row index.
   * @param column - The column index.
   * @returns The setup time value.
   * @throws If the row or column index is out of range.
   */
  int GetSetupTime(unsigned row, unsigned column) const;  

  /**
   * @brief Retrieves a task by its index.
   * @param index - The index of the task.
   * @returns A pointer to the task.
   * @throws If the index is out of range.
   */
  Task* GetTaskByIndex(unsigned index) const;

  /** @brief Prints the PMSP information: machine amount, tasks and setup times */
  void ShowInfo();
};
#endif // PMSP_PROBLEM_H_