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
 */

#include "grasp_pmsp.h"

/**
 * @brief Solve the Parallel Machine Scheduling Problem using a GRASP algorithm.
 * @return Solution representing the assignment of tasks to machines
 */
Solution GraspPMSP::Solve() {
  vector<Task*> tasks = problem_->GetAllTasks();
  unsigned machine_amount = problem_->GetNumberOfMachines();
  vector<vector<Task*>> assignment/*(machine_amount)*/;
  vector<vector<Task*>> initial_assignment;

  int best_completion_time = INT_MAX;  

  // Choose 'm' initial tasks One for each machine.
  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return problem_->GetSetupTime(0, a->id_) < problem_->GetSetupTime(0, b->id_); //setup_times_[0][a->id_] < setup_times_[0][b->id_];
  }); 

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    vector<vector<Task*>> current_solution(machine_amount);

    //cout << "Building initial solution...\n"; // DEBUG
    ConstructInitialSolution(current_solution, tasks);    

    //cout << "[Local Search]\n"; // DEBUG
    LocalSearch(current_solution);

    // Calculate completion time of the current solution
    int current_completion_time = CalculateTCT(current_solution);
    // Update the best solution
    if (current_completion_time < best_completion_time) {
      assignment = current_solution;
      best_completion_time = current_completion_time;
    }
    //int t = 0; for(const auto& a : assignment) t += a.size(); cout << "Current task amount: " << t << endl;  // DEBUG
  }
  return Solution(assignment);
}

/**
 * @brief Build the initial solution for the GRASP algorithm.
 *  First, assign 'm' tasks with the lowest time for 'm' machines.
 *  For each remaining task, create the LRC and select a random one. This selected task will be added
 * to the machine and position that minimize the TCT of the assignment.
 * 
 * @param current_solution - reference to an empty solution
 * @param tasks - task list
 */
void GraspPMSP::ConstructInitialSolution(vector<vector<Task*>>& current_solution, const vector<Task*>& tasks) {
  unsigned machine_amount = problem_->GetNumberOfMachines();
  vector<bool> tasks_used(tasks.size(), false);
  for (unsigned i = 0; i < machine_amount; ++i) { // 'm' tasks with the lowest time for 'm' machines
    current_solution[i].push_back(tasks[i]);
    tasks_used[i] = true;
  }

  unsigned taskIndex = machine_amount;
  while (taskIndex < tasks.size()) { // Paso 3: Repetir hasta asignar todas las tareas
    vector<vector<Task*>> best_solution = current_solution;
    int best_delta_TCT = INT_MAX; //int best_machine = -1, best_position = -1;

    // Create candidate list
    vector<Task*> candidates(0);
    for (unsigned i = 0; i < tasks.size() && candidates.size() < candidate_list_size_; ++i) {
      if (!tasks_used[i]) {
        candidates.push_back(tasks[i]);
      }
    }
    if (candidates.empty()) break; // No tasks left to assign

    Task* selected_task = SelectRandomTask(candidates);
    for (unsigned i = 0; i < tasks.size(); ++i) {
      if (tasks[i]->id_ == selected_task->id_) {
        tasks_used[i] = true;
        break;
      }
    }
    // Buscar la tarea-máquina-posición que minimiza el incremento del TCT
    for (unsigned i = 0; i < machine_amount; ++i) {
      for (unsigned j = 0; j <= current_solution[i].size(); ++j) {
        vector<vector<Task*>> current_assignment = current_solution;
        current_assignment[i].insert(current_assignment[i].begin() + j, selected_task);
        int delta_TCT = CalculateTCT(current_assignment) - CalculateTCT(current_solution);
        if (delta_TCT < best_delta_TCT) {
          best_delta_TCT = delta_TCT;
          best_solution = current_assignment;
          //best_machine = i; //best_position = j;
        }
      }
    } // Actualizar la solución
    current_solution = best_solution;
    ++taskIndex;
    //cout << "\tCurrent BEST solution\t"; Solution s(assignment); s.Show(false, ""); cout << endl; // DEBUG
  }
}

/**
 * @brief Perform local search to improve the given solution.
 * @param solution The solution to be improved.
 */
void GraspPMSP::LocalSearch(vector<vector<Task*>>& solution) {  
  vector<vector<Task*>> current_solution = solution; // Make a copy of the solution
  int best_tct = CalculateTCT(current_solution);
  
  bool improved = true; // Flag to check if the solution has been improved
  while (improved) {
    improved = false; // No improvement assumption

    // Iterar sobre cada tarea en la solución actual
    for (unsigned machine_index = 0; machine_index < current_solution.size(); ++machine_index) {
      for (unsigned task_index = 0; task_index < current_solution[machine_index].size(); ++task_index) {        
        Task* current_task = current_solution[machine_index][task_index]; // Guardar la tarea actual para moverla posteriormente

        // Eliminar la tarea actual de su posición actual
        current_solution[machine_index].erase(current_solution[machine_index].begin() + task_index);
        
        // Check all possible movements.
        // Evaluate the insertion of the current_task for each position on each machine

        // Iterar sobre todas las máquinas para evaluar posibles movimientos
        for (unsigned new_machine_index = 0; new_machine_index < current_solution.size(); ++new_machine_index) {
          // Iterar sobre todas las posiciones para insertar la tarea actual en la nueva máquina
          for (unsigned position = 0; position <= current_solution[new_machine_index].size(); ++position) {
            // Insertar la tarea actual en la nueva posición y calcular el nuevo TCT
            current_solution[new_machine_index].insert(current_solution[new_machine_index].begin() + position, current_task);
            int current_tct = CalculateTCT(current_solution);

            // Si el nuevo TCT es mejor que el actual, actualizar la solución y marcar la mejora
            if (current_tct < best_tct) {
              best_tct = current_tct;
              improved = true;
              solution = current_solution;
            } else { // Si el nuevo TCT no es mejor, revertir el movimiento
              current_solution[new_machine_index].erase(current_solution[new_machine_index].begin() + position);
            }
          }
        }
        if (improved) break; // Si se ha mejorado la solución, salir del bucle interno

        // Si no se ha mejorado la solución, restaurar la tarea eliminada a su posición original
        current_solution[machine_index].insert(current_solution[machine_index].begin() + task_index, current_task);
      }             
      if (improved) break; // Si se ha mejorado la solución, salir del bucle externo
    }
  }  
}

/**
 * @brief Select a random task from a list of candidates.
 * @param candidates The list of candidate tasks.
 * @return A randomly selected task from the candidates.
 */
Task* GraspPMSP::SelectRandomTask(const vector<Task*>& candidates) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, candidates.size() - 1);
  return candidates[dis(gen)];
}