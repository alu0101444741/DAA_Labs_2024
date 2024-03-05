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
void MergesortSolution::Combine(pair<Solution*, Solution*> sub_solutions) {
  vector<int> first_half = ((MergesortSolution*)sub_solutions.first)->merge_array_;
  vector<int> second_half = ((MergesortSolution*)sub_solutions.second)->merge_array_;
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
Solution* MergesortSolution::GetInstance() {
	return new MergesortSolution();
}

string MergesortSolution::GetRecurrence() { return "T(n)=2T(n/2)+O(n)";}

//MergesortSolution::~MergesortSolution() {}