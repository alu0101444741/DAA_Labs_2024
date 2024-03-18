/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Greesy TSP solver class implementation.
 * 
 */

#include "greedy_tsp.h"

/**
 * @brief TSP solution using a greedy aproach 
 * @param start_node - starting node identifier
 * @return distance to go through all nodes and return to the starting point 
 */
int GreedyTSP::Solve(const string& start_node) {
  auto start = Clock::now();
  
  string current_node = start_node;
  vector<string> path;
  path.push_back(current_node);
  unsigned  counter = 0,
            sum = 0,
            node_to_include, index,
            size = node_names_.size();
  int minimum_distance = INT_MAX;
  
  // While still nodes to visit...
  while (counter < size - 1) {
    if (ExecutionTimeExceeded(start)) return kExecutionTimeCode; // <------------------- Time check

    index = GetIndexOfNode(current_node);
    // Search the smallest distance to a not visited node
    for (unsigned i = 0; i < size; ++ i) {
      bool vector_contains = (find(path.begin(), path.end(), node_names_[i]) != path.end()) ? true : false;
      if (!vector_contains && (adjacency_matrix_[index][i] < minimum_distance)) {
        node_to_include = i;
        minimum_distance = adjacency_matrix_[index][i];
      }
    }    
    current_node = node_names_[node_to_include];
    path.push_back(current_node);
    ++ counter;
    sum += minimum_distance;
    minimum_distance = INT_MAX;    
  }
  // Add the last (starting) node to the path
  index = GetIndexOfNode(current_node);
  for (unsigned i = 0; i < size; ++i) {
    if (ExecutionTimeExceeded(start)) return kExecutionTimeCode; // <------------------- Time check 
    if ((node_names_[i] == start_node) && (adjacency_matrix_[index][i] < minimum_distance)) {      
      node_to_include = i;
      minimum_distance = adjacency_matrix_[index][i];
    }
  }
  sum += minimum_distance;
  path.push_back(node_names_[node_to_include]);
  minimum_path_ = path;
  if (ExecutionTimeExceeded(start)) return kExecutionTimeCode; // <------------------- Time check 
  return(sum);
}