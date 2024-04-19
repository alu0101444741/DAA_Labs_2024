/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Dynamic programming TSP solver class definition.
 * 
 */
#ifndef DYNAMIC_PROGRAMMING_TSP_H_
#define DYNAMIC_PROGRAMMING_TSP_H_

#include "tsp.h"

class DynamicProgrammingTSP: public TSP {
private:
  unsigned recursive_calls_;
  int kVisitedAll_;
  vector<vector<int>>dynamic_programming_table_;
  vector<vector<vector<unsigned>>> path_;
  TimePoint execution_start_;

public:
  /**
   * @brief DynamicProgrammingTSP constructor
   * @param symetric_adjacency_list - 'true' if the graph is non directed
   */
  DynamicProgrammingTSP(bool symetric_adjacency_list) : TSP(symetric_adjacency_list) { }

  /**
   * @brief TSP solution using dynamic programming.
   * @param start_node - starting node identifier
   * @return distance to go through all nodes and return to the starting point 
   */
  int Solve(const string& start_node) override;

private:
  /**
   * @brief TSP solution using dynamic programming.
   * @param start_node - starting node identifier
   * @return distance to go through all nodes and return to the starting point 
   */
  pair<int, vector<unsigned>> TSPRecursiveMethod(int mask, unsigned current_position, unsigned start_index);

  /**
   * @brief Change the positions of two nodes in the adjacency matrix. 
   * @param first_node 
   * @param second_node 
   */
  void SwapNodes(const string& first_node, const string& second_node);

  /**
   * @brief Create the path followed by the Held-Karp TSP algorithm 
   * @param minimum_distances 
   * @param start_node 
   * @return path as vector of identifiers
   */
  vector<string> GetMinimumPath();
};

#endif /* DYNAMIC_PROGRAMMING_TSP_H_ */