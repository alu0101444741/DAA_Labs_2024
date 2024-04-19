/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Solution class implementation.
 */

#include "solution.h"

/** @brief Calculate the diversity of the solution based on the distances between elements. */
void Solution::UpdateDiversity() {
  unsigned n = solution_.size();
  diversity_ = 0.0;
  for (unsigned i = 0; i < n - 1; ++i) {
    for (unsigned j = i + 1; j < n; ++j) {
      diversity_ += solution_[i].DistanceTo(solution_[j]);
    }
  }
}

/**
 * @brief Display the solution of the maximum diversity problem.
 * @param tag String that will preceed the total time console output
 * @param show_elements Flag indicating whether to display the elements.
 */
void Solution::Show(const string& tag, bool show_elements) {
  cout << tag << kFourSpaces << "n: " << solution_.size() << kFourSpaces
       << "K: " << solution_[0].GetDimension() << kFourSpaces
       << "m: " << solution_.size() << kFourSpaces
       << "z: " << diversity_ << kFourSpaces;
  if (show_elements) {
    unsigned size = solution_.size();
    cout << "{";
    for (unsigned i = 0; i < size; ++i) {
      cout << "{";
      solution_[i].Show();
      cout << "}";
      if (i < (size - 1)) cout << ", ";    
    }
    cout << "}";
  }
  cout << kFourSpaces;
}