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
#include <vector>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

const string kFourSpaces = "    ";
const string kMicro = "\u00B5";

/** @brief A class representing an element with values in multiple dimensions. */
class Element {
private:
  unsigned index_;
  vector<float> values_;
public:
  /** @brief Default constructor. */
  Element(){}

  /**
   * @brief Constructor to initialize the element with a specified dimension.
   * @param index The index of the element on the list
   * @param dimension The dimensionality of the element.
   */
  Element(unsigned index, unsigned dimension) : index_(index), values_(vector<float>(dimension, 0.0)) {}

  /**
   * @brief Constructor to initialize the element with specified values.
   * @param index The index of the element on the list
   * @param values Vector containing the values of the element in each dimension.
   */
  Element(unsigned index, vector<float> values) : index_(index), values_(values) {} 

  /**
   * @brief Calculate the distance to another element.
   * @param element The element to calculate the distance to.
   * @return The Euclidean distance between this element and the specified element.
   */
  float DistanceTo(const Element& element) const;

  /**
   * @brief Get the value of a specific dimension.
   * @param dimension_index The index of the dimension.
   * @return The value of the specified dimension.
   * @throw runtime_error if the dimension index is out of range.
   */
  float GetDimensionValue(unsigned dimension_index) const;

  /**
   * @brief Overloaded equality operator to compare two elements for equality.
   * @param other The element to compare with.
   * @return True if the elements are equal, false otherwise.
   */
  bool operator == (const Element& other) const { return index_ == other.index_; }

  /**
   * @brief Get the dimensionality of the element.
   * @return The number of dimensions of the element.
   */
  unsigned GetDimension() const { return values_.size(); }

  /**
   * @brief Get the index of the element.
   * @return Index on the list.
   */
  unsigned GetIndex() const { return index_; }

  /** @brief Display the values of the element. */
  void Show() const;
};

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