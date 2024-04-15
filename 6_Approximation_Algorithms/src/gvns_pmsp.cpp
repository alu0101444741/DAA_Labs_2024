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
  Solution solution(problem_);  

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++iteration) { // GRASP loop
    Solution initial_solution = grasp.Solve();    // Solucion GRASP sin busquedas locales.
    solution = initial_solution;

     if (debug) { initial_solution.Show("Grasp initial solution: ", false); cout << endl; } // DEBUG

    for (unsigned k = 0; k < k_maximum_; ++k) { // k define el radio del anillo de busqueda      
      Solution shaken_solution = Shaking(initial_solution, k); // (a) Shaking
      
      if (debug) { shaken_solution.Show(kFourSpaces + "Shaken solution (k = " + to_string(k) + "): ", false); cout << endl;}  // DEBUG   

      Solution current_solution = VND(shaken_solution); // (b) Local search by VND

      if (debug) { current_solution.Show(kFourSpaces + "VND solution: ", false); cout << endl; } // DEBUG 
      
      // (c) Movimiento o no a la solución local óptima
      if (current_solution.GetTotalCompletionTime() < initial_solution.GetTotalCompletionTime()) { 
        solution = current_solution;
        k = 1; // Continuar la búsqueda con la primera estructura de vecindario

        if (debug) { solution.Show(kFourSpaces + "Improved solution: ", false); }
      }
    }
  }
  return solution;
}

class SwapMovement {
private:
  pair<unsigned, unsigned> machines_indexes_;
  pair<unsigned, unsigned> tasks_indexes_;
public:
  SwapMovement(unsigned first_machine, unsigned second_machine, unsigned first_task, unsigned second_task) {
    machines_indexes_ = pair<unsigned, unsigned>(first_machine, second_machine);
    tasks_indexes_ = pair<unsigned,unsigned>(first_task, second_task);
  }

  SwapMovement(const Solution& solution) {
    unsigned machine_amount = solution.GetMachineAmount();
    machines_indexes_ = pair<unsigned, unsigned>(rand() % machine_amount, rand() % machine_amount);
    while(machines_indexes_.first == machines_indexes_.second) {
      machines_indexes_.second = rand() % machine_amount;
    }

    unsigned first_machine_tasks  = solution.GetMachineSize(machines_indexes_.first),
             second_machine_tasks = solution.GetMachineSize(machines_indexes_.second);

    tasks_indexes_ = pair<unsigned, unsigned>(rand() % first_machine_tasks, rand() % second_machine_tasks);
  }

  void Execute(Solution& solution) const {
    solution.SwapTasksInPosition(machines_indexes_.first, machines_indexes_.second, tasks_indexes_.first, tasks_indexes_.second);
  }

  bool operator == (const SwapMovement& otro) const {
    bool same_machines = ((machines_indexes_.first == otro.machines_indexes_.first) && (machines_indexes_.second == otro.machines_indexes_.second));
    same_machines = ((machines_indexes_.first == otro.machines_indexes_.second) && (machines_indexes_.second == otro.machines_indexes_.first));
    bool same_tasks = ((tasks_indexes_.first == otro.tasks_indexes_.first) && (tasks_indexes_.second == otro.tasks_indexes_.second));
    same_tasks = ((tasks_indexes_.first == otro.tasks_indexes_.second) && (tasks_indexes_.second == otro.tasks_indexes_.first));
    return same_machines && same_tasks;
  }

  string GetInfo() const {
    return "M[" + to_string(machines_indexes_.first)  + "][" + to_string(tasks_indexes_.first)  +
      "] to M[" + to_string(machines_indexes_.second) + "][" + to_string(tasks_indexes_.second) + "]";
  }
};

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

  // Búsqueda local por VND
  for (unsigned l = 0; l < 4; ++l) {
    Solution current_neighbor = LocalSearch(solution, l);
    if (current_neighbor.GetTotalCompletionTime() < best_neighbor.GetTotalCompletionTime()) {
      best_neighbor = current_neighbor;
      l = 0;  
    }
  }
  return best_neighbor;
}