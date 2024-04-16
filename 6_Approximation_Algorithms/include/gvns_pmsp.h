/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 14 2024
 *
 * @brief GVNS PMSP solver class definition.
 * 
 */
#ifndef GVNS_PMSP_H_
#define GVNS_PMSP_H_

#include "grasp_pmsp.h"

/** @brief GVNS Parallel Machine Scheduling Problem solver. */
class GvnsPMSP: public PMSP {
private:
  unsigned maximum_iterations_, candidate_list_size_, k_maximum_;
  unsigned iterations_with_no_improvement_ = 2;
public:  
  /**
   * @brief Constructor for GvnsPMSP.
   * @param maximum_iterations - Number of iterations for the grasp algorithm
   * @param candidate_list_size - Size of the list of candidates (LRC)
   * @param k_maximum - Maximum perturbation amount
   */
  GvnsPMSP(unsigned maximum_iterations, unsigned candidate_list_size, unsigned k_maximum)
  : maximum_iterations_(maximum_iterations),
    candidate_list_size_(candidate_list_size),
    k_maximum_(k_maximum)
    { algorithm_name_ = "GVNS"; problem_ = new Problem(); }

  /**
   * @brief Solve the Parallel Machine Scheduling Problem using a GVNS algorithm.
   * @return A 2D vector representing the assignment of tasks to machines.
   */
  Solution Solve();

private:
  /**
   * @brief Shake the given solution to explore a set of diverse solutions.
   * @param solution The current solution to be shaken.
   * @param k The number of shaking movements to apply.
   * @return The shaken solution.
   */
  Solution Shaking(const Solution& solution, unsigned k);

  /**
   * @brief Perform Variable Neighborhood Descent (VND) local search to improve the given solution.
   * @param solution The initial solution to be improved.
   * @return The best neighbor solution found by VND.
   */
  Solution VND(const Solution& solution);
};

/** @brief Represents a movement to swap tasks between machines in a solution. */
class SwapMovement {
private:
  pair<unsigned, unsigned> machines_indexes_;
  pair<unsigned, unsigned> tasks_indexes_;
public:  
  /**
   * @brief Constructs a SwapMovement object.
   * @param solution The solution to operate on.
   */
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

  /* 
  SwapMovement(unsigned first_machine, unsigned second_machine, unsigned first_task, unsigned second_task) {
    machines_indexes_ = pair<unsigned, unsigned>(first_machine, second_machine);
    tasks_indexes_ = pair<unsigned,unsigned>(first_task, second_task);
  }
  */

  /**
   * @brief Executes the swap movement on the solution.
   * @param solution The solution to operate on.
   */
  void Execute(Solution& solution) const {
    solution.SwapTasksInPosition(machines_indexes_.first, machines_indexes_.second, tasks_indexes_.first, tasks_indexes_.second);
  }

  /**
   * @brief Checks if two SwapMovement objects are equal.
   * @param other The other SwapMovement object to compare with.
   * @return True if the two SwapMovement objects are equal, false otherwise.
   */
  bool operator == (const SwapMovement& other) const {
    bool same_machines = ((machines_indexes_.first == other.machines_indexes_.first) && (machines_indexes_.second == other.machines_indexes_.second));
    same_machines = ((machines_indexes_.first == other.machines_indexes_.second) && (machines_indexes_.second == other.machines_indexes_.first));
    bool same_tasks = ((tasks_indexes_.first == other.tasks_indexes_.first) && (tasks_indexes_.second == other.tasks_indexes_.second));
    same_tasks = ((tasks_indexes_.first == other.tasks_indexes_.second) && (tasks_indexes_.second == other.tasks_indexes_.first));
    return same_machines && same_tasks;
  }

  /**
   * @brief Gets a string representation of the swap movement.
   * @return A string representing the swap movement.
   */
  string GetInfo() const {
    return "M[" + to_string(machines_indexes_.first)  + "][" + to_string(tasks_indexes_.first)  +
      "] to M[" + to_string(machines_indexes_.second) + "][" + to_string(tasks_indexes_.second) + "]";
  }
};
#endif /* GVNS_PMSP_H_ */