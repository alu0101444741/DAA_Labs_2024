/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Greedy PMSP solver class implementation.
 * 
 */

#include "greedy_pmsp.h"

// Approach #2 [Apr 8 2024]
/**
 * @brief Solve the Parallel Machine Scheduling Problem using a greedy algorithm.
 * @return Solution representing the assignment of tasks to machines.
 */
Solution GreedyPMSP::Solve() {
  vector<Task*> tasks = problem_->GetAllTasks();
  unsigned machine_amount = problem_->GetNumberOfMachines();
  Solution assignment(problem_);

  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return (problem_->GetSetupTime(0, a->id_) + a->time_) < (problem_->GetSetupTime(0, b->id_) + b->time_); //setup_times_[0][a->id_] < setup_times_[0][b->id_];
  });  
  for (unsigned i = 0; i < machine_amount; ++i) assignment.PushbackTaskToMachine(i, tasks[i]);  // Step 2: 'm' tasks with the lowest time for 'm' machines
  tasks.erase(tasks.begin(), tasks.begin() + machine_amount);  
  
  //cout << "AL TEMA:\n"; // DEBUG
  unsigned taskIndex = 0; //machine_amount;
  while (taskIndex < tasks.size()) { // Paso 3: Repetir hasta asignar todas las tareas
    Solution best_solution(assignment); //vector<vector<Task*>> best_solution = assignment;
    
    int best_delta_TCT = INT_MAX; //int best_machine = -1, best_position = -1;

    // Buscar la tarea-máquina-posición que minimiza el incremento del TCT
    for (unsigned i = 0; i < machine_amount; ++i) {
      for (unsigned j = 0; j <= assignment.GetMachineSize(i)/*assignment[i].size()*/; ++j) {
        Solution current_solution(assignment); //vector<vector<Task*>> current_solution = assignment;
        current_solution.InsertTaskInPosition(i, j, tasks[taskIndex]); //current_solution[i].insert(current_solution[i].begin() + j, tasks[taskIndex]);
        //int delta_TCT = CalculateTCT(current_solution) - CalculateTCT(assignment);
        int delta_TCT = current_solution.GetTotalCompletionTime() - assignment.GetTotalCompletionTime();
        if (delta_TCT < best_delta_TCT) {
          best_delta_TCT = delta_TCT;
          best_solution = current_solution;
          //best_machine = i; //best_position = j;
        }
      }
    } // Actualizar la solución
    assignment = best_solution;
    ++taskIndex;
    //cout << "\tCurrent BEST solution\t"; Solution s(assignment); s.Show(false, ""); cout << endl; // DEBUG
  }
  return assignment;
}

