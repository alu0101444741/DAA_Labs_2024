// Approach #1 [Apr 1 2024]
/**
 * @brief Solve the Parallel Machine Scheduling Problem using a greedy algorithm.
 * @return A 2D vector representing the assignment of tasks to machines.
 */
/*
Solution GreedyPMSP::Solve() {  //Problem* problem_;
  vector<Task*> tasks = problem_->GetAllTasks();
  unsigned machine_amount = problem_->GetNumberOfMachines();
  vector<vector<Task*>> machine_assignment(machine_amount);  

  // Step 1: Choose 'm' initial tasks
  sort(tasks.begin(), tasks.end(), [&](Task* a, Task* b) {
    return problem_->GetSetupTime(0, a->id_) < problem_->GetSetupTime(0, b->id_); //setup_times_[0][a->id_] < setup_times_[0][b->id_];
  });  
  for (unsigned i = 0; i < machine_amount; ++i) machine_assignment[i].push_back(tasks[i]); // Step 2: 'm' tasks with the lowest time for 'm' machines
  tasks.erase(tasks.begin(), tasks.begin() + machine_amount);

  // Step 3: Repeat until there is no task to be assigned
  while (!tasks.empty()) {
    vector<vector<Task*>> best_assignment = machine_assignment;    
    int minimum_increment = INT_MAX, best_machine = -1, best_task_index = -1;

    // Step 5: Get the best task-machine assignment (la tarea-maquina-posicion que minimiza el incremento del TCT)
    for (unsigned machine = 0; machine < machine_amount; ++machine) {
      for (unsigned task_index = 0; task_index < tasks.size(); ++task_index) {
        Task* current_task = tasks[task_index];
        if (find(machine_assignment[machine].begin(), machine_assignment[machine].end(), current_task) != machine_assignment[machine].end()) {          
          continue; // Task already assigned to the current machine
        }
        // Calculate the setup time for inserting the current task into the current machine.
        // If the machine is empty setup_time = 0; otherwise, retrieve the setup time from the matrix for the last task on the machine and the current task.
        int setup_time = (machine_assignment[machine].empty()) ? 0 : problem_->GetSetupTime(machine_assignment[machine].back()->id_, current_task->id_);
        int completion_time = CalculateTCT(machine_assignment) + setup_time + current_task->time_; // CalculateCompletionTime(machine_assignment[machine])

        int increment = completion_time - CalculateTCT(machine_assignment); //CalculateCompletionTime(machine_assignment[machine]);
        if (increment < minimum_increment) { // Me quedo con la que menor incremento genera
          minimum_increment = increment;
          best_machine = machine;
          best_task_index = task_index;
        }
      }
    }
    if ((best_machine != -1) && (best_task_index != -1)) { // Step 6: Insert the task in the corresponding machine and update S*
      machine_assignment[best_machine].push_back(tasks[best_task_index]);
      tasks.erase(tasks.begin() + best_task_index); // Delete the task from the list
    }
  }
  return Solution(machine_assignment);
}
*/

// Approach #1 [Apr 1 2024]
/*
int GreedyPMSP::CalculateTCT(vector<vector<Task*>> assignment) {
  // Approach #1 [Apr 1 2024]

  int completion_time = 0, current_time;
  for (const vector<Task*> tasks : assignment) {
    current_time = 0;
    for (const Task* task : tasks) {
      current_time += task->time_;      
    }
    completion_time = max(completion_time, current_time);
  }
  return completion_time;
}
// what ?
int PMSP::CalculateCompletionTime(const vector<Task*>& machine_tasks) {
  int completion_time = 0, current_time = 0;
  for (const Task* task : machine_tasks) {
    current_time += task->time_;
    completion_time = max(completion_time, current_time);
  }
  return completion_time;
}
*/

/*
// Creating initial solution for the GRASP algorithm
// Approach #1 [Apr 1 2024]
for (unsigned machine = 0; machine < machine_amount; ++machine) { // Construct the current solution
    vector<Task*> machine_tasks;
    //while (machine_tasks.size() < tasks.size() / machine_amount) {
      // Select a random unused task from the LRC
      vector<Task*> candidates;
      for (unsigned i = 0; i < candidate_list_size_; ++i) {
        if (!tasks_used[i]) {
          candidates.push_back(tasks[i]);
        }
      }
      if (candidates.empty()) break; // No tasks left to assign

      Task* selected_task = SelectRandomTask(candidates);
      machine_tasks.push_back(selected_task);
      tasks_used[selected_task->id_] = true;
    //}
    current_solution[machine] = machine_tasks;
}
*/