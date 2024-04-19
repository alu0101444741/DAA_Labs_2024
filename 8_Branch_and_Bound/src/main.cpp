/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 18 2024
 *
 * @brief Main program. Maximum Diversity. Approximation algorithms. Branch and Bound
 */

#ifndef MAIN_
#define MAIN_

#include "max_div_testing.h"

/** @brief Main function */
int main(int argc, char* argv[]) {

  unsigned m_value = 5;

  test_maximum_diversity_algorithms(m_value);

  //test_grasp_localsearch();
  //test_modificacion();

  return 0;
};

#endif // MAIN_