/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 1 2024
 *
 * @brief BinarySearchSolution class definition.
 */

#ifndef BINARYSEARCH_SOLUTION_H_
#define BINARYSEARCH_SOLUTION_H_

#include "base_solution.h"

class BinarySearchSolution: public Solution {
private:
  int solution_index_; 
public:
  /** @brief BinarySearchSolution constructor. */
	BinarySearchSolution() : Solution() {} 
	
  /**
   * @brief Combine two problem parts once both are sorted. 
   * @param sub_solutions - problem parts
   */
	void Combine(pair<Solution*, Solution*> sub_solutions) override;  

  /**
   * @brief Method to get a pointer to a Solution 
   * @return Solution pointer
   */
  Solution* GetInstance() override;
};

#endif /* MERGESORTSOLUTION_H_ */
