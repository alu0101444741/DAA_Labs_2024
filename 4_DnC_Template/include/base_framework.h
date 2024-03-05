/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief 'Divide and Conquer' Framework class definition.
 */

#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#include "base_problem.h"
#include "base_solution.h"

class DnCFramework {
public:
  Solution* algorithm_;
  unsigned recursive_calls_;
  unsigned maximum_depth_;

	/** @brief Framework constructor. */
	DnCFramework() {}  

  /**
   * @brief Divide and Conquer method.
   * Solves a problem and store the result on a given solution pointer.
   * @param problem - problem to solve
   * @param solution - solution pointer to store the solution
   */
	void Solve(Problem* problem, Solution* solution, unsigned maximum_depth);
  
  void ResetRecursiveCalls(); // Modificacion Mar 5 2024
  void ResetMaximumDepth(); // Modificacion Mar 5 2024

  string GetRecurrence();
  void SetAlgorithm(Solution* solution);

  /** @brief Framework destructor. */
	virtual ~DnCFramework() {}
};

#endif /* FRAMEWORK_H_ */
