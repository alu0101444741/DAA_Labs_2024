/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief MergesortProblem class implementation.
 */

#include <iostream>
#include "mergesort_solution.h"

/**
 * @brief Combine two problem parts once both are sorted. 
 * @param sub_solutions - problem parts
 */
template <typename T>
void MergesortSolution<T>::Combine(pair<Solution<T>*, Solution<T>*> sub_solutions) {
  vector<T> first_half = ((MergesortSolution<T>*)sub_solutions.first)->merge_array_;
  vector<T> second_half = ((MergesortSolution<T>*)sub_solutions.second)->merge_array_;
  merge_array_.resize(first_half.size() + second_half.size());

  unsigned i = 0, j = 0, k = 0;
  unsigned first_half_size = first_half.size();
  unsigned second_half_size = second_half.size();

  while((i < first_half_size) && (j < second_half_size)){
    if(first_half[i] <= second_half[j]){
      merge_array_[k++] = first_half[i++];
    } else {
      merge_array_[k++] =  second_half[j++];
    }
  }
  while(i < first_half_size) {
    merge_array_[k++] = first_half[i++];
  }
  while(j < second_half_size) {
    merge_array_[k++] = second_half[j++];
  }
}

/**
 * @brief Method to get a pointer to a Solution 
 * @return Solution pointer
 */
template <typename T>
Solution<T>* MergesortSolution<T>::GetInstance() {
	return new MergesortSolution<T>();
}

template <typename T>
string MergesortSolution<T>::GetRecurrence() { return "T(n)=2T(n/2)+O(n)";}

//MergesortSolution::~MergesortSolution() {}