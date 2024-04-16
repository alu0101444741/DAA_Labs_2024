/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 15 2024
 *
 * @brief Local search functions for the GRASP and GVNS algorithms.
 */

#include "local_search.h"

/**
 * @brief Build the initial solution for the GRASP algorithm.
 *  First, assign 'm' tasks with the lowest time for 'm' machines.
 *  For each remaining task, create the LRC and select a random one. This selected task will be added
 * to the machine and position that minimize the TCT of the assignment.
 * 
 * @param problem - Problem information
 * @param tasks - Task list
 * @param candidate_list_size - Maximum candidate list size
 */
Solution ConstructInitialSolution(Problem* problem, const vector<Task*>& tasks, unsigned candidate_list_size) {  
  unsigned machine_amount = problem->GetNumberOfMachines();
  Solution current_solution(problem);
  vector<bool> tasks_used(tasks.size(), false);
  for (unsigned i = 0; i < machine_amount; ++i) { // 'm' tasks with the lowest time for 'm' machines
    current_solution.PushbackTaskToMachine(i, tasks[i]);
    tasks_used[i] = true;
  }

  unsigned taskIndex = machine_amount;
  while (taskIndex < tasks.size()) { // Paso 3: Repetir hasta asignar todas las tareas    
    Solution best_solution(current_solution);
    int best_delta_TCT = INT_MAX;

    // Create candidate list
    vector<Task*> candidates(0);
    for (unsigned i = 0; i < tasks.size() && candidates.size() < candidate_list_size; ++i) {
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
      for (unsigned j = 0; j <= current_solution.GetMachineSize(i); ++j) {        
        Solution current_assignment(current_solution);
        current_assignment.InsertTaskInPosition(i, j, selected_task);
        int delta_TCT = current_assignment.GetTotalCompletionTime() - current_solution.GetTotalCompletionTime();
        if (delta_TCT < best_delta_TCT) {
          best_delta_TCT = delta_TCT;
          best_solution = current_assignment;
        }
      }
    } // Actualizar la solución
    current_solution = best_solution;
    ++taskIndex;
  }  
  //current_solution.Show("", true, true, false); // DEBUG
  return current_solution;
}

/**
 * @brief Local search algorithm to improve a given solution.
 * @param solution - The initial solution to be improved.
 * @param neighborhood The neighborhood structure to be used:
 *                     1 for Insertion Intra (Intra-machine insertion),
 *                     2 for Insertion Inter (Inter-machine insertion),
 *                     3 for Swap Intra (Intra-machine swap),
 *                     any other value defaults to Swap Inter (Inter-machine swap).
 * @param iterations_with_no_improvement Number of iterations with no improvement to stop the search.
 * @return The local optimum solution found.
 */
