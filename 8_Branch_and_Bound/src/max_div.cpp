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
  vector<Element> problem_elements(problem->GetElements());

  while(current_solution.GetSolutionSize() < m_value_) {
    // Calculo el centro
    Element current_center = CalculateGravityCenter(problem_elements);

    // Creo la lista de candidatos con los N más alejados
    vector<Element> candidate_list = GetTheNFurthestElements(candidate_list_size, problem_elements, current_center);

    // Elijo uno aleatorio, lo incluyo en la solucion y lo elimino de los restantes
    Element element_to_add = SelectRandomElement(candidate_list);
    current_solution.AddElement(element_to_add);

    EraseElement(problem_elements, element_to_add);
  } 
  return current_solution;
}

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
 * @brief Get the N furthest elements from a given center element.
 * @param number_of_elements Amount of elements to get
 * @param elements A vector of Element objects representing the elements.
 * @param center An Element object representing the center element.
 * @return The furthest Element object from the center.
 */
vector<Element> MaximumDiversity::GetTheNFurthestElements(unsigned number_of_elements, const vector<Element>& elements, const Element& center) const {
  vector<Element> furthest_elements;
  vector<Element> current_elements = problem_->GetElements();
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