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

/** @brief A class representing an element with values in multiple dimensions. */
class Element {
private:
  vector<float> values_;
public:
  /** @brief Default constructor. */
  Element(){}

  /**
   * @brief Constructor to initialize the element with a specified dimension.
   * @param dimension The dimensionality of the element.
   */
  Element(unsigned dimension) { values_ = vector<float>(dimension, 0.0); }

  /**
   * @brief Constructor to initialize the element with specified values.
   * @param values Vector containing the values of the element in each dimension.
   */
  Element(vector<float> values) : values_(values) {} 

  /**
   * @brief Calculate the distance to another element.
   * @param element The element to calculate the distance to.
   * @return The Euclidean distance between this element and the specified element.
   */
  float DistanceTo(const Element& element) const {
    float distance = 0.0;
    for (unsigned i = 0; i < values_.size(); ++i) {
      distance += ((values_[i] - element.values_[i]) * (values_[i] - element.values_[i]));
    }
    return sqrt(distance);
  }

  /**
   * @brief Get the value of a specific dimension.
   * @param dimension_index The index of the dimension.
   * @return The value of the specified dimension.
   * @throw runtime_error if the dimension index is out of range.
   */
  float GetDimensionValue(unsigned dimension_index) const {
    if ((dimension_index < 0) || (dimension_index >= values_.size())) throw runtime_error("[Element] Dimension index out of range");
    return values_[dimension_index];
  }

  /**
   * @brief Overloaded equality operator to compare two elements for equality.
   * @param other The element to compare with.
   * @return True if the elements are equal, false otherwise.
   */
  bool operator==(const Element& other) const {
    return values_ == other.values_;
  }

  /**
   * @brief Get the dimensionality of the element.
   * @return The number of dimensions of the element.
   */
  unsigned GetDimension() const { return values_.size(); }

  /** @brief Display the values of the element. */
  void Show() const {
    unsigned size = values_.size();
    for (unsigned i = 0; i < size; ++i) {
      cout << values_[i];
      if (i < (size - 1)) cout << ", ";
    }
  }
};

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