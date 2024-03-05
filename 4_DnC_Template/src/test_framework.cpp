/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief Functions to test the Template Framework. (Implementation)
 */

#include "test_framework.h"

/**
* @brief Execute Divide and Conquer algorithms on a given amount of arrays.
* These arrays will be sized from 2 to a given size and will contain integer numbers only.
* @param test_amount - how many arrays will be sorted
* @param minimum_size - minimum vector size to test
* @param maximum_size - maximum vector size to test
*/
void sort_tests(unsigned test_amount, unsigned minimum_size, unsigned maximum_size) {
  DnCFramework* framework = new DnCFramework();
  vector<int> random_vector;
  for (unsigned size = minimum_size; size <= maximum_size; ++size) {
    cout << kTableDelimiter << kTableDelimiter << kTableDelimiter << endl;
    cout << kTableDelimiter << " Vector size: " << size <<" "<< kTableDelimiter << endl;
    for (unsigned test = 0; test < test_amount; ++test) {
      // Vector creation
      random_vector = create_random_vector(size, kMaximumVectorValue);      
      cout << "\n\tVector: "; show_vector(random_vector, "");

      test_algorithm("MergeSort", framework, new MergesortSolution(), new MergesortProblem(random_vector));
      test_algorithm("QuickSort", framework, new QuicksortSolution(), new QuicksortProblem(random_vector, 0, random_vector.size()-1));      
    }    
  }
  cout << kTableDelimiter << kTableDelimiter << kTableDelimiter << endl;
}

/**
 * @brief Time measure of an algorithm using the provided framework, solution, and problem.
 * @param name - Name of the algorithm being tested.
 * @param framework - Pointer to the Divide and Conquer framework.
 * @param solution - Pointer to the solution object.
 * @param problem - Pointer to the problem object.
 */
void test_algorithm(const string& name, DnCFramework* framework, Solution* solution, Problem* problem) {
  unsigned maximum_depth = 0;
  cout << endl; //cout << "\n<" + name + ">: ";
  
  auto start = std::chrono::high_resolution_clock::now();
  problem = problem;
  solution = solution;
  framework->SetAlgorithm(solution);
  framework->Solve(problem, solution, maximum_depth);
  solution->Show();

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  cout << "(o) Time: " << duration.count() << " microseconds" << endl;
  // Modificación
  cout << "(o) Recursion calls: " << framework->recursive_calls_ << endl; framework->ResetRecursiveCalls();
  cout << "(o) Maximum depth: " << framework->maximum_depth_ << endl; framework->ResetMaximumDepth();
  //cout << "(o) Recurrence: " << framework->GetRecurrence() << endl;
}