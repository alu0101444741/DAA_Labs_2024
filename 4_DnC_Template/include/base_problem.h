/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief Problem class definition.
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "base_solution.h"

class Problem {
protected:
  vector<int> merge_array_;
public:
	/** @brief Problem constructor . */
	Problem(const vector<int>& array) : merge_array_(array) {}

  /** @brief Problem destructor . */
	virtual ~Problem() {}

  /**
   * @brief Method to know if the current problem is small enough to stop dividing it. 
   * @return 'true' if it is small enough
   */
	virtual bool Small() = 0;

  /**
   * @brief Divide method to slice the problem into smaller parts. 
   * @return problem parts
   */
	virtual pair<Problem*, Problem*> Divide() = 0;

  /**
   * @brief Sort a problem that is small enough. 
   * @param solution - solution pointer that store the sorted vector
   */
	virtual void SolveSmall(Solution* solution) = 0;
};

#endif /* PROBLEM_H_ */
