/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief Implementation of auxiliary functions used in the Quicksort.
 */

#include "quicksort_utilities.h"

/**
 * @brief Quicksort helper function.
 *   Given an array, two indexes and a pivot it will swap the array values
 * until both indexes values intersect.
 * @param array - vector reference
 * @param left_limit 
 * @param right_limit 
 * @param pivot 
 * @return intersection index 
 */
template <typename T>
int partition(vector<T>& array, int left_limit, int right_limit/*, int pivot*/) {
  /*int left = left_limit, right = right_limit;
  while(left < right) {
    while(array[left] < pivot) left++;
    while(array[right] > pivot) right--;
    if(left <= right) {
      swap(array, left, right); left++; right--;
    }
  }
  swap(array, min(left, right_limit), right_limit);
  return(min(left, right_limit));*/
  int pivot = array[right_limit]; // selecciona el pivote
  int i = (left_limit - 1); // índice del elemento más pequeño

  for (int j = left_limit; j <= right_limit; j++) {
    // Si el elemento actual es más pequeño que el pivote
    if (array[j] < pivot) {
      i++; // incrementa el índice del elemento más pequeño
      swap(array, i, j);
    }
  }
  swap(array, i + 1, right_limit);
  return (i + 1);
}

/**
 * @brief Swap the content of a vector given two indexes 
 * @param array 
 * @param first_position - first index
 * @param second_position - second index
 */
template <typename T>
void swap(vector<T>& array, int first_position, int second_position) {
  T swap_element = array[first_position];  
  array[first_position] = array[second_position];
  array[second_position] = swap_element;
}