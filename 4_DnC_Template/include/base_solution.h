/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief Solution class definition.
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <utility>
#include "utilities.h"

class Solution {
public:
	/** @brief Solution constructor. */
	Solution() {}
	
	/**
   * @brief Combine two problem parts once both are sorted. 
   * @param sub_solutions - problem parts
   */
	virtual void Combine(pair<Solution*, Solution*> sub_solutions) = 0;	

  /**
   * @brief Method to get a pointer to a Solution 
   * @return Solution pointer
   */
  virtual Solution* GetInstance() = 0;

  virtual string GetRecurrence() = 0;
  //string GetRecurrence() { return "T(n) <= " + a + "T(" + b + ") +" + c ;} //aT(b) + c

  /**
   * @brief Setter method for the stored vector. 
   * @param array - new vector
   */
  //virtual void SetValue(const vector<int>& array) { merge_array = array; }

  virtual void Show() = 0;

  /** @brief Solution destructor */
	virtual ~Solution() {}
};

#endif /* SOLUTION_H_ */
