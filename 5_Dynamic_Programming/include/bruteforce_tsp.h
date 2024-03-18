/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Brute force TSP solver class definition.
 * 
 */
#ifndef BRUTEFORCE_TSP_H_
#define BRUTEFORCE_TSP_H_

#include "tsp.h"

class BruteForceTSP: public TSP {
public:
  /**
   * @brief BruteForceTSP constructor
   * @param symetric_adjacency_list - 'true' if the graph is non directed
   */
  BruteForceTSP(bool symetric_adjacency_list): TSP(symetric_adjacency_list) {}

  /**
   * @brief TSP solution using a brute force aproach 
   * @param start_node - starting node identifier
   * @return distance to go through all nodes and return to the starting point 
   */
  int Solve(const string& start_node) override;

private:
  /**
   * @brief Change the positions of two nodes in the adjacency matrix. 
   * @param first_node 
   * @param second_node 
   */
  void SwapNodes(const string& first_node, const string& second_node);
};

#endif /* BRUTEFORCE_TSP_H_ */