/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Testing functions definition.
 */
#ifndef TEST_UTILITIES_H_
#define TEST_UTILITIES_H_

#include "greedy_pmsp.h"
#include "gvns_pmsp.h"

const string kInputFolderPath = "./input/tasks_";
const string kInputFileExtension = ".txt";

using TimePoint = std::chrono::system_clock::time_point;
using Clock = chrono::high_resolution_clock;
const string kMicro = "\u00B5";


//const unsigned kMaximumExecutionTime = 300000000;
//const int kExecutionTimeCode = -3;

/**
 * @brief Test the performance of a PMSP algorithm using the given instance file and starting node.
 * @param tsp_algorithm Pointer to the TSP algorithm instance.
 * @param filename Name of the instance file.
 */
void test_algorithm(PMSP* tsp_algorithm, const string& filename, const string& tasks);

/** @brief Execute PMSP algorithms and measure the time taken by each of them. */
void test_pmsp_algorithms();

#endif // TEST_UTILITIES_H_