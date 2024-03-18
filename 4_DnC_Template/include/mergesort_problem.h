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
 */

#ifndef MERGESORT_PROBLEM_H_
#define MERGESORT_PROBLEM_H_

#include "base_problem.h"
#include "mergesort_solution.h"

template <class T>
class MergesortProblem: public Problem<T> {
private:
   vector<T> merge_array_;
public:
	/**
   * @brief MergesortProblem constructor to sort a vector.
   * @param array - vector to sort
   */
	MergesortProblem(const vector<T>& array) : /*Problem<T>(),*/ merge_array_(array) {}

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

#endif /* MERGESORT_PROBLEM_H_ */