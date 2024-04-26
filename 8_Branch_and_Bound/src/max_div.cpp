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
 * @brief Build the initial solution for the Maximum Diversity algorithms.
 * 
 * @param problem - Problem information
 * @param candidate_list_size - Maximum candidate list size
 */
Solution MaximumDiversity::ConstructInitialSolution(Problem* problem, unsigned candidate_list_size) {
  Solution current_solution(problem);
  vector<Element> remaining_elements(problem->GetElements());
  Element current_center = CalculateGravityCenter(GetElementIndexes(remaining_elements));

  while(current_solution.GetSolutionSize() < m_value_) {
    // Creo la lista de candidatos con los N más alejados
    vector<Element> candidate_list = GetTheNFurthestElements(candidate_list_size, remaining_elements, current_center);

    // Elijo uno aleatorio, lo incluyo en la solucion y lo elimino de los restantes
    Element element_to_add = SelectRandomElement(candidate_list);

    current_solution.AddElement(element_to_add.GetIndex());

    EraseElement(remaining_elements, element_to_add);

    // Calculo el centro
    current_center = CalculateGravityCenter(current_solution.GetElements());
  } 
  return current_solution;
}

/**
 * @brief Calculate the gravity center of a set of elements.
 * @param elements A vector of Element objects representing the elements.
 * @return An Element object representing the gravity center.
 */
Element MaximumDiversity::CalculateGravityCenter(const vector<unsigned>& elements_indexes) const {
  unsigned dimension = problem_->GetDimension();
  vector<float> center(dimension, 0);

  for (const unsigned& element_index : elements_indexes) { // Get the sum of each feature
    for (unsigned i = 0; i < dimension; ++i) {
      center[i] += problem_->GetElementOnIndex(element_index).GetDimensionValue(i);
    }
  }
  for (float& value : center) { // Divide each feature by the dimension
    value /= dimension;
  }
  return Element(0, center);
}

/**
 * @brief Get the indexes of every Element in a vector. 
 * @param elements A vector of Element objects.
 * @return A vector containing the indexes of elements in the same order as the input vector.
 */
vector<unsigned> MaximumDiversity::GetElementIndexes(const vector<Element>& elements) const {
  unsigned size = elements.size();
  vector<unsigned> indexes(size, 0);
  for (unsigned i = 0; i < size; ++i) indexes[i] = elements[i].GetIndex();
  return indexes;
}

/**
 * @brief Get the furthest element from another Element.
 * @param elements A vector of Element objects representing the elements.
 * @param center An Element object representing the centroid element.
 * @return The furthest Element object from the given Element.
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
 * @brief Get the N furthest elements from a given center Element.
 * @param number_of_elements Amount of elements to get
 * @param elements A vector of Element objects representing the elements.
 * @param center An Element object representing the center element.
 * @return The furthest Element object from the center.
 */
vector<Element> MaximumDiversity::GetTheNFurthestElements(unsigned number_of_elements, const vector<Element>& elements, const Element& center) const {
  vector<Element> furthest_elements;
  vector<Element> current_elements = elements;
  for (unsigned i = 0; i < number_of_elements; ++i) {
    Element current_furthest_element = GetFurthestElement(current_elements, center);
    EraseElement(current_elements, current_furthest_element);
    furthest_elements.push_back(current_furthest_element);
  }
  return furthest_elements;
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