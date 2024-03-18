/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Main program. TSP. Dynamic Programming.
 * 
 */

#ifndef MAIN_
#define MAIN_

#include "test_utilities.h"

/** @brief Main function */
int main(int argc, char* argv[]) {  
  vector<string> algorithm_names = {"Voraz", "FB", "PD"};
  test_tsp_algorithms("A", algorithm_names, true);

  // Modificacion
  /*cout << endl << "<Non-symetric adjacency list>\n";
  vector<string> files_mod;
  files_mod.push_back("./input/example_mod.txt");
  TestTSPAlgorithmsNonSymetric("A");*/

  return 0;
};

#endif // MAIN_