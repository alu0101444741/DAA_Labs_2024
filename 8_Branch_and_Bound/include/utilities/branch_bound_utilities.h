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

#include "problem.h"
#include "max_div_utilities.h"

struct Node {
  vector<unsigned> subset; // Conjunto de índices de puntos seleccionados
  float lb, ub; // Límite inferior y superior de la solución que representa
};

// Función para obtener las distancias desde v hasta el resto de elementos. Orden descendente.
vector<float> get_sorted_distances(Problem* problem, unsigned v);

// Función para calcular dmin(v)
float calculate_dmin(unsigned m_value, unsigned element_index, const vector<float>& sorted_distances);

// Función para calcular dmax(v)
float calculate_dmax(unsigned m_value, unsigned element_index, const vector<float>& sorted_distances);

// Función para obtener los elementos no seleccionados
vector<unsigned> get_unselected(const vector<unsigned>& selected, const vector<unsigned>& all_elements);

// Función para obtener z1 + UB_23
float get_upper_bound(Problem* problem, const vector<unsigned>& selected, const vector<unsigned>& unselected);