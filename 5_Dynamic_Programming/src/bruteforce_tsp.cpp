/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Brute force TSP solver class implementation.
 * 
 */

#include "bruteforce_tsp.h"

/**
 * @brief TSP solution using a brute force aproach 
 * @param start_node - starting node identifier
 * @return distance to go through all nodes and return to the starting point 
 */
int BruteForceTSP::Solve(const string& start_node) {
  auto start = Clock::now();

  if (start_node != node_names_[0]) SwapNodes(start_node, node_names_[0]);
  unsigned size = node_names_.size(),
                  minimum_sum = INT_MAX;

  vector<string> nodes, current_path;
  for(unsigned i = 0; i < size; ++i) {
    if(node_names_[i] != start_node) {
      nodes.push_back(node_names_[i]);
    }
  }
  // For all combinations of the remaining nodes...
  while(next_permutation(nodes.begin(), nodes.end())) {    
    if (ExecutionTimeExceeded(start)) return kExecutionTimeCode; // <------------------- Time check 

    unsigned path_weight = 0,
             current_node_index = GetIndexOfNode(start_node);
    current_path.resize(0);
    current_path.push_back(start_node);

    // Traverse through each node in the current permutation
    for (unsigned i = 0; i < nodes.size(); i++) {
      path_weight += adjacency_matrix_[current_node_index][GetIndexOfNode(nodes[i])];
      current_node_index = GetIndexOfNode(nodes[i]);
      current_path.push_back(nodes[i]);
    }
    path_weight += adjacency_matrix_[current_node_index][GetIndexOfNode(start_node)];
    current_path.push_back(start_node);
    if (path_weight < minimum_sum) {
      minimum_sum = path_weight;
      minimum_path_ = current_path;
    }
  }
  //this->minimum_path = minimum_path;
  return (minimum_sum);
}

/**
 * @brief Change the positions of two nodes in the adjacency matrix. 
 * @param first_node 
 * @param second_node 
 */
void BruteForceTSP::SwapNodes(const string& first_node, const string& second_node) {
  unsigned  first_node_index = GetIndexOfNode(first_node),
            second_node_index = GetIndexOfNode(first_node);
  string swap_identifier = node_names_[first_node_index];
  node_names_[first_node_index] = node_names_[second_node_index];
  node_names_[second_node_index] = swap_identifier;
  adjacency_matrix_.resize(0);
  CreateAdjacencyMatrix();
}