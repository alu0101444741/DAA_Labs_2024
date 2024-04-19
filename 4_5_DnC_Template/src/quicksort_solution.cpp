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
template <typename T>
void QuicksortSolution<T>::Combine(pair<Solution<T>*, Solution<T>*> sub_solutions) {
  vector<T> first_half = (((QuicksortSolution<T>*)sub_solutions.first))->merge_array_;
  vector<T> second_half = (((QuicksortSolution<T>*)sub_solutions.second))->merge_array_;
  if (vector_is_sorted(first_half)) merge_array_ = first_half;
  else merge_array_ = second_half;
}

/**
 * @brief Method to get a pointer to a Solution 
 * @return Solution pointer
 */
template <typename T>
Solution<T>* QuicksortSolution<T>::GetInstance() {
	return new QuicksortSolution<T>();
}

/**
 * @brief Get the recurrence relation for the Quicksort algorithm.
 * @return string - The recurrence relation in the form T(n) = T(k) + T(n−k−1) + O(n).
 */
template <typename T>
string QuicksortSolution<T>::GetRecurrence() { return "T(n)=T(k)+T(n−k−1)+O(n)"; }