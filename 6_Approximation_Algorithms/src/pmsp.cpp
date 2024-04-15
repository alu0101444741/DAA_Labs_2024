/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief PMSP (Parallel Machine Scheduling Problem) implementation.
 */

#include "pmsp.h"

/**
 * @brief Calculate the completion time of tasks on a machine.
 * @param machine_tasks The list of tasks assigned to a machine.
 * @return The completion time of tasks on the machine.
 */
// Approach #2 [Apr 8 2024]
/*
int PMSP::CalculateTCT(vector<vector<Task*>> assignment) {
  unsigned machines_amount = assignment.size();
  int TCT = 0;

  // Calcular el tiempo de finalización máximo entre todas las máquinas
  for (unsigned i = 0; i < machines_amount; ++i) {
    int machineCompletionTime = 0;
    int setupTime = 0;
    for (unsigned j = 0; j < assignment[i].size(); ++j) {
    //for (const auto& task : assignment[i]) {
      //machineCompletionTime += task->time_ + setupTime;
      //setupTime = (assignment[i].empty() || task->time_ == 0) ? 0 : setup_times_[i].at(&task - &assignment[i].front());
      machineCompletionTime += assignment[i][j]->time_ + setupTime;
      setupTime = (j == 0) ? 0 : problem_->GetSetupTime(i, j);
    }
    if (machineCompletionTime > TCT) {
      TCT = machineCompletionTime; // Actualizar el TCT si es mayor
    }
  }
  return TCT;
}
*/

/**
 * @brief Get the index of a task with the given ID in the task list.
 * @param id The ID of the task to find.
 * @return The index of the task in the list if found, otherwise -1.
 */
int PMSP::GetTaskIndex(int id) const {
  /*for (size_t i = 0; i < tasks_.size(); ++i) {
    if (tasks_[i]->id_ == id)  return i;
  }
  return -1;*/
  return 0;
}