Solution LocalSearch(const Solution& solution, unsigned neighborhood, unsigned iterations_with_no_improvement) {
  Problem* problem = solution.GetProblem();
  Solution local_optimum(problem, solution);
  Solution current_solution(problem, solution); // Make a copy of the solution  
  int best_tct = current_solution.GetTotalCompletionTime();
  unsigned machine_amount = current_solution.GetMachineAmount();

  bool improved = true; // Flag to check if the solution has been improved
  unsigned no_improvement_counter = 0;
  while (improved || no_improvement_counter < iterations_with_no_improvement) {
    improved = false; // No improvement assumption

    switch (neighborhood) {
      case 1: LocalSearch_InsertionIntra(local_optimum, current_solution, improved, best_tct, machine_amount); break;
      case 2: LocalSearch_SwapIntra(local_optimum, current_solution, improved, best_tct, machine_amount); break;
      case 3: LocalSearch_InsertionInter(local_optimum, current_solution, improved, best_tct, machine_amount); break;
      default: LocalSearch_SwapInter(local_optimum, current_solution, improved, best_tct, machine_amount); break;
    }
    if (improved) no_improvement_counter = 0;
    else no_improvement_counter ++;
  }
  return local_optimum;
}
/**
 * @brief Perform local search to improve the given solution by moving one task from a machine to another position
 * in the same machine.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_InsertionIntra(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount) {
  for (unsigned machine_index = 0; machine_index < machine_amount; ++machine_index) {
    for (unsigned task_index = 0; task_index < current_solution.GetMachineSize(machine_index); ++task_index) {        
      Task* current_task = current_solution.GetTask(machine_index, task_index); // Guardar la tarea actual para moverla posteriormente
      // Eliminar la tarea actual de su posición actual
      current_solution.EraseTaskInPosition(machine_index, task_index);

      // Iterar sobre todas las posiciones para insertar la tarea actual en la nueva máquina
      for (unsigned position = 0; position <= current_solution.GetMachineSize(machine_index); ++position) {
        if (task_index == position) continue;

        // Insertar la tarea actual en la nueva posición y calcular el nuevo TCT
        current_solution.InsertTaskInPosition(machine_index, position, current_task);
        int current_tct = current_solution.GetTotalCompletionTime();

        // Si el nuevo TCT es mejor que el actual, actualizar la solución y marcar la mejora
        //cout << "Movement TCT: " << current_tct << " vs Best TCT:" << best_tct << endl;
        if (current_tct < best_tct) { //cout << "¡Improvement! "; // DEBUG              
          best_tct = current_tct;
          improved = true;
          solution = current_solution;
        } else { // Si el nuevo TCT no es mejor, revertir el movimiento
          current_solution.EraseTaskInPosition(machine_index, position);
        }
      }
      if (improved) break; // Si se ha mejorado la solución, salir del bucle interno
      // Si no se ha mejorado la solución, restaurar la tarea eliminada a su posición original
      current_solution.InsertTaskInPosition(machine_index, task_index, current_task);
    }             
    if (improved) break; // Si se ha mejorado la solución, salir del bucle externo
  }
}

/**
 * @brief Perform local search to improve the given solution by swapping one task from a machine with another task
 * assigned to the same machine.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_SwapIntra(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount) {
  for (unsigned machine_index = 0; machine_index < machine_amount; ++machine_index) { // Iterar sobre cada tarea en la solución actual
    unsigned machine_size = current_solution.GetMachineSize(machine_index);
    for (unsigned task_index = 0; task_index < machine_size; ++task_index) { // Iterar sobre todas las posiciones para insertar la tarea actual en la nueva máquina        
      for (unsigned position = 0; position < machine_size; ++position) {
        if (task_index == position) continue; // Iterar sobre el resto de las posiciones de la misma máquina
        // Intercambiar la tarea actual, con la tarea en la nueva posición
        current_solution.SwapTasksInPosition(machine_index, machine_index, task_index, position);
        int current_tct = current_solution.GetTotalCompletionTime();          
        
        // cout << "Movement TCT: " << current_tct << " vs Best TCT:" << best_tct << endl;

        // Si el nuevo TCT es mejor que el actual, actualizar la solución y marcar la mejora
        if (current_tct < best_tct) {  //cout << "¡Improvement! "; // DEBUG 
          best_tct = current_tct;
          improved = true;
          solution = current_solution;
        } else { // Si el nuevo TCT no es mejor, revertir el movimiento
          current_solution.SwapTasksInPosition(machine_index, machine_index, task_index, position);
        }
      }
      if (improved) break; // Si se ha mejorado la solución, salir del bucle interno
    }             
    if (improved) break; // Si se ha mejorado la solución, salir del bucle externo
  }
}

/**
 * @brief Perform local search to improve the given solution by moving one task from a machine to another.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_InsertionInter(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount) {
  for (unsigned machine_index = 0; machine_index < machine_amount; ++machine_index) { // Iterar sobre cada tarea en la solución actual
    for (unsigned task_index = 0; task_index < current_solution.GetMachineSize(machine_index); ++task_index) {        
      Task* current_task = current_solution.GetTask(machine_index, task_index); // Guardar la tarea actual para moverla posteriormente
              
      current_solution.EraseTaskInPosition(machine_index, task_index); // Eliminar la tarea actual de su posición actual
      
      for (unsigned new_machine_index = 0; new_machine_index < machine_amount; ++new_machine_index) { // Iterar sobre todas las máquinas
        if (new_machine_index == machine_index) continue; // Iterar sobre todas las posiciones en OTRA máquina         
        for (unsigned position = 0; position < current_solution.GetMachineSize(new_machine_index); ++position) {
          // Insertar la tarea actual en la nueva posición y calcular el nuevo TCT            
          current_solution.InsertTaskInPosition(new_machine_index, position, current_task);

          int current_tct = current_solution.GetTotalCompletionTime();
          
          //if (debug) cout << "Movement TCT: " << current_tct << " vs Best TCT:" << best_tct << endl; // DEBUG

          // Si el nuevo TCT es mejor que el actual, actualizar la solución y marcar la mejora
          if (current_tct < best_tct) { //cout << "¡Improvement! "; // DEBUG
            best_tct = current_tct;
            improved = true;
            solution = current_solution;
          } else { // Si el nuevo TCT no es mejor, revertir el movimiento              
            current_solution.EraseTaskInPosition(new_machine_index, position);
          }
        }
      }
      if (improved) break; // Si se ha mejorado la solución, salir del bucle interno
      // Si no se ha mejorado la solución, restaurar la tarea eliminada a su posición original        
      current_solution.InsertTaskInPosition(machine_index, task_index, current_task);
    }             
    if (improved) break; // Si se ha mejorado la solución, salir del bucle externo
  }
}

/**
 * @brief Perform local search to improve the given solution by swapping one task from a machine with another task
 * assigned to another machine.
 * @param solution - The solution to be improved.
 * @param current_solution - Solution copy to test new movements
 * @param improved - Improvement flag. Set to 'true' if an improvement was found.
 * @param best_tct - Reference to the best TCT value in order to update it at the same time as the solution
 * @param machine_amount - Number of machines
 */
