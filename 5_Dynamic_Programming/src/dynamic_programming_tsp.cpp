/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Held-Karp TSP solver class implementation.
 * 
 */

#include "dynamic_programming_tsp.h"

/**
 * @brief TSP solution using dynamic programming.
 * @param start_node - starting node identifier
 * @return distance to go through all nodes and return to the starting point 
 */
int DynamicProgrammingTSP::Solve(const string& start_node) {
  execution_start_ = std::chrono::high_resolution_clock::now();
  
  unsigned nodes_amount = adjacency_matrix_.size();  
  kVisitedAll_ = (1 << nodes_amount) - 1;
  dynamic_programming_table_ = vector<vector<int>>(pow(2, nodes_amount), vector<int>(nodes_amount, -1)); // Dynamic Programming Table 2^N * N
  path_ = vector<vector<vector<unsigned>>>(pow(2, nodes_amount), vector<vector<unsigned>>(nodes_amount));

  unsigned start_index = GetIndexOfNode(start_node);
  pair<int, vector<unsigned>> minimum_path = TSPRecursiveMethod(0, start_index, start_index);

  int minimum_cost = minimum_path.first;
  for (const unsigned& p : minimum_path.second) minimum_path_.push_back(node_names_[p]);

  return minimum_cost;
}

/**
 * @brief Perform dynamic programming based Traveling Salesman Problem (TSP) solution recursively.
 * @param mask The bitmask representing visited nodes.
 * @param current_position The current position in the path.
 * @param start_index The starting index of the path.
 * @return A pair containing the minimum cost and the path traversed.
 */
pair<int, vector<unsigned>> DynamicProgrammingTSP::TSPRecursiveMethod(int mask, unsigned current_position, unsigned start_index) {
  if (ExecutionTimeExceeded(execution_start_)) return {kExecutionTimeCode, vector<unsigned>()}; // <------------------- Time check 

  if (mask == kVisitedAll_) {
    return {adjacency_matrix_[current_position][start_index], {start_index}}; // Cost and path to the starting node
  }

  if (dynamic_programming_table_[mask][current_position] != -1) {
    return {dynamic_programming_table_[mask][current_position], path_[mask][current_position]}; // Previously store cost and path
  }
  int minimum_cost = INT_MAX;
  vector<unsigned> min_path;

  for (unsigned i = 0; i < adjacency_matrix_.size(); ++i) {
    if ((mask & (1 << i)) == 0) {
      auto [subproblem_cost, subproblem_path] = TSPRecursiveMethod(mask | (1 << i), i, start_index);
      int new_ans = adjacency_matrix_[current_position][i] + subproblem_cost;
      
      if (new_ans < minimum_cost) {
        minimum_cost = new_ans;
        min_path = subproblem_path;
        min_path.push_back(i); // Add current node to the minimum path
      }
    }
  }
  dynamic_programming_table_[mask][current_position] = minimum_cost;
  path_[mask][current_position] = min_path;

  return {minimum_cost, min_path};
}

/**
 * @brief Change the positions of two nodes in the adjacency matrix. 
 * @param first_node 
 * @param second_node 
 */
void DynamicProgrammingTSP::SwapNodes(const string& first_node, const string& second_node) {
  unsigned  first_node_index = GetIndexOfNode(first_node),
            second_node_index = GetIndexOfNode(second_node);
  string swap_identifier = node_names_[first_node_index];
  node_names_[first_node_index] = node_names_[second_node_index];
  node_names_[second_node_index] = swap_identifier;
  adjacency_matrix_.resize(0);
  CreateAdjacencyMatrix();
}

template <typename T>
void show_vector(vector<T> array) {
  unsigned size = array.size();
  for (unsigned i = 0; i < size; ++i){
    cout << array[i];
    if (i < (size - 1)) cout << ", ";
  }
  //cout << endl;
}