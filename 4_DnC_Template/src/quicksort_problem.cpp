/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief QuicksortProblem class implementation.
 */

#include "quicksort_problem.h"
#include "quicksort_solution.h"
#include "quicksort_utilities.h"

/**
 * @brief Method to know if the current problem is small enough to stop dividing it. 
 * @return 'true' if it is small enough
 */
template <typename T>
bool QuicksortProblem<T>::Small() {
	return (left_limit_ >= right_limit_);
}

/**
 * @brief Divide method to slice the problem into smaller parts. 
 * @return problem parts
 */
template <typename T>
pair<Problem<T>*, Problem<T>*> QuicksortProblem<T>::Divide() {
  pivot_ = merge_array_[right_limit_];
  int half_size = partition(this->merge_array_, left_limit_, right_limit_);

  vector<T> first_half, second_half;
  for(unsigned index = 0; index < half_size; ++index)
    first_half.push_back(merge_array_[index]);
  for(unsigned index = half_size; index < this->merge_array_.size(); ++index)
    second_half.push_back(merge_array_[index]);

  pair<Problem<T>*, Problem<T>*> sub_problems;
  sub_problems.first = new QuicksortProblem<T>(merge_array_, left_limit_, half_size - 1);
  sub_problems.second = new QuicksortProblem<T>(merge_array_, half_size + 1, right_limit_);
  return (sub_problems);
}

/**
 * @brief Sort a problem that is small enough. 
 * @param solution - solution pointer that store the sorted vector
 */
template <typename T>
void QuicksortProblem<T>::SolveSmall(Solution<T>* solution) {
	((QuicksortSolution<T>*)solution)->SetValue(merge_array_);
  /*if ((this->merge_array_.size() > 1) &&  (this->merge_array_[0] > this->merge_array_[1])) {
    swap(this->merge_array_, 0, 1);
  }*/
}
