/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief MaximumDiversity functions.
 */
#include "max_div.h"

/**
 * @brief Calculate the gravity center of a set of elements.
 * @param elements A vector of Element objects representing the elements.
 * @return An Element object representing the gravity center.
 */
Element MaximumDiversity::CalculateGravityCenter(const vector<Element>& elements) const {
  unsigned dimension = elements[0].GetDimension();
  vector<float> center(dimension, 0);
  
  for (const Element& element : elements) { // Get the sum of each feature
    for (unsigned i = 0; i < dimension; ++i) {
      center[i] += element.GetDimensionValue(i);
    }
  }
  for (float& value : center) { // Divide each feature by the dimension
    value /= dimension;
  }
  return Element(center);
}

/**
 * @brief Get the furthest element from a given center element.
 * @param elements A vector of Element objects representing the elements.
 * @param center An Element object representing the center element.
 * @return The furthest Element object from the center.
 */
Element MaximumDiversity::GetFurthestElement(const vector<Element>& elements, const Element& center) const {
  Element furthest_element = elements[0];
  float highest_distance = 0;
  for (const Element& e : elements) {
    float current_distance = e.DistanceTo(center);
    if (current_distance > highest_distance) {
      furthest_element = e;
      highest_distance = current_distance;
    }
  }
  return furthest_element;
}

/**
 * @brief Erase a specific element from a vector of elements.
 * @param elements A reference to a vector of Element objects.
 * @param element_to_erase The Element object to be erased from the vector.
 */
void MaximumDiversity::EraseElement(vector<Element>& elements, const Element& element_to_erase) const {
  auto it = find(elements.begin(), elements.end(), element_to_erase);
  if (it != elements.end()) elements.erase(it);
}