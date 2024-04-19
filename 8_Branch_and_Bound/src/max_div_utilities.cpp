/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Utility functions.
 * 
 */

#include "max_div_utilities.h"



/**
 * @brief Checks if an element exists into a vector
 * @param array - vector to check
 * @param element - element to search
 * @return 'true' if exists
 */
template <typename T>
bool vector_contains(vector<T> array, const T& element) {
  if( find(array.begin(), array.end(), element) != array.end() ) {
    return true;
  }
  return false;
}

/**
* @brief Prints an integer vector
* @param array to be printed
*/
void show_vector(vector<int> array) {
  unsigned size = array.size();
  for (unsigned i = 0; i < size; ++i){
    cout << array[i];
    if (i < (size - 1)) cout << ", ";
  } //cout << endl;
}