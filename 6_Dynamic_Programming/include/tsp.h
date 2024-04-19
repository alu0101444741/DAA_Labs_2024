/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief TSP interface definition.
 * 
 */

#ifndef TSP_H_
#define TSP_H_

#include <bits/stdc++.h>
#include <algorithm>
#include <sstream>
#include "utilities.h"

using namespace std;
using TimePoint = std::chrono::system_clock::time_point;
using Clock = chrono::high_resolution_clock;

const unsigned kMaximumExecutionTime = 300000000;
const int kExecutionTimeCode = -3;

template <typename T>
void show_vector(vector<T> array);

class TSP {
protected:
  vector<string> node_names_, minimum_path_;
  vector<pair<pair<string, string>, int>> distances_;
  vector<vector<int>> adjacency_matrix_;
  bool symetric_adjacency_list_;

public:

  /**
   * @brief Constructor for the Traveling Salesman Problem (TSP) solver.
   * @param symetric_adjacency_list Indicates whether the adjacency list is symmetric.
   */
  TSP(bool symetric_adjacency_list) : symetric_adjacency_list_(symetric_adjacency_list) {}

  /**
   * @brief Solve the Traveling Salesman Problem (TSP) starting from a given node.
   * @param start_node The starting node for the TSP.
   * @return The minimum cost of the TSP solution.
   */
  virtual int Solve(const string& start_node) = 0;

  /**
   * @brief Create the tree from a 'txt' file. 
   * @param filename - name/path of the file
   */
  void CreateFromFile(const string& filename);
  
  /** @brief Print the stored graph. */
  void ShowGraph();

  /** @brief Print the adjacency matrix. */
  void ShowAdjacencyMatrix();


  /**
   * @brief Getter method the minimum path.
   * @returns minimum path
   */
  vector<string> GetMinimumPath() { return minimum_path_; }

protected:
  /** @brief Create the adjacency matrix from the stored node data. */
  void CreateAdjacencyMatrix();

  /**
   * @brief Find the distance between two given nodes
   * @param start_node
   * @param end_node
   * @return distance between the nodes
   */
  unsigned DistanceBetweenNodes(const string& start_node, const string& end_node);

  /**
   * @brief Get the index of a node by it identifier 
   * @param node - node identifier
   * @return index
   */
  unsigned GetIndexOfNode(const string& node);

  /**
 * @brief Check if the execution time has exceeded the maximum allowed time.
 * @param start The start time of the execution.
 * @return True if the execution time has exceeded the maximum allowed time, false otherwise.
 */
  bool ExecutionTimeExceeded(const TimePoint& start);
};
#endif // TSP_H_