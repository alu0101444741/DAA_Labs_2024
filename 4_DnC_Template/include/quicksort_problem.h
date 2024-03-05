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

class QuicksortProblem: public Problem {
private:
  int left_limit_, right_limit_, pivot_;
public:
  /**
   * @brief QuicksortProblem constructor to sort a vector portion defined by two limits.
   * @param array - vector to sort
   * @param left - left limit
   * @param right - right limit
   */
	QuicksortProblem(const vector<int>& array, int left, int right) : Problem(array), left_limit_(left), right_limit_(right) {}

  /**
   * @brief Method to know if the current problem is small enough to stop dividing it. 
   * @return 'true' if it is small enough
   */
	bool Small() override;

  /**
   * @brief Divide method to slice the problem into smaller parts. 
   * @return problem parts
   */
	pair<Problem*, Problem*> Divide() override;

  /**
   * @brief Sort a problem that is small enough. 
   * @param solution - solution pointer that store the sorted vector
   */
	void SolveSmall(Solution* solution) override;
};
#endif /* QUICKSORT_PROBLEM_H_ */