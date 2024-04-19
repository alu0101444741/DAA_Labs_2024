/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief QuicksortProblem class definition.
 * 
 */

#ifndef QUICKSORT_PROBLEM_H_
#define QUICKSORT_PROBLEM_H_

#include "base_problem.h"
#include "quicksort_solution.h"

template <class T>
class QuicksortProblem: public Problem<T> {
private:
  vector<T> merge_array_;
  int left_limit_, right_limit_, pivot_;
public:
  /**
   * @brief QuicksortProblem constructor to sort a vector portion defined by two limits.
   * @param array - vector to sort
   * @param left - left limit
   * @param right - right limit
   */
	QuicksortProblem(const vector<T>& array, int left, int right) : /*Problem<T>(),*/ left_limit_(left), right_limit_(right) { merge_array_ = array; }

  /**
   * @brief Method to know if the current problem is small enough to stop dividing it. 
   * @return 'true' if it is small enough
   */
	bool Small() override;

  /**
   * @brief Divide method to slice the problem into smaller parts. 
   * @return problem parts
   */
	pair<Problem<T>*, Problem<T>*> Divide() override;

  /**
   * @brief Sort a problem that is small enough. 
   * @param solution - solution pointer that store the sorted vector
   */
	void SolveSmall(Solution<T>* solution) override;
};
#endif // QUICKSORT_PROBLEM_H_