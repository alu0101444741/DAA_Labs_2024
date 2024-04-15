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
  int machine_completion_time = 0, setup_time = 0;
  for (unsigned i = 0; i < solution_[machine_index].size(); ++i) {
    /*
      Tiempo de setup s[i][j] para procesar la tarea j justo después de la tarea i.
      (!) s[i->id][j->id] para task_anterior(i) y task_actual(j) 
      Con sij != sji, en general.
      Hay un tiempo de setup s0j para procesar la primera tarea en cada máquina.
    */
    setup_time = problem_->GetSetupTime((i == 0) ? 0 : solution_[machine_index][i - 1]->id_, solution_[machine_index][i]->id_);
    machine_completion_time += (solution_[machine_index][i]->time_ + setup_time);
    


    //machine_completion_time += solution_[machine_index][i]->time_ + setup_time;
    //setup_time = (i == 0) ? 0 : problem_->GetSetupTime(machine_index, i);
  }
  machines_tct_[machine_index] = machine_completion_time;
  if (machines_tct_[machine_index] > total_tct_) {
    total_tct_ = machines_tct_[machine_index]; // Actualizar el TCT si es mayor
  }
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
 * @param tag String that will preceed the total time console output
 */
void Solution::Show(const string& tag, bool show_task_info) {
  //cout << kFourSpaces + "Instance: " + filename;
  int total_tasks = 0, total_completion_time = 0;
  for (size_t i = 0; i < solution_.size(); ++i) {
    //cout << "Machine " << i+1 << " [Size: " << solution[i].size() << "]: ";
    int total_time = 0;
    for (const auto& task : solution_[i]) {
      if (show_task_info) cout << "\n\t" << task->GetInfo();
      total_time += task->time_;
      total_tasks ++;
    }
    total_completion_time = max(total_completion_time, total_time);
  }
  cout << tag << kFourSpaces + "Total time: " << total_completion_time;
  //cout << "\tTasks: " << total_tasks; // DEBUG
}