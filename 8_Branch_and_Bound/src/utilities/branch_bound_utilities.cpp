/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: May 4 2024
 *
 * @brief Branch and Bound utility functions.
 * 
 */

#include "../../include/utilities/branch_bound_utilities.h"

// Función para obtener las distancias desde v hasta el resto de elementos. Orden descendente.
vector<float> get_sorted_distances(Problem* problem, unsigned v) {
  vector<float> sorted_distances;
  for (const Element& e : problem->GetElements()) {
    sorted_distances.push_back(problem->GetDistance(v, e.GetIndex()));
  }
  sort(sorted_distances.begin(), sorted_distances.end(), greater<float>());
  return sorted_distances;
}

// Función para calcular dmin(v)
float calculate_dmin(unsigned m_value, unsigned element_index, const vector<float>& sorted_distances) {
  unsigned n = sorted_distances.size();
  float dmin = 0.0;    
  // Calcular dmin(v)
  for (unsigned i = 0; i < m_value; ++i) {
    dmin += sorted_distances[n - i - 1];
  }
  return 0.5 * dmin;
}

// Función para calcular dmax(v)
float calculate_dmax(unsigned m_value, unsigned element_index, const vector<float>& sorted_distances) {
  //unsigned n = sorted_distances.size();
  float dmax = 0.0;    
  // Calcular dmax(v)
  for (unsigned i = 0; i < m_value; ++i) {
    dmax += sorted_distances[i];
  }
  return 0.5 * dmax;
}

// Función para obtener z1 + UB_23
float get_upper_bound(Problem* problem, const vector<unsigned>& selected, const vector<unsigned>& unselected) {
  float upper_bound = 0.0;
  // Calculate z1. Sum of each pair of elements in selected
  for (unsigned i = 0; i < selected.size(); ++i) {
    for (unsigned j = i + 1; j < selected.size(); ++j) {
      upper_bound += (problem->GetDistance(selected[i], selected[j]));
    }
  }
  // Calculate UB_23
  // ...

  return upper_bound;
}

// Función para obtener la suma de las distancias desde un elemento hacia el resto
float get_sum_of_distances(Problem* problem, unsigned element) {
  float sum = 0.0;
  for (const Element& e : problem->GetElements()) {
    sum += problem->GetDistance(element, e.GetIndex());
  }
  return sum;
}