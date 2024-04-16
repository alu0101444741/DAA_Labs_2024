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

#include "gvns_pmsp.h"

/**
 * @brief Solve the Parallel Machine Scheduling Problem using a GVNS algorithm.
 * @return Solution representing the assignment of tasks to machines
 */
Solution GvnsPMSP::Solve() {  
  bool debug = false; // DEBUG
  unsigned grasp_iterations = 5, candidate_list_size = 3;
  GraspPMSP grasp(grasp_iterations, candidate_list_size, false); grasp.SetProblem(problem_);
  Solution best_solution(problem_);  

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    //Solution initial_solution = grasp.Solve();    // Solucion GRASP sin busquedas locales.
    //solution = initial_solution;
    Solution current_solution = grasp.Solve();

    if (debug) { current_solution.Show("Grasp initial solution: ", false); cout << endl; } // DEBUG

    for (unsigned k = 0; k < k_maximum_; ++k) { // k define el radio del anillo de busqueda      
      //Solution shaken_solution = Shaking(initial_solution, k); // (a) Shaking
      Solution shaken_solution = Shaking(current_solution, k); // (a) Shaking
      
      if (debug) { shaken_solution.Show(kFourSpaces + "Shaken solution (k = " + to_string(k) + "): ", false); cout << endl;}  // DEBUG   

      Solution vnd_solution = VND(shaken_solution); // (b) Local search by VND

      if (debug) { vnd_solution.Show(kFourSpaces + "VND solution: ", false); cout << endl; } // DEBUG 
      
      // (c) Movimiento o no a la solución local óptima
      if (vnd_solution.GetTotalCompletionTime() < current_solution.GetTotalCompletionTime()) { 
        best_solution = vnd_solution;
        current_solution = vnd_solution;
        k = 0; // Continuar la búsqueda con la primera estructura de vecindario

        if (debug) { best_solution.Show(kFourSpaces + "Improved solution: ", false); }
      }
    }
  }
  return best_solution;
}

/**
 * @brief Shake the given solution to explore a set of diverse solutions.
 * @param solution The current solution to be shaken.
 * @param k The number of shaking movements to apply.
 * @return The shaken solution.
 */
Solution GvnsPMSP::Shaking(const Solution& solution, unsigned k) {
  Solution shaken_solution(solution);
  vector<SwapMovement> movements;
  for (unsigned i = 0; i < k; ++i) {
    bool valid_movement = true;
    SwapMovement movement(solution);
    for (unsigned j = 0; j < movements.size(); ++j) {
      if (movement == movements[j]) {
        valid_movement = false;
        break;
      }
    }
    if (valid_movement) movements.push_back(movement);
    else i--;
  }
  //cout << "(!) MOVEMENTS:\n"; for (const SwapMovement& movement : movements) cout << "\t" << movement.GetInfo() << endl; // DEBUG
  for (const SwapMovement& movement : movements) movement.Execute(shaken_solution);
  return shaken_solution;
}

/**
 * @brief Perform Variable Neighborhood Descent (VND) local search to improve the given solution.
 * @param solution The initial solution to be improved.
 * @return The best neighbor solution found by VND.
 */
Solution GvnsPMSP::VND(const Solution& solution) { 
  Solution best_neighbor = solution;
  Solution current_neighbor = solution;
  // Búsqueda local por VND
  for (unsigned l = 0; l < local_search_types_; ++l) {
    current_neighbor = LocalSearch(best_neighbor, l);
    if (current_neighbor.GetTotalCompletionTime() < best_neighbor.GetTotalCompletionTime()) {
      best_neighbor = current_neighbor;
      l = 0;
    }
  }
  return best_neighbor;
}

Solution GvnsPMSP::Solve_Modificacion() {  
  unsigned grasp_iterations = 5, candidate_list_size = 3;
  Solution best_solution(problem_);

  GraspPMSP grasp(grasp_iterations, candidate_list_size, true, 0);
  grasp.SetProblem(problem_);   
  Solution initial_solution = grasp.Solve();
  

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    //Solution initial_solution = grasp.Solve();    // Solucion GRASP sin busquedas locales.
    //solution = initial_solution;
    Solution current_solution = initial_solution;  

    for (unsigned k = 0; k < k_maximum_; ++k) { // k define el radio del anillo de busqueda      
      Solution shaken_solution = Shaking(current_solution, k); // (a) Shaking     

      Solution vnd_solution = VND_Modificacion(shaken_solution); // (b) Local search by VND
      
      // (c) Movimiento o no a la solución local óptima
      if (vnd_solution.GetTotalCompletionTime() < current_solution.GetTotalCompletionTime()) { 
        best_solution = vnd_solution;
        current_solution = vnd_solution;
        k = 0; // Continuar la búsqueda con la primera estructura de vecindario
      }
    }
  }
  return best_solution;
}

/**
 * @brief Perform Variable Neighborhood Descent (VND) local search to improve the given solution.
 * @param solution The initial solution to be improved.
 * @return The best neighbor solution found by VND.
 */
Solution GvnsPMSP::VND_Modificacion(const Solution& solution) { 
  Solution best_neighbor = solution;
  Solution current_neighbor = solution;
  // Búsqueda local por VND
  for (unsigned l = 2; l < local_search_types_; ++l) {
    //cout << " LS tipo " << l << endl;
    current_neighbor = LocalSearch(best_neighbor, l);
    if (current_neighbor.GetTotalCompletionTime() < best_neighbor.GetTotalCompletionTime()) {
      best_neighbor = current_neighbor;
      l = 2;
    }
  }
  return best_neighbor;
}

