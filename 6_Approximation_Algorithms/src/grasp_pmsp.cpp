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
  Solution assignment(problem_);

  int best_completion_time = INT_MAX;

  vector<int> tct_improvements(maximum_iterations_);  
  
  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return (problem_->GetSetupTime(0, a->id_) + a->time_) < (problem_->GetSetupTime(0, b->id_) + b->time_) ; //Sorted by t[0][j]
  }); 

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    Solution current_solution = ConstructInitialSolution(problem_, tasks, candidate_list_size_);

    tct_improvements[iteration] = current_solution.GetTotalCompletionTime();
    
    //current_solution = LocalSearch(current_solution, local_search_type_, iterations_with_no_improvement_);
    current_solution = LocalSearchMainStructure(current_solution, local_search_type_, iterations_with_no_improvement_);

    // Calculate completion time of the current solution
    int current_completion_time = current_solution.GetTotalCompletionTime();

    tct_improvements[iteration] = tct_improvements[iteration] - current_completion_time;
    // Update the best solution
    if (current_completion_time < best_completion_time) {
      assignment = current_solution;
      best_completion_time = current_completion_time;
    }
  }  
/* 
  // Local search average improvement DEBUG
  double tct_improvement_sum = 0;
  //show_vector(tct_improvements);
  for (unsigned i = 0; i < maximum_iterations_; ++i) {
    tct_improvement_sum += tct_improvements[i];
  }
  cout << " Sum = " << tct_improvement_sum << ". ";
  tct_improvement_sum = (tct_improvement_sum / (double) maximum_iterations_);

  cout << "Average local search improvement " << tct_improvement_sum << "%\n";
*/  
  return assignment;
}
