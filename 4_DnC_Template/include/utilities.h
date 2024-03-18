/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 1 2024
 *
 * @brief Definition of auxiliary functions.
 */
#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Displays the elements of a vector along with a title.
 * @param array The vector to be displayed.
 * @param title The title to be printed before the vector elements.
 */
template <typename T>
void show_vector(const vector<T>& array, const string& title);

/**
* @brief Create a vector with random integers
* @param size - vector's desired size
* @param maximum_value - maximum value permitted
* @return vector of integer
*/
vector<int> create_random_vector(unsigned size, int maximum_value);

template <typename T>
bool vector_is_sorted(const vector<T>& array);

#endif // UTILITIES_H