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
#ifndef MAX_DIV_UTILITIES_H_
#define MAX_DIV_UTILITIES_H_

#include <string>
#include <iostream>
#include <fstream>

#include "element.h"

const string kFourSpaces = "    ";
const string kMicro = "\u00B5";

/**
 * @brief Replace a value from a vector with another one. Will search for one of two given values and
 * replace it for the other one. 
 * @param indexes Array to be modified
 * @param first_value 
 * @param second_value 
 */
void replace_index(vector<unsigned>& indexes, unsigned first_value, unsigned second_value);

/**
 * @brief Validate an index against specified bounds.
 * @param index The index to validate.
 * @param maximum_index The maximum allowed index.
 * @param tag A string tag used in the error message to identify the context of the validation.
 * @param minimum_index (Optional) The minimum allowed index. Defaults to 0 if not specified.
 * @throws runtime_error if the index is out of range.
 */
void index_validation(unsigned index, unsigned maximum_index, const string& tag, unsigned minimum_index = 0);

/**
 * @brief Checks if an element exists into a vector
 * @param array - vector to check
 * @param element - element to search
 * @return 'true' if exists
 */
template <typename T>
bool vector_contains(vector<T> array, const T& element);

/**
* @brief Prints an integer vector
* @param array to be printed
*/
void show_vector(vector<int> array);

#endif // MAX_DIV_UTILITIES_H_ 