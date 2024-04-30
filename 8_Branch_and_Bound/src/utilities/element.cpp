/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Element class implementation.
 * 
 */

#include "../../include/utilities/element.h"

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