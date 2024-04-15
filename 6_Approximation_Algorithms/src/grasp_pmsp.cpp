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
  Solution assignment(problem_); //vector<vector<Task*>> assignment;

  int best_completion_time = INT_MAX;

  vector<int> tct_improvements(maximum_iterations_);  
  
  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return (problem_->GetSetupTime(0, a->id_) + a->time_) < (problem_->GetSetupTime(0, b->id_) + b->time_) ; //t[0][j]
  }); 

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    //cout << "Building initial solution...\n"; // DEBUG
    Solution current_solution = ConstructInitialSolution(problem_, tasks, candidate_list_size_);

    //Solution current_solution(problem_); //vector<vector<Task*>> current_solution(machine_amount);
    //ConstructInitialSolution(current_solution, tasks); // 

    tct_improvements[iteration] = current_solution.GetTotalCompletionTime();
    
    //cout << "[Local Search]\n"; // DEBUG
    if (perform_local_search_) LocalSearch_InsercionInter(current_solution, problem_, iterations_with_no_improvement_);
    //if (perform_local_search_) LocalSearch_SwapInter(current_solution, problem_, iterations_with_no_improvement_);
    //if (perform_local_search_) LocalSearch_InsercionIntra(current_solution, problem_, iterations_with_no_improvement_);    
    //if (perform_local_search_) LocalSearch_SwapIntra(current_solution, problem_, iterations_with_no_improvement_);

    // Calculate completion time of the current solution    
    int current_completion_time = current_solution.GetTotalCompletionTime(); // CalculateTCT(current_solution);

    tct_improvements[iteration] = tct_improvements[iteration] - current_completion_time;//max(tct_improvements[iteration] - current_completion_time, 0);
    // Update the best solution
    if (current_completion_time < best_completion_time) {
      assignment = current_solution;
      best_completion_time = current_completion_time;
    }
    //int t = 0; for(const auto& a : assignment) t += a.size(); cout << "Current task amount: " << t << endl;  // DEBUG
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
