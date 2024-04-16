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
  //unsigned local_search_types = 4;
  //vector<vector<int>> tct_improvements(local_search_types, vector<int>(maximum_iterations_, 0)); 
  //int current_completion_time;
  
  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return (problem_->GetSetupTime(0, a->id_) + a->time_) < (problem_->GetSetupTime(0, b->id_) + b->time_) ; //Sorted by t[0][j]
  }); 

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    Solution current_solution = ConstructInitialSolution(problem_, tasks, candidate_list_size_);

    tct_improvements[iteration] = current_solution.GetTotalCompletionTime();    
    current_solution = LocalSearch(current_solution, local_search_type_, iterations_with_no_improvement_);

    /*
    for (unsigned i = 0; i < local_search_types; ++i) {
      tct_improvements[i][iteration] = current_solution.GetTotalCompletionTime();

      current_solution = LocalSearch(current_solution, i, iterations_with_no_improvement_);

      int current_completion_time = current_solution.GetTotalCompletionTime();
      tct_improvements[i][iteration] = tct_improvements[i][iteration] - current_completion_time;

      if (current_completion_time < best_completion_time) {
        assignment = current_solution;
        best_completion_time = current_completion_time;
      }
    }
    */
    // Calculate completion time of the current solution
    int current_completion_time = current_solution.GetTotalCompletionTime();
    tct_improvements[iteration] = tct_improvements[iteration] - current_completion_time;

    // Update the best solution    
    if (current_completion_time < best_completion_time) {
      assignment = current_solution;
      best_completion_time = current_completion_time;
    }
    
  }  
 
  // Local search average improvement
  tct_improvement_average_ = 0;
  for (unsigned i = 0; i < maximum_iterations_; ++i) {
    tct_improvement_average_ += tct_improvements[i];
  }
  /*
  tct_improvement_average_ = vector<double>(local_search_types);
  for (unsigned i = 0; i < local_search_types; ++i) {
    for (unsigned j = 0; j < maximum_iterations_; ++j) {
      tct_improvement_average_[i] += tct_improvements[i][j];
    }
    tct_improvement_average_[i] = (tct_improvement_average_[i] / (double) maximum_iterations_);
  }
  */
  // cout << " Sum = " << tct_improvement_sum << ". "; // DEBUG
  tct_improvement_average_ = (tct_improvement_average_ / (double) maximum_iterations_);

  // cout << "Average local search improvement: " << tct_improvement_sum << "%\n"; // DEBUG
 
  return assignment;
}
