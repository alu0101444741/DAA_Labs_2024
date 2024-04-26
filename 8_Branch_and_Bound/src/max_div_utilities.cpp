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
 * @brief Calculate the distance to another element.
 * @param element The element to calculate the distance to.
 * @return The Euclidean distance between this element and the specified element.
 */
float Element::DistanceTo(const Element& element) const {
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
float Element::GetDimensionValue(unsigned dimension_index) const {
  if ((dimension_index < 0) || (dimension_index >= values_.size())) throw runtime_error("[Element] Dimension index out of range");
  return values_[dimension_index];
}

/** @brief Display the values of the element. */
void Element::Show() const {
  unsigned size = values_.size();
  cout << "[" << index_ << "] {";
  for (unsigned i = 0; i < size; ++i) {
    cout << values_[i];
    if (i < (size - 1)) cout << ", ";
  } cout << "}";
}

/**
 * @brief Validate an index against specified bounds.
 * @param index The index to validate.
 * @param maximum_index The maximum allowed index.
 * @param tag A string tag used in the error message to identify the context of the validation.
 * @param minimum_index (Optional) The minimum allowed index. Defaults to 0 if not specified.
 * @throws runtime_error if the index is out of range.
 */
void index_validation(unsigned index, unsigned maximum_index, const string& tag, unsigned minimum_index) {
  if (index < minimum_index || index >= maximum_index) throw runtime_error("[" + tag +"] Index out of range");
}

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