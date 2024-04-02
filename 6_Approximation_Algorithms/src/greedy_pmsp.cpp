/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Greesy PMSP solver class implementation.
 * 
 */

#include "greedy_pmsp.h"

/**
 * @brief Solve the Parallel Machine Scheduling Problem using a greedy algorithm.
 * @return A 2D vector representing the assignment of tasks to machines.
 */
vector<vector<Task*>> GreedyPMSP::Solve() {  
  vector<vector<Task*>> machine_assignment(machine_amount_);
  vector<Task*> tasks = tasks_;

  // Step 1: Choose 'm' initial tasks
  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return setup_times_[0][a->id_] < setup_times_[0][b->id_];
  });  
  for (unsigned i = 0; i < machine_amount_; ++i) machine_assignment[i].push_back(tasks[i]); // Step 2: 'm' tasks with the lowest time for 'm' machines
  tasks.erase(tasks.begin(), tasks.begin() + machine_amount_);

  // Step 3: Repeat
  while (!tasks.empty()) {
    vector<vector<Task*>> best_assignment = machine_assignment;    
    int minimum_increment = INT_MAX, best_machine = -1, best_task_index = -1;

    // Step 5: Get the best task-machine assignment (la tarea-maquina-posicion que minimiza el incremento del TCT)
    for (unsigned machine = 0; machine < machine_amount_; ++machine) {
      for (unsigned task_index = 0; task_index < tasks.size(); ++task_index) {
        Task* current_task = tasks[task_index];
        if (find(machine_assignment[machine].begin(), machine_assignment[machine].end(), current_task) != machine_assignment[machine].end()) {          
          continue; // Task already assigned to the current machine
        }
        // Calculate the setup time for inserting the current task into the current machine.
        // If the machine is empty, setup time is 0; otherwise, retrieve the setup time from the matrix for the last task on the machine and the current task.
        int setup_time = (machine_assignment[machine].empty()) ? 0 : setup_times_[machine_assignment[machine].back()->id_][current_task->id_];
        int completion_time = CalculateCompletionTime(machine_assignment[machine]) + setup_time + current_task->time_;

        int increment = completion_time - CalculateCompletionTime(machine_assignment[machine]);
        if (increment < minimum_increment) {
          minimum_increment = increment;
          best_machine = machine;
          best_task_index = task_index;
        }
      }
    }
    if (best_machine != -1 && best_task_index != -1) { // Step 6: Insert the task in the corresponding machine and update S*
      machine_assignment[best_machine].push_back(tasks[best_task_index]);
      tasks.erase(tasks.begin() + best_task_index); // Delete the task from the list
    }

    // Paso 7: Verificar si todas las tareas han sido asignadas a alguna máquina
    //for (const auto& machineTasks : machine_assignment) {
    //  if (machineTasks.size() != tasks.size() / machine_amount_) break;
    //}
    //if (tasks.empty()) break;
  }
  return machine_assignment;
}