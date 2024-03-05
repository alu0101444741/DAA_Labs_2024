/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief QuicksortSolution class implementation.
 */

#include <iostream>
#include "quicksort_solution.h"

/**
 * @brief Combine two problem parts once both are sorted. 
 * @param sub_solutions - problem parts
 */
void QuicksortSolution::Combine(pair<Solution*, Solution*> sub_solutions) {
  vector<int> first_half = (((QuicksortSolution*)sub_solutions.first))->merge_array_;
  vector<int> second_half = (((QuicksortSolution*)sub_solutions.second))->merge_array_;
  if (vector_is_sorted(first_half)) merge_array_ = first_half;
  else merge_array_ = second_half;
}

/**
 * @brief Method to get a pointer to a Solution 
 * @return Solution pointer
 */
Solution* QuicksortSolution::GetInstance() {
	return new QuicksortSolution();
}

/**
 * @brief Get the recurrence relation for the Quicksort algorithm.
 * @return string - The recurrence relation in the form T(n) = T(k) + T(n−k−1) + O(n).
 */
string QuicksortSolution::GetRecurrence() { return "T(n)=T(k)+T(n−k−1)+O(n)"; }