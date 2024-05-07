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
 * @param candidate_list_size - Maximum candidate list size
 */
Solution MaximumDiversity::ConstructInitialSolution(unsigned candidate_list_size) {
  Solution current_solution(problem_);
  vector<unsigned> remaining_elements = GetElementIndexes(problem_->GetElements());
  Element current_center = CalculateGravityCenter(remaining_elements);

  while(current_solution.GetSolutionSize() < m_value_) {
    // Creo la lista de candidatos con los N más alejados
    vector<unsigned> candidate_list = GetTheNFurthestElements(candidate_list_size, remaining_elements, current_center);

    // Elijo uno aleatorio, lo incluyo en la solucion y lo elimino de los restantes
    unsigned element_to_add = SelectRandomElement(candidate_list);

    current_solution.AddElement(element_to_add);

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
  for (unsigned i = 0; i < dimension; ++i) { // Divide each feature by the dimension
    center[i] /= dimension;
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
 * @brief Get the elements indexes that are not included in a given Solution 
 * @param solution 
 * @return array of indexes
 */
vector<unsigned> MaximumDiversity::GetRemainingElements(const Solution& solution) const {
  vector<unsigned> remaining_elements;
  for (unsigned i = 0; i < problem_->GetElements().size(); ++i) {
    if (!solution.HasElement(i)) {
      remaining_elements.push_back(i);
    }
  }
  return remaining_elements;
}

/**
 * @brief Get the index of furthest element from another Element.
 * @param elements Indexes of Element objects representing the elements.
 * @param center An Element object representing the centroid element.
 * @return Index of the furthest Element object from the given Element.
 */
unsigned MaximumDiversity::GetFurthestElement(const vector<unsigned>& elements, const Element& center) const {
  unsigned furthest_element = elements[0];
  float highest_distance = 0;
  for (const unsigned& e : elements) {
    float current_distance = problem_->GetElements()[e].DistanceTo(center);
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
 * @param elements A vector of Element indexes representing the elements.
 * @param center An Element object representing the center element.
 * @return Indexes of the furthests Element objects from the center.
 */
vector<unsigned> MaximumDiversity::GetTheNFurthestElements(unsigned number_of_elements, const vector<unsigned>& elements, const Element& center) const {
  vector<unsigned> furthest_elements;
  vector<unsigned> current_elements = elements;
  for (unsigned i = 0; i < number_of_elements; ++i) {
    unsigned current_furthest_element = GetFurthestElement(current_elements, center);
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
void MaximumDiversity::EraseElement(vector<unsigned>& elements, unsigned element_to_erase) const {
  auto it = find(elements.begin(), elements.end(), element_to_erase);

  //cout << "  [EraseElement] Deleting " << element_to_erase << " as " << *it <<endl;
  //cout << "    Elements { "; for (const unsigned& e : elements) cout << e << ", ";
  //cout <<" } to { ";

  if (it != elements.end()) elements.erase(it);

  //for (const unsigned& e : elements) cout << e << ", ";
  //cout <<" }\n";
}