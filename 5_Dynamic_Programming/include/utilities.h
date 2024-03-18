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
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const string kInputFolderPath = "./input/";
const string kInputFileExtension = ".txt";

/**
 * @brief Checks if an element exists into a vector
 * @param array - vector to check
 * @param element - element to search
 * @return 'true' if exists
 */
template <typename T>
bool vector_contains(vector<T> array, const T& element);

/**
* @brief Prints a vector
* @param array
*/
template <typename T>
void show_vector(vector<T> array);

/**
 * @brief Concatenate the strings in a vector into a single string, separated by spaces.
 * @param vec The vector of strings to concatenate.
 * @return string The concatenated string.
 */
string concatenate_strings(const vector<string>& vec);

/**
 * @brief Remove specified subsequences from a string.
 * @param original The original string.
 * @param subsequences The subsequences to remove from the original string.
 * @return string The string with the specified subsequences removed.
 */
string remove_subsequences(const string& original, vector<string> subsequences);

#endif // UTILITIES_H_ 