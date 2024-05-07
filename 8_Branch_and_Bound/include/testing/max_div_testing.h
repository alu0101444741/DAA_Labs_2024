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
#include "grasp_maxdiv.h"
#include "tabu_maxdiv.h"
#include "bnb_maxdiv.h"

const string kInputFolderPath = "./input/";
const string kInputFileExtension = ".txt";

using TimePoint = std::chrono::system_clock::time_point;
using Clock = chrono::high_resolution_clock;

//const unsigned kMaximumExecutionTime = 300000000;
//const int kExecutionTimeCode = -3;

/** @brief Class to test algotithms behaviour and performance */
class Tester {
private:
  vector<MaximumDiversity*> algorithms_;
  vector<string> elements_, dimension_;
  vector<unsigned> m_values_, maximum_iterations_, candidate_list_sizes_;

public:
  /** @brief Constructor for the Tester class.  */
  Tester();

  /** 
   * @brief Execute MaximumDiversity algorithms and measure the time taken by each of them.
   * @param show_elements Flag to show the S set that contains all the elements 
   */
  void TestMaximumDiversityAlgorithms(bool show_elements = false);

private:
  /**
   * @brief Test the performance of a Maximum Diversity algorithm using the given instance file.
   * @param maxdiv_algorithm Pointer to the MaximumDiversity algorithm instance.
   * @param filename Name of the instance file.
   */
  void TestAlgorithm(MaximumDiversity* maxdiv_algorithm, const string& filename, unsigned iterations, unsigned candidate_list_size);

  /** @brief Print the S set that contains all the elements on the problem object. */
  void ShowElements(Problem* problem);
};
#endif // TEST_UTILITIES_H_