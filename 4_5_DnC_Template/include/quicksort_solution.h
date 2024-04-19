/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief QuicksortSolution class definition.
 * 
 */
#ifndef QUICKSORT_SOLUTION_H_
#define QUICKSORT_SOLUTION_H_

#include "base_solution.h"

template <class T>
class QuicksortSolution: public Solution<T> {
private:
  vector<int> merge_array_;
  int left_limit;
  int right_limit;
public:
	/** @brief QuicksortSolution constructor. */
	QuicksortSolution() : Solution<T>() {}  
	
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
	void Show() { show_vector(merge_array_, "Quicksort solution:"); }

  void SetValue(const vector<int>& merge_array) { merge_array_ = merge_array; }
};

#endif /* QUICKSORT_SOLUTION_H_ */
