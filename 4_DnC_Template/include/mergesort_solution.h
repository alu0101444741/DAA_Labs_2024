/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief MergesortSolution class definition.
 */

#ifndef MERGESORT_SOLUTION_H_
#define MERGESORT_SOLUTION_H_

#include "base_solution.h"

template <class T>
class MergesortSolution: public Solution<T> {
private:
  vector<T> merge_array_;
public:
  /** @brief QuicksortSolution constructor. */
	MergesortSolution() : Solution<T>() {} 
	
  /**
   * @brief Combine two problem parts once both are sorted. 
   * @param sub_solutions - problem parts
   */
	void Combine(pair<Solution<T>*, Solution<T>*> sub_solutions) override;  

  /**
   * @brief Method to get a pointer to a Solution 
   * @return Solution pointer
   */
  Solution<T>* GetInstance() override;

  string GetRecurrence() override;
  
  /** @brief Prints the stored vector */
	void Show() { show_vector(merge_array_, "Mergesort solution:"); }

  void SetValue(const vector<int>& merge_array) { merge_array_ = merge_array; }
};

#endif /* MERGESORT_SOLUTION_H_ */
