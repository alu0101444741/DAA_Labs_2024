/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 18 2024
 *
 * @brief Testing functions definition.
 */
#ifndef TEST_UTILITIES_H_
#define TEST_UTILITIES_H_

#include "greedy_maxdiv.h"
//#include "gvns_pmsp.h"

const string kInputFolderPath = "./input/";
const string kInputFileExtension = ".txt";

using TimePoint = std::chrono::system_clock::time_point;
using Clock = chrono::high_resolution_clock;
const string kMicro = "\u00B5";

//const unsigned kMaximumExecutionTime = 300000000;
//const int kExecutionTimeCode = -3;

/**
 * @brief Test the performance of a Maximum Diversity algorithm using the given instance file.
 * @param maxdiv_algorithm Pointer to the MaximumDiversity algorithm instance.
 * @param filename Name of the instance file.
 * @param elements Number of elements as a string
 * @param dimension Dimension (K) of the elements as a string
 */
void test_algorithm(MaximumDiversity* maxdiv_algorithm, const string& filename, const string& elements,  const string& dimension);

/** 
 * @brief Execute Maximum Diversity algorithms and measure the time taken by each of them.
 * @param m_value - Size of the solution
 */
void test_maximum_diversity_algorithms(unsigned m_value);

//void test_grasp_localsearch();

#endif // TEST_UTILITIES_H_