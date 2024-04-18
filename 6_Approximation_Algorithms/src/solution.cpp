/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 5 2024
 *
 * @brief Solution class implementation.
 */

#include "solution.h"

/** @brief Updates the total completion time (TCT) of the solution. */
void Solution::UpdateTotalTCT() {
  unsigned machines_amount = solution_.size();
  // Calcular el tiempo de finalización máximo entre todas las máquinas
  for (unsigned i = 0; i < machines_amount; ++i) {
    UpdateMachineTCT(i);    
  }
}

/**
 * @brief Updates the total completion time (TCT) of a specific machine in the solution.
 * @param machine_index The index of the machine.
 */
void Solution::UpdateMachineTCT(unsigned machine_index) {
  int machine_completion_time = solution_[machine_index][0]->time_ + problem_->GetSetupTime(0, solution_[machine_index][0]->id_),
      setup_time = 0;
  unsigned machine_size = solution_[machine_index].size();

  for (unsigned j = 1; j < machine_size; ++j) {
    //setup_time = problem_->GetSetupTime((i == 0) ? 0 : solution_[machine_index][i - 1]->id_, solution_[machine_index][i]->id_);
    setup_time = problem_->GetSetupTime(solution_[machine_index][j - 1]->id_, solution_[machine_index][j]->id_); // sij
    machine_completion_time += ((machine_size - j) * (setup_time + solution_[machine_index][j]->time_)); // (k - i) * (sij + pj)
  }
  machines_tct_[machine_index] = machine_completion_time;

  int maximum_tct = machines_tct_[machine_index];
  for (const int& tct : machines_tct_) {
    if (tct > maximum_tct) {
      maximum_tct = tct; // Actualizar el TCT si es mayor
    }
  }
  //cout << "Updating TCT from " << total_tct_ << " to " << maximum_tct << endl; // DEBUG
  total_tct_ = maximum_tct;
}

/**
 * @brief Adds a task to the end of the machine's task list.
 * @param machine_index The index of the machine.
 * @param task          Pointer to the task to be added.
 */
void Solution::PushbackTaskToMachine(unsigned machine_index, Task* task) {
  solution_[machine_index].push_back(task);   
  UpdateMachineTCT(machine_index);
};

/**
 * @brief Erases a task at the specified position in the machine's task list.
 * @param machine_index The index of the machine.
 * @param position      The position of the task to be erased.
 */
void Solution::EraseTaskInPosition(unsigned machine_index, unsigned position) {
  bool debug = false; // DEBUG
  if (debug) cout << "M[" << machine_index << "][" << position << "] --> Deleting " << solution_[machine_index][position]->GetInfo() << endl; // DEBUG
  if (debug) cout << "\tHad " << GetMachineSize(machine_index) << " tasks. TCT: " << machines_tct_[machine_index]; // DEBUG

  solution_[machine_index].erase(solution_[machine_index].begin() + position);  
  UpdateMachineTCT(machine_index);

  if (debug) cout << "\tNow " << GetMachineSize(machine_index) << ". TCT: " << machines_tct_[machine_index] << endl; // DEBUG
}

/**
 * @brief Inserts a task at the specified position in the machine's task list.
 * @param machine_index The index of the machine.
 * @param position      The position where the task will be inserted.
 * @param task          Pointer to the task to be inserted.
 */
void Solution::InsertTaskInPosition(unsigned machine_index, unsigned position, Task* task) {
  bool debug = false; // DEBUG
  if (debug) cout << "M[" << machine_index << "][" << position << "] --> Inserting " << task->GetInfo() << endl; // DEBUG
  if (debug) cout << "\tHad " << GetMachineSize(machine_index) << " tasks. TCT: " << machines_tct_[machine_index]; // DEBUG

  solution_[machine_index].insert(solution_[machine_index].begin() + position, task);
  UpdateMachineTCT(machine_index);

  if (debug) cout << "\tNow " << GetMachineSize(machine_index) << ". TCT: " << machines_tct_[machine_index] << endl; // DEBUG
}

/**
 * @brief Swaps two tasks at the specified positions between two machines.
 * @param machine_index     The index of the first machine.
 * @param new_machine_index The index of the second machine.
 * @param first_position    The position of the first task.
 * @param second_position   The position of the second task.
 */
void Solution::SwapTasksInPosition(unsigned machine_index, unsigned new_machine_index, unsigned first_position, unsigned second_position) {
  swap(solution_[machine_index][first_position], solution_[new_machine_index][second_position]);
  UpdateMachineTCT(machine_index);
  if (machine_index != new_machine_index) UpdateMachineTCT(new_machine_index);
}


/**
 * @brief Display the solution of the parallel machine scheduling problem.
 * @param show_task_info Flag indicating whether to display task information.
 * @param show_machine_tasks Flag indicating whether to display task amount on each machine.
 * @param show_machine_tcts Flag indicating whether to display each machine TCT.
 * @param tag String that will preceed the total time console output
 */
void Solution::Show(const string& tag, bool show_machine_tasks, bool show_machine_tcts, bool show_task_info) {
  //cout << kFourSpaces + "Instance: " + filename;
  int total_tasks = 0;
  for (size_t i = 0; i < solution_.size(); ++i) {
    if (show_machine_tasks || show_machine_tcts || show_task_info)  cout << "Machine " << i;
    if (show_machine_tasks) cout << " [Size: " << solution_[i].size() << "]";
    if (show_machine_tcts) cout << " TCT: " << machines_tct_[i];
    if (show_machine_tasks || show_machine_tcts || show_task_info) cout << endl;

    for (const auto& task : solution_[i]) {      
      if (show_task_info) cout << "\n\t" << task->GetInfo();
      total_tasks ++;
    }
  }
  cout << tag << kFourSpaces + "TCT: " << GetTotalCompletionTime();
  //cout << "\tTasks: " << total_tasks; // DEBUG
}