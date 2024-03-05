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

#ifndef MERGESORTPROBLEM_H_
#define MERGESORTPROBLEM_H_

#include "base_problem.h"
#include "mergesort_solution.h"

class MergesortProblem: public Problem {
public:
	/**
   * @brief MergesortProblem constructor to sort a vector.
   * @param array - vector to sort
   */
	MergesortProblem(const vector<int>& array) : Problem(array) {}

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

#endif /* MERGESORTPROBLEM_H_ */