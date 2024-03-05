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
#include "utilities.h"

/**
* @brief Create a vector with random integers
* @param size - vector's desired size
* @param maximum_value - maximum value permitted
* @return vector of integer
*/
vector<int> create_random_vector(unsigned size, int maximum_value) {
  vector<int> random_vector;
  int negative = 1;
  for (unsigned i = 0; i < size; ++i) {
    if (rand() % 2 == 0) negative = 1; else negative = -1;
    random_vector.push_back((rand() % maximum_value) * negative);
  }    
  return(random_vector);
}

// Función para verificar si un array está ordenado
bool vector_is_sorted(const vector<int>& array) {
  for (unsigned i = 1; i < array.size(); ++i) {
    if (array[i] < array[i - 1])  return false;
  }
  return true;
}

/**
 * @brief Displays the elements of a vector along with a title.
 * @param array The vector to be displayed.
 * @param title The title to be printed before the vector elements.
 */
void show_vector(const vector<int>& array, const string& title) {
  cout << title + ": ";  
  for (unsigned i = 0; i < array.size(); ++i) {
    cout << array[i];
    if (i < array.size() - 1) cout << ", ";
  }
  cout << endl;
}
