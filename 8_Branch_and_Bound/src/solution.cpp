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
  /*
  unsigned n = solution_.size(); // solution_ --> array de elementos
  diversity_ = 0.0;
  for (unsigned i = 0; i < n - 1; ++i) {
    for (unsigned j = i + 1; j < n; ++j) {
      diversity_ += solution_[i].DistanceTo(solution_[j]); // distancia euclídea
    }
  }
  */
}

/**
 * @brief Check if a given element is included in the solution
 * @param element - Element to find
 * @return true if included
 */
/*
bool Solution::HasElement(const Element& element) const {
  auto it = find(solution_.begin(), solution_.end(), element);
  if (it != solution_.end()) return true;
  return false;
}
*/
bool Solution::HasElement(unsigned element_index) const {
  index_validation(element_index, solution_.size(), "Solution");
  for (const unsigned& index : solution_) if (index == element_index) return true;
  return false;
}

/**
 * @brief Get the Element at the specified index.
 * @param index - element index
 * @return Element 
 */
unsigned Solution::GetElementAtIndex(unsigned index) const {
  //if (index < 0 || index >= solution_.size()) throw runtime_error("[Solution] Index out of range");
  index_validation(index, solution_.size(), "Solution");
  return solution_[index];
}

/**
 * @brief Adds a new element to the solution 
 * @param element New element to be added
 * @param position Position at which to insert the element. It will be added at the end if position has a negative value
 */
//void Solution::AddElement(const Element& element, int position) {
void Solution::AddElement(unsigned element_index, int position) {
  if (position < 0) solution_.push_back(element_index);
  else solution_.insert(solution_.begin() + position, element_index);

  // For each remaining element, add it distance with the one to be added
  for (const unsigned& index : solution_) {
    diversity_ += problem_->GetDistance(element_index, index);
  }
}

/**
 * @brief Removes the element on a given position 
 * @param position Position of the element to be removed
 */
void Solution::RemoveElement(unsigned position) {
  // For each remaining element, substract it distance with the one to be erased
  for (const unsigned& index : solution_) {
    diversity_ -= problem_->GetDistance(solution_[position], index);
  }
  solution_.erase(solution_.begin() + position);
}

/**
 * @brief Display the solution of the maximum diversity problem.
 * @param tag String that will preceed the total time console output
 * @param cpu String with the execution time of the algorithm
 * @param iterations Iterations executed by the algorithm
 * @param candidate_list_size Size of the candidate list
 * @param show_elements Flag indicating whether to display the elements.
 */
void Solution::Show(const string& tag, const string& cpu, unsigned iterations, unsigned candidate_list_size, bool show_elements) {
  sort(solution_.begin(), solution_.end());
  cout << tag << endl
       << "n: " << problem_->GetElements().size() << kFourSpaces
       << "K: " << problem_->GetDimension() << kFourSpaces
       << "m: " << solution_.size() << kFourSpaces;

  if (iterations > 1) cout << "Iter: " << iterations << kFourSpaces;
  if (candidate_list_size > 1) cout << "|LRC|: " << candidate_list_size << kFourSpaces;

  cout << "z: " << diversity_ << kFourSpaces
       << cpu   << endl;
  if (show_elements) {
    unsigned size = solution_.size();
    cout << "S = {";
    for (unsigned i = 0; i < size; ++i) {
      problem_->GetElementOnIndex(i).Show();
      if (i < (size - 1)) cout << ", ";    
    }
    cout << "}";
  }
  cout << endl;
}

/**
 * @brief Display the solution of the maximum diversity problem.
 * @param tag String that will preceed the total time console output
 * @param cpu String with the execution time of the algorithm
 * @param iterations Iterations executed by the algorithm
 * @param candidate_list_size Size of the candidate list
 * @param show_elements Flag indicating whether to display the elements.
 */
void Solution::ShowMarkdown(const string& tag, const string& cpu, unsigned iterations, unsigned candidate_list_size, bool show_elements) {
  sort(solution_.begin(), solution_.end());
  cout << "| " << tag << " | " // Filename
       << problem_->GetElements().size() << " | " // n
       << problem_->GetDimension() << " | " // K
       << solution_.size() << " | "; // m

  if (iterations > 1) cout << iterations << " | "; // Iter
  if (candidate_list_size > 1) cout << candidate_list_size << " | "; // |LRC|

  cout << diversity_ << " | " // z
       << cpu << " | "; // CPU
  if (show_elements) { // S
    unsigned size = solution_.size();
    cout << "{";
    for (unsigned i = 0; i < size; ++i) {
      cout << solution_[i];
      if (i < (size - 1)) cout << ", ";    
    }
    cout << "}";
  }
  cout << " | ";
}

