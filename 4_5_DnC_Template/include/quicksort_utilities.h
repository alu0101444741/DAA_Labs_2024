/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief Definition of auxiliary functions used in the Quicksort.
 */
#ifndef QUICKSORT_UTILITIES_H
#define QUICKSORT_UTILITIES_H
#include <vector>
#include "math.h"
using namespace std;

/**
 * @brief Swap the content of a vector given two indexes 
 * @param array 
 * @param first_position - first index
 * @param second_position - second index
 */
template <typename T>
void swap(vector<T>& array, int first_position, int second_position);

/**
 * @brief Quicksort helper function.
 *   Given an array, two indexes and a pivot it will swap the array values
 * until both indexes values intersect.
 * @param array - vector reference
 * @param left_limit 
 * @param right_limit
 * @return intersection index 
 */
template <typename T>
int partition(vector<T>& array, int left_limit, int right_limit);

#endif // QUICKSORT_UTILITIES_H