void LocalSearch_SwapInter(Solution& solution, Solution& current_solution, bool& improved, int& best_tct, unsigned machine_amount) {
  for (unsigned machine_index = 0; machine_index < machine_amount; ++machine_index) { // Iterar sobre cada tarea en la solución actual
    for (unsigned task_index = 0; task_index < current_solution.GetMachineSize(machine_index); ++task_index) {
      
      for (unsigned new_machine_index = 0; new_machine_index < machine_amount; ++new_machine_index) { // Iterar sobre el resto de máquinas
        if (new_machine_index == machine_index) continue; // Iterar sobre todas las posiciones para insertar la tarea actual en la nueva máquina          
        for (unsigned position = 0; position < current_solution.GetMachineSize(new_machine_index); ++position) {
          // Intercambiar la tarea actual, con la tarea en la nueva posición
          current_solution.SwapTasksInPosition(machine_index, new_machine_index, task_index, position);
          int current_tct = current_solution.GetTotalCompletionTime();
          
          // Si el nuevo TCT es mejor que el actual, actualizar la solución y marcar la mejora
          //cout << "Movement TCT: " << current_tct << " vs Best TCT:" << best_tct << endl;
          if (current_tct < best_tct) { // cout << "¡Improvement! "; // DEBUG 
            best_tct = current_tct;
            improved = true;
            solution = current_solution;
          } else { // Si el nuevo TCT no es mejor, revertir el movimiento
            current_solution.SwapTasksInPosition(machine_index, new_machine_index, task_index, position);
          }
        }
      }
      if (improved) break; // Si se ha mejorado la solución, salir del bucle interno
    }             
    if (improved) break; // Si se ha mejorado la solución, salir del bucle externo
  }
}

/**
 * @brief Select a random task from a list of candidates.
 * @param candidates The list of candidate tasks.
 * @return A randomly selected task from the candidates.
 */
Task* SelectRandomTask(const vector<Task*>& candidates) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, candidates.size() - 1);
  return candidates[dis(gen)];
}