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
 * @return A 2D vector representing the assignment of tasks to machines.
 */
vector<vector<Task*>> GraspPMSP::Solve() {
  vector<vector<Task*>> machine_assignment(machine_amount_);
  int best_completion_time = INT_MAX;

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) {
    vector<vector<Task*>> current_solution(machine_amount_);
    vector<bool> tasks_used(tasks_.size(), false);

    for (unsigned machine = 0; machine < machine_amount_; ++machine) { // Construct the current solution
      vector<Task*> machine_tasks;
      while (machine_tasks.size() < tasks_.size() / machine_amount_) {
        // Select a random unused task
        vector<Task*> candidates;
        for (unsigned i = 0; i < tasks_.size(); ++i) {
          if (!tasks_used[i]) {
            candidates.push_back(tasks_[i]);
          }
        }
        if (candidates.empty()) break; // No tasks left to assign

        Task* selected_task = SelectRandomTask(candidates);
        machine_tasks.push_back(selected_task);
        tasks_used[selected_task->id_] = true;
      }
      current_solution[machine] = machine_tasks;
    }

    LocalSearch(current_solution); // Local search (empty)

    // Calculate completion time of the current solution
    int current_completion_time = 0;
    for (const auto& machine_tasks : current_solution) {
      current_completion_time = max(current_completion_time, CalculateCompletionTime(machine_tasks));
    }
    // Update the best solution
    if (current_completion_time < best_completion_time) {
      machine_assignment = current_solution;
      best_completion_time = current_completion_time;
    }
  }
  return machine_assignment;
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

/**
 * @brief Perform local search to improve the given solution (empty implementation).
 * @param solution The solution to be improved.
 */
void GraspPMSP::LocalSearch(vector<vector<Task*>>& solution) {
  //
  // ...
  //
}