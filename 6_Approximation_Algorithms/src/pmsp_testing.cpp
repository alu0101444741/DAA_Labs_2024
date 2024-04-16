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
  pmsp_algorithm->InitializeProblem(kInputFolderPath + tasks + "/" + filename + kInputFileExtension);
  Solution solution = pmsp_algorithm->Solve();
  auto stop = Clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  solution.Show("[" + filename + "]");
  
  cout << kFourSpaces + "CPU: " << duration.count() / 1000 << "ms" << " Avg. LocalSearch improvement:" <<  << endl;
  //cout << kFourSpaces + "CPU: " << duration.count() << " " << kMicro << "s" << endl; // Microseconds

  //for (const auto& a : solution) { cout << " " << a[a.size() - 1]->time_ << " vs"; } cout << endl; // DEBUG
}

/** @brief Execute PMSP algorithms and measure the time taken by each of them. */
void test_pmsp_algorithms() {
  vector<string> machines = { "2",  "4",  /*"6",  "8" */};
  vector<string> tasks    = { "40", "50", /*"60", "70"*/};
  unsigned maximum_iterations = 50, candidate_list_size = 8;
  vector<PMSP*> algorithms = {
    //new GreedyPMSP(),
    new GraspPMSP(maximum_iterations, candidate_list_size, true, 1),
    //new GvnsPMSP(10, candidate_list_size)
  };

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

void test_grasp_localsearch() {
  vector<string> local_search_names = {"InsertionIntra", "SwapIntra", "InsertionInter", "SwapInter"};
  vector<string> machines = { "2",  "4",  "6",/*  "8" */};
  vector<string> tasks    = { "40", "50", "60",/* "70"*/};
  unsigned maximum_iterations = 50, candidate_list_size = 8;
  vector<PMSP*> algorithms = {
    new GraspPMSP(maximum_iterations, candidate_list_size, true, 1),
    new GraspPMSP(maximum_iterations, candidate_list_size, true, 2),
    new GraspPMSP(maximum_iterations, candidate_list_size, true, 3),
    new GraspPMSP(maximum_iterations, candidate_list_size, true, 4)
  };

  for (const string& m : machines) {
    for (const string& t : tasks) { 
      string filename = "I" + t + "j_" + m + "m_S1_1";
      cout << "[" + filename + "]" << endl;
      for (unsigned i = 0; i < algorithms.size(); ++i) {
        cout << "<" << local_search_names[i] << ">";
        test_algorithm(algorithms[i], filename, t);
      }      
    }
    cout << endl;
  }    
}