/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 18 2024
 *
 * @brief Testing functions implementation. 
 */

#include "max_div_testing.h"

/**
 * @brief Test the performance of a Maximum Diversity algorithm using the given instance file.
 * @param maxdiv_algorithm Pointer to the MaximumDiversity algorithm instance.
 * @param filename Name of the instance file.
 * @param elements Number of elements as a string
 * @param dimension Dimension (K) of the elements as a string
 */
void test_algorithm(MaximumDiversity* maxdiv_algorithm, const string& filename, const string& elements,  const string& dimension) {
  maxdiv_algorithm->InitializeProblem(kInputFolderPath + "/" + filename + kInputFileExtension);
  auto start = Clock::now();  
  Solution solution = maxdiv_algorithm->Solve();
  //maxdiv_algorithm->GetProblem()->ShowInfo();
  auto stop = Clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  solution.Show("[" + filename + "]", true);
  
  cout << kFourSpaces + "CPU: " << duration.count() << " ms" << kFourSpaces;
  //cout << "m: " << machines << " n: " << tasks << endl;
}

/** 
 * @brief Execute MaximumDiversity algorithms and measure the time taken by each of them.
 * @param m_value - Size of the solution
 */
void test_maximum_diversity_algorithms(unsigned m_value) {
  vector<string> elements  = {"15", "20", "30"};
  vector<string> dimension = {"2",  "3"};
  pair<unsigned, unsigned> m_values(2, 5);
  
  //unsigned maximum_iterations = 50, candidate_list_size = 3, k_maximum = 2;
  vector<MaximumDiversity*> algorithms = {
    new GreedyMaxDiversity(),
    //new GraspMaxDiversity(m_value, maximum_iterations, candidate_list_size, true, 1),
    //new GvnsMaxDiversity(m_value, 10, candidate_list_size, k_maximum),    
  };

  for (const auto& algorithm : algorithms) {
    cout << "<<< " << algorithm->GetAlgorithmName() << " >>>\n"; 
    for (const string& d : dimension) {
      for (const string& e : elements) {     
        for (unsigned i = m_values.first; i <= m_values.second; ++i) {
          algorithm->SetSubsetSize(i);
          test_algorithm(algorithm, "max_div_" + e + "_" + d, e, d);
          cout << endl;
        }
        cout << endl;
      }
    }
  }  
}