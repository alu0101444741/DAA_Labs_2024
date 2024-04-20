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
  unsigned n = solution_.size(); // solution_ --> array de elementos
  diversity_ = 0.0;
  for (unsigned i = 0; i < n - 1; ++i) {
    for (unsigned j = i + 1; j < n; ++j) {
      diversity_ += solution_[i].DistanceTo(solution_[j]); // distancia euclídea
    }
  }
}

/**
 * @brief Check if a given element is included in the solution
 * @param element - Element to find
 * @return true if included
 */
bool Solution::HasElement(const Element& element) const {
  auto it = find(solution_.begin(), solution_.end(), element);
  if (it != solution_.end()) return true;
  return false;
}

/**
 * @brief Get the Element at the specified index.
 * @param index - element index
 * @return Element 
 */
Element Solution::GetElementAtIndex(unsigned index) const {
  if (index < 0 || index >= solution_.size()) throw runtime_error("[Solution] Index out of range");
  return solution_[index];
}

/**
 * @brief Adds a new element to the solution 
 * @param element New element to be added
 * @param position Position at which to insert the element. It will be added at the end if position has a negative value
 */
void Solution::AddElement(const Element& element, int position) {
  if (position < 0) solution_.push_back(element);
  else solution_.insert(solution_.begin() + position, element);
}

/**
 * @brief Removes the element on a given position 
 * @param position Position of the element to be removed
 */
void Solution::RemoveElement(unsigned position) {
  solution_.erase(solution_.begin() + position);
}

/**
 * @brief Display the solution of the maximum diversity problem.
 * @param tag String that will preceed the total time console output
 * @param cpu String with the execution time of the algorithm
 * @param show_elements Flag indicating whether to display the elements.
 */
void Solution::Show(const string& tag, const string& cpu, bool show_elements) {
  cout << tag << kFourSpaces
       << "n: " << problem_->GetElements().size() << kFourSpaces
       << "K: " << solution_[0].GetDimension() << kFourSpaces
       << "m: " << solution_.size() << kFourSpaces
       << "z: " << diversity_ << kFourSpaces
       << cpu << endl;
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
  cout << endl;
}

