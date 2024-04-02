/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Utility functions.
 * 
 */
#ifndef PMSP_UTILITIES_H_
#define PMSP_UTILITIES_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const string kFourSpaces = "    ";

/** @brief Class representing a task in the Parallel Machine Scheduling Problem. */
class Task {
public:
  int id_, machine_, time_;

  /**
   * @brief Constructor for Task class.
   * @param id The ID of the task.
   * @param machine The machine assigned to the task.
   * @param time The processing time of the task.
   */
  Task(int id, int machine, int time) : id_(id), machine_(machine), time_(time) {}

  /**
   * @brief Get information about the task.
   * @return A string containing task information.
   */
  string GetInfo() const {
    return "Task ID: " + to_string(id_) + ", Machine: " + to_string(machine_) + ", Time: " + to_string(time_);
  }
};

/**
 * @brief Checks if an element exists into a vector
 * @param array - vector to check
 * @param element - element to search
 * @return 'true' if exists
 */
template <typename T>
bool vector_contains(vector<T> array, const T& element);

/**
* @brief Prints an integer vector
* @param array to be printed
*/
void show_vector(vector<int> array);

/**
 * @brief Display the solution of the parallel machine scheduling problem.
 * @param solution The solution containing the assignment of tasks to machines.
 * @param filename The name of the instance.
 * @param show_task_info Flag indicating whether to display task information.
 */
void show_solution(const vector<vector<Task*>>& solution, const string& filename, bool show_task_info);

#endif // PMSP_UTILITIES_H_ 