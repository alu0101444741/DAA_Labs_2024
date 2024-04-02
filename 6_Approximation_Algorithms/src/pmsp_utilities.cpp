/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Utility functions.
 * 
 */

#include "pmsp_utilities.h"

/**
 * @brief Checks if an element exists into a vector
 * @param array - vector to check
 * @param element - element to search
 * @return 'true' if exists
 */
template <typename T>
bool vector_contains(vector<T> array, const T& element) {
  if( find(array.begin(), array.end(), element) != array.end() ) {
    return true;
  }
  return false;
}

/**
* @brief Prints an integer vector
* @param array to be printed
*/
void show_vector(vector<int> array) {
  unsigned size = array.size();
  for (unsigned i = 0; i < size; ++i){
    cout << array[i];
    if (i < (size - 1)) cout << ", ";
  } //cout << endl;
}

/**
 * @brief Display the solution of the parallel machine scheduling problem.
 * @param solution The solution containing the assignment of tasks to machines.
 * @param filename The name of the instance.
 * @param show_task_info Flag indicating whether to display task information.
 */
void show_solution(const vector<vector<Task*>>& solution, const string& filename, bool show_task_info) {
  cout << kFourSpaces + "Instance: " + filename;
  int total_tasks = 0, total_completion_time = 0;
  for (size_t i = 0; i < solution.size(); ++i) {
    //cout << "Machine " << i+1 << " [Size: " << solution[i].size() << "]: ";
    int total_time = 0;
    for (const auto& task : solution[i]) {
      if (show_task_info) cout << "\n\t" << task->GetInfo();
      total_time += task->time_;
      total_tasks ++;
    }
    //cout << "Total time: " << total_time << endl;
    total_completion_time = max(total_completion_time, total_time);
  }
  //cout << "-> Total tasks: " << total_tasks << endl << endl;
  cout << kFourSpaces + "Total time: " << total_completion_time;
}