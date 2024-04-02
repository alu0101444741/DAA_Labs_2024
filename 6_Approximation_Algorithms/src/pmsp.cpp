/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief PMSP (Parallel Machine Scheduling Problem) implementation.
 */

#include "pmsp.h"

/**
 * @brief Create the PMSP instance from a 'txt' file. 
 * @param filename - name/path of the file
 */
void PMSP::CreateFromFile(const string& filename) {
  tasks_.resize(0);
  setup_times_.resize(0);
  ifstream file(filename);
  unsigned n, m;

  if (file.is_open()) { //cout << "Mirando " << filename;  // DEBUG
    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string token;
      ss >> token;

      if (token == "n:") { // Número de tareas
        ss >> n;
        tasks_.resize(n); //cout << ". Tareas " << n; // DEBUG
      } else if (token == "m:") { // Número de máquinas
        ss >> m;
        machine_amount_ = m;  //cout << ". Máquinas " << m << endl;  // DEBUG
      } else if (regex_match(token, regex("Pi:U\\[[0-9]+-[0-9]+\\]"))) { //(token == "Pi:") {
        for (unsigned i = 0; i < n; ++i) {
          int time;
          ss >> time;
          tasks_[i] = new Task(i, 0, time);
        }
      } else if (regex_match(token, regex("Sij:U\\[[0-9]+-[0-9]+\\]"))) { //(token == "Sij:") {
        setup_times_.resize(n + 1, vector<int>(n + 1, 0));
        for (unsigned i = 0; i <= n; ++i) {
          getline(file, line);
          stringstream ss(line);
          for (unsigned j = 0; j <= n; ++j) {
            ss >> setup_times_[i][j];
          }
        }
      }
    }
    file.close(); //cout << " <FIN>\n"; // DEBUG 
  } else {
    cerr << "Error al abrir el archivo: " << filename << endl;
  }
}

/**
 * @brief Get the index of a task with the given ID in the task list.
 * @param id The ID of the task to find.
 * @return The index of the task in the list if found, otherwise -1.
 */
int PMSP::GetTaskIndex(int id) const {
  for (size_t i = 0; i < tasks_.size(); ++i) {
    if (tasks_[i]->id_ == id)  return i;
  }
  return -1;
}

/**
 * @brief Calculate the completion time of tasks on a machine.
 * @param machine_tasks The list of tasks assigned to a machine.
 * @return The completion time of tasks on the machine.
 */
int PMSP::CalculateCompletionTime(const vector<Task*>& machine_tasks) {
  int completion_time = 0, current_time = 0;
  for (const Task* task : machine_tasks) {
    current_time += task->time_;
    completion_time = max(completion_time, current_time);
  }
  return completion_time;
}

/** @brief Prints the PMSP information: machine amount, tasks and setup times */
void PMSP::ShowInfo() {
  cout << "Machines: " << machine_amount_ << endl;  
  cout << "Tasks: " << tasks_.size() << endl;  
  for (const auto& task : tasks_) cout << "\t" << task->GetInfo() << endl;

  unsigned columns = (setup_times_.size() > 0) ? setup_times_[0].size() : 0;
  cout << "\nSetup times [ " << setup_times_.size() << " x " << columns << " ]\n";
  //bool shorter_info = (task_amount_ > 10);
  for (unsigned i = 0; i < setup_times_.size(); ++i) {
    show_vector(setup_times_[i]);
  }  
}