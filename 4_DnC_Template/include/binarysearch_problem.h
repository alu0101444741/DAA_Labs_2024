/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 1 2024
 *
 * @brief BinarySearchProblem class definition.
 */

#ifndef BINARYSEARCH_PROBLEM_H_
#define BINARYSEARCH_PROBLEM_H_

#include "base_problem.h"
#include "binarysearch_solution.h"

class BinarySearchProblem: public Problem {
public:
	/**
   * @brief BinarySearchProblem constructor to sort a vector.
   * @param array - vector to sort
   */
	BinarySearchProblem(const vector<int>& array) : Problem(array) {}

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

#endif /* BINARYSEARCH_PROBLEM_H_ */