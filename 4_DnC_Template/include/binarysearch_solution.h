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

template <class T>
class BinarySearchSolution: public Solution<T> {
private:
  int solution_index_; 
  vector<T> merge_array_;
public:
  /** @brief BinarySearchSolution constructor. */
	BinarySearchSolution() : Solution<T>() {} 
	
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

  // <----- CAMBIAR
  void Show() { show_vector(merge_array_, "BinarySearch solution:"); }

  void SetValue(const vector<int>& merge_array) { merge_array_ = merge_array; }
};

#endif /* BINARYSEARCH_SOLUTION_H_ */
