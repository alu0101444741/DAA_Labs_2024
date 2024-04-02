/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 1 2024
 *
 * @brief Testing functions implementation. 
 */

#include "pmsp_testing.h"

/**
 * @brief Test the performance of a PMSP algorithm using the given instance file and starting node.
 * @param pmsp_algorithm Pointer to the TSP algorithm instance.
 * @param filename Name of the instance file.
 */
void test_algorithm(PMSP* pmsp_algorithm, const string& filename, const string& tasks) {
  auto start = Clock::now();
  pmsp_algorithm->CreateFromFile(kInputFolderPath + tasks + "/" + filename + kInputFileExtension);
  vector<vector<Task*>> solution = pmsp_algorithm->Solve();
  auto stop = Clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  show_solution(solution, filename, false);
  cout << kFourSpaces + "CPU: " << duration.count() << " " << kMicro << "s" << endl;
}

/** @brief Execute PMSP algorithms and measure the time taken by each of them. */
void test_pmsp_algorithms() {
  unsigned maximum_iterations = 100;
  vector<string> machines = {"2", "4", "6", "8"};
  vector<string> tasks = {"40", "50", "60", "70"};
  vector<PMSP*> algorithms = {new GreedyPMSP(), new GraspPMSP(maximum_iterations)};
  for (const auto& algorithm : algorithms) {
    cout << "<<< " << algorithm->GetAlgorithmName() << " >>>\n";
    for (const string& m : machines) {
      for (const string& t : tasks) {            
        test_algorithm(algorithm, "I" + t + "j_" + m + "m_S1_1", t);
      }
      cout << endl;
    }
    cout << endl;
  }  
}