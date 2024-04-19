/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Utility functions.
 * 
 */

#include "../include/utilities.h"


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
* @brief Prints a vector
* @param array
*/
template <typename T>
void show_vector(vector<T> array) {
  unsigned size = array.size();
  for (unsigned i = 0; i < size; ++i){
    cout << array[i];
    if (i < (size - 1)) cout << ", ";
  }
  //cout << endl;
}

/**
 * @brief Concatenate the strings in a vector into a single string, separated by spaces.
 * @param vec The vector of strings to concatenate.
 * @return string The concatenated string.
 */
string concatenate_strings(const vector<string>& vec) {
  string result;
  for (const string& str : vec)  result += str + " ";
  return result;
}

/**
 * @brief Remove specified subsequences from a string.
 * @param original The original string.
 * @param subsequences The subsequences to remove from the original string.
 * @return string The string with the specified subsequences removed.
 */
string remove_subsequences(const string& original, vector<string> subsequences) {
  string new_string = original;
  // Buscar la subsecuencia en el string original
  for (const string& sub : subsequences) {
    size_t pos = new_string.find(sub);
    while (pos != string::npos) {
      new_string.erase(pos, sub.length());
      pos = new_string.find(sub, pos);
    }
  }
  return new_string;
}