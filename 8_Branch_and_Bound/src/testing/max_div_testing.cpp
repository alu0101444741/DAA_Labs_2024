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
#include "../../include/testing/max_div_testing.h"

/** @brief Constructor for the Tester class.  */
Tester::Tester() {  
  elements_  = vector<string>{/*"15", "20",*/ "30"};
  dimension_ = vector<string>{/*"2",*/  "3"}; 
  m_values_ = vector<unsigned>{2, 3, 4, 5};   
  maximum_iterations_ = vector<unsigned>{10, 20};
  candidate_list_sizes_ = vector<unsigned>{2, 3};

  algorithms_ = {
    //new GreedyMaxDiversity(),
    //new GreedyMaxDiversity(true),
    //new GraspMaxDiversity(50, 3),
    new TabuMaxDiversity(50, 3),    
  };
}

/** @brief Execute MaximumDiversity algorithms and measure the time taken by each of them. */
void Tester::TestMaximumDiversityAlgorithms(bool show_elements) {
  for (const auto& algorithm : algorithms_) {
    cout << "\t\t" << "----------------------------------------------" << endl;
    cout << "\t\t\t" << algorithm->GetAlgorithmName() << endl;
    cout << "\t\t" << "----------------------------------------------" << endl;
    for (const string& d : dimension_) {
      for (const string& e : elements_) {
        string filename = "max_div_" + e + "_" + d;
        Problem* problem = new Problem();
        problem->CreateFromFile(kInputFolderPath + ("max_div_" + e + "_" + d) + kInputFileExtension);
        algorithm->SetProblem(problem);

        if (show_elements) ShowElements(problem);

        bool is_greedy_algorithm = (algorithm->GetAlgorithmName().find("Greedy") != std::string::npos);

        for (const unsigned& m : m_values_) {
          algorithm->SetSubsetSize(m);
          
          // Check if the algorithm is Greedy to shrink the output table
          if (is_greedy_algorithm) {
            TestAlgorithm(algorithm, filename, 1, 1);
            cout << endl; 
            continue;
          }

          for (const unsigned& iterations : maximum_iterations_) {
            algorithm->SetMaximumIterations(iterations);
            for (const unsigned& candidates : candidate_list_sizes_) {
              TestAlgorithm(algorithm, filename, iterations, candidates);
              cout << endl;          
            }           
          }            
        }                
        cout << "|---------|------|----|---|---|-----|---|" << endl; // Markdown divisor
      }
    }
  }
}

/**
 * @brief Test the performance of a Maximum Diversity algorithm using the given instance file.
 * @param maxdiv_algorithm Pointer to the MaximumDiversity algorithm instance.
 * @param filename Name of the instance file.
 */
void Tester::TestAlgorithm(MaximumDiversity* maxdiv_algorithm, const string& filename, unsigned iterations, unsigned candidate_list_size) {
  //maxdiv_algorithm->InitializeProblem(kInputFolderPath + "/" + filename + kInputFileExtension);
  auto start = Clock::now();
  Solution solution = maxdiv_algorithm->Solve();
  //maxdiv_algorithm->GetProblem()->ShowInfo();
  auto stop = Clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  solution.ShowMarkdown(
    "[" + filename + "]",
    to_string(duration.count()),
    iterations,
    candidate_list_size,
    true
  );
}

/** @brief Print the S set that contains all the elements on the problem object. */
void Tester::ShowElements(Problem* problem) {
  cout << "S = {\t";
  vector<Element> elements = problem->GetElements();
  for (unsigned i = 0; i < elements.size(); ++i) {
    if (i != 0 && i % 5 == 0) cout << " <br>\n&emsp;\t";
    elements[i].Show();
    if (i < (elements.size() - 1)) cout << ", ";           
  } cout << "<br>" << endl << "&emsp; } <br> \n";
}