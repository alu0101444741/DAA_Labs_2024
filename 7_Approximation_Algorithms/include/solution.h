/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 5 2024
 *
 * @brief Solution class for the PMSP algorithm.
 */

#ifndef PMSP_SOLUTION_H_
#define PMSP_SOLUTION_H_

#include <algorithm>
#include <sstream>
#include <regex>
#include "pmsp_utilities.h"
#include "problem.h"

using namespace std;

/** @brief Solution class for the Parallel Machine Scheduling Problem (PMSP) solver. */
class Solution {
private:
  Problem* problem_;
  vector<vector<Task*>> solution_;
  vector<int> machines_tct_;
  int total_tct_;
public:
  /**
   * @brief Constructor for creating a Solution object.
   * @param problem A pointer to the problem instance.
   */
  Solution(Problem* problem) : problem_(problem) {
    unsigned machine_amount = problem->GetNumberOfMachines();
    solution_ = vector<vector<Task*>>(machine_amount, vector<Task*>(0));
    machines_tct_= vector<int>(machine_amount, 0);
    total_tct_ = 0;
  }

  /**
   * @brief Constructor for creating a Solution object based on an existing solution.
   * @param problem A pointer to the problem instance.
   * @param solution The existing solution from which to create the new solution.
   */
  Solution(Problem* problem, const Solution& solution) : problem_(problem), solution_(solution.GetSolution())  {
    machines_tct_= vector<int>(problem->GetNumberOfMachines(), 0);
    UpdateTotalTCT();
  }    

  /**
   * @brief Adds a task to the end of the machine's task list.
   * @param machine_index The index of the machine.
   * @param task          Pointer to the task to be added.
   */
  void PushbackTaskToMachine(unsigned machine_index, Task* task);

  /**
   * @brief Erases a task at the specified position in the machine's task list.
   * @param machine_index The index of the machine.
   * @param position      The position of the task to be erased.
   */
  void EraseTaskInPosition(unsigned machine_index, unsigned position);

  /**
   * @brief Inserts a task at the specified position in the machine's task list.
   * @param machine_index The index of the machine.
   * @param position      The position where the task will be inserted.
   * @param task          Pointer to the task to be inserted.
   */
  void InsertTaskInPosition(unsigned machine_index, unsigned position, Task* task);

  /**
   * @brief Swaps two tasks at the specified positions between two machines.
   * @param machine_index     The index of the first machine.
   * @param new_machine_index The index of the second machine.
   * @param first_position    The position of the first task.
   * @param second_position   The position of the second task.
   */
  void SwapTasksInPosition(unsigned machine_index, unsigned new_machine_index, unsigned first_position, unsigned second_position);

  /**
   * @brief Gets the total completion time (TCT) of the solution.
   * @return The total completion time (TCT) of the solution.
   */
  int GetTotalCompletionTime() const { return total_tct_; }

  /**
   * @brief Gets the total amount of machines in the solution.
   * @return The total amount of machines in the solution.
   */
  unsigned GetMachineAmount() const { return solution_.size(); }

  /**
   * @brief Gets the number of tasks in a specific machine.
   * @param machine_index The index of the machine.
   * @return The number of tasks in the specified machine.
   */
  unsigned GetMachineSize(unsigned machine_index) const { return solution_[machine_index].size(); }  

  /**
   * @brief Gets the task at the specified position in the specified machine.
   * @param machine_index The index of the machine.
   * @param position      The position of the task.
   * @return Pointer to the task at the specified position.
   */
  Task* GetTask(unsigned machine_index, unsigned position) const { return solution_[machine_index][position]; }

  Problem* GetProblem() const { return problem_; }

  /**
   * @brief Display the solution of the parallel machine scheduling problem.
   * @param show_task_info Flag indicating whether to display task information.
   * @param show_machine_tasks Flag indicating whether to display task amount on each machine.
   * @param show_machine_tcts Flag indicating whether to display each machine TCT.
   * @param tag String that will preceed the total time console output
   */
  void Show(const string& tag, bool show_machine_tasks = false, bool show_machine_tcts = false, bool show_task_info = false);

private:
  /** @brief Updates the total completion time (TCT) of the solution. */
  void UpdateTotalTCT();

  /**
   * @brief Updates the total completion time (TCT) of a specific machine in the solution.
   * @param machine_index The index of the machine.
   */
  void UpdateMachineTCT(unsigned machine_index);

  /**
   * @brief Gets the current solution.
   * @return The current solution as a vector of vectors of pointers to tasks.
   */
  vector<vector<Task*>> GetSolution() const { return solution_; };
};
#endif // PMSP_SOLUTION_H_