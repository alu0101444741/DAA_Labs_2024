/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 5 2024
 *
 * @brief Problem class implementation.
 */

#include "problem.h"

/**
 * @brief Create the PMSP instance from a 'txt' file. 
 * @param filename - name/path of the file
 */
void Problem::CreateFromFile(const string& filename) {
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

/** @brief Prints the problem information: machine amount, tasks and setup times */
void Problem::ShowInfo() {
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

/**
 * @brief Retrieves the setup time for a specific row and column.
 * @param row - The row index.
 * @param column - The column index.
 * @returns The setup time value.
 * @throws If the row or column index is out of range.
 */
int Problem::GetSetupTime(unsigned row, unsigned column) const {
  if (row >= setup_times_.size() || row < 0) throw runtime_error("[Setup times] Row index out of range");
  if (column >= setup_times_[0].size() || column < 0) throw runtime_error("[Setup times] Column index out of range");
  return(setup_times_[row][column]);
}

/**
 * @brief Retrieves a task by its index.
 * @param index - The index of the task.
 * @returns A pointer to the task.
 * @throws If the index is out of range.
 */
Task* Problem::GetTaskByIndex(unsigned index) const {
  if (index >= tasks_.size() || index < 0) throw runtime_error("[Tasks] Index out of range");
  return(tasks_[index]);
}