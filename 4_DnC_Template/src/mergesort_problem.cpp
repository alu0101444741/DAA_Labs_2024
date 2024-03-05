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

#include "mergesort_problem.h"
#include "mergesort_solution.h"
#include "math.h"

/**
 * @brief Method to know if the current problem is small enough to stop dividing it. 
 * @return 'true' if it is small enough
 */
bool MergesortProblem::Small() {
	return (merge_array_.size() <= 1);
}

/**
 * @brief Divide method to slice the problem into smaller parts. 
 * @return problem parts
 */
pair<Problem*,Problem*> MergesortProblem::Divide() {
  pair<Problem*, Problem*> sub_problems;
  vector<int> first_half;
  vector<int> second_half;
  unsigned half_size = merge_array_.size() / 2;
  for(unsigned i = 0; i < half_size; ++i){
    first_half.push_back(merge_array_[i]);
  }
  for(unsigned i = half_size; i < merge_array_.size(); ++i){
    second_half.push_back(merge_array_[i]);
  }

  sub_problems.first = new MergesortProblem(first_half);
  sub_problems.second = new MergesortProblem(second_half);
  return sub_problems;
}

/**
 * @brief Sort a problem that is small enough. 
 * @param solution - solution pointer that store the sorted vector
 */
void MergesortProblem::SolveSmall(Solution* solution) {
	((MergesortSolution*)solution)->SetValue(merge_array_);
}