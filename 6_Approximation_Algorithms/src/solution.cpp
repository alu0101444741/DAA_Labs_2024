/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 5 2024
 *
 * @brief Solution class implementation.
 */

#include "solution.h"

/**
 * @brief Display the solution of the parallel machine scheduling problem.
 * @param show_task_info Flag indicating whether to display task information.
 * @param tag String that will preceed the total time console output
 */
void Solution::Show(const string& tag, bool show_task_info) {
  //cout << kFourSpaces + "Instance: " + filename;
  int total_tasks = 0, total_completion_time = 0;
  for (size_t i = 0; i < solution_.size(); ++i) {
    //cout << "Machine " << i+1 << " [Size: " << solution[i].size() << "]: ";
    int total_time = 0;
    for (const auto& task : solution_[i]) {
      if (show_task_info) cout << "\n\t" << task->GetInfo();
      total_time += task->time_;
      total_tasks ++;
    }
    total_completion_time = max(total_completion_time, total_time);
  }
  cout << tag << kFourSpaces + "Total time: " << total_completion_time;
  //cout << "\tTasks: " << total_tasks; // DEBUG
}