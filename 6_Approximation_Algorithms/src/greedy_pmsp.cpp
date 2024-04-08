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

// Approach #2 [Apr 8 2024]
/**
 * @brief Solve the Parallel Machine Scheduling Problem using a greedy algorithm.
 * @return Solution representing the assignment of tasks to machines.
 */
Solution GreedyPMSP::Solve() {
  vector<Task*> tasks = problem_->GetAllTasks();
  unsigned machine_amount = problem_->GetNumberOfMachines();
  vector<vector<Task*>> assignment(machine_amount);

  // Paso 1: Seleccionar las m tareas con menores valores de t0j
  //vector<pair<int, int>> taskIndexTimePairs(tasks.size());
  //for (unsigned i = 0; i < tasks.size(); ++i) taskIndexTimePairs[i] = {i, problem_->GetSetupTime(0, i)};
  //sort(taskIndexTimePairs.begin(), taskIndexTimePairs.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

  // Paso 2: Inicializar S con las m primeras tareas seleccionadas
  //for (unsigned i = 0; i < machines_amount && i < tasks.size(); ++i) assignment[i].push_back(tasks[taskIndexTimePairs[i].first]);
  //tasks.erase(tasks.begin(), tasks.begin() + machines_amount);

  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return problem_->GetSetupTime(0, a->id_) < problem_->GetSetupTime(0, b->id_); //setup_times_[0][a->id_] < setup_times_[0][b->id_];
  });  
  for (unsigned i = 0; i < machine_amount; ++i) assignment[i].push_back(tasks[i]); // Step 2: 'm' tasks with the lowest time for 'm' machines
  tasks.erase(tasks.begin(), tasks.begin() + machine_amount);  
  
  unsigned taskIndex = 0;//machine_amount;
  while (taskIndex < tasks.size()) { // Paso 3: Repetir hasta asignar todas las tareas
    vector<vector<Task*>> best_solution = assignment;
    int best_delta_TCT = INT_MAX; //int best_machine = -1, best_position = -1;

    // Buscar la tarea-máquina-posición que minimiza el incremento del TCT
    for (unsigned i = 0; i < machine_amount; ++i) {
      for (unsigned j = 0; j <= assignment[i].size(); ++j) {
        vector<vector<Task*>> current_solution = assignment;
        current_solution[i].insert(current_solution[i].begin() + j, tasks[taskIndex]);
        int delta_TCT = CalculateTCT(current_solution) - CalculateTCT(assignment);
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
  return Solution(assignment);
}

