/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Greesy TSP solver class definition.
 * 
 */
#ifndef GREEDY_TSP_H_
#define GREEDY_TSP_H_

#include "tsp.h"

class GreedyTSP: public TSP {
public:
  /**
   * @brief BruteForceTSP constructor
   * @param symetric_adjacency_list - 'true' if the graph is non directed
   */
  GreedyTSP(bool symetric_adjacency_list): TSP(symetric_adjacency_list) {}
  /**
   * @brief TSP solution using a greedy aproach 
   * @param start_node - starting node identifier
   * @return distance to go through all nodes and return to the starting point 
   */
  int Solve(const string& start_node) override;
};

#endif /* GREEDY_TSP_H_ */