/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Solution class for the Maximum Diversity algorithm.
 */

#ifndef MAX_DIV_SOLUTION_H_
#define MAX_DIV_SOLUTION_H_

#include "max_div_utilities.h"
#include "problem.h"

using namespace std;

/** @brief Solution class for the Maximum Diversity solver. */
class Solution {
private:
  Problem* problem_;
  vector<Element> solution_;
  double diversity_;
public:
  /**
   * @brief Constructor for creating a Solution object.
   * @param problem A pointer to the problem instance.
   */
  Solution(Problem* problem) : problem_(problem) {}

  /** @brief Calculate the diversity of the solution based on the distances between elements. */
  void UpdateDiversity();

  /**
   * @brief Adds a new element to the solution 
   * @param element New element to be added
   */
  void AddElement(const Element& element) { solution_.push_back(element); }

  /**
   * @brief Get the Problem object 
   * @return Pointer to the problem objetc 
   */
  Problem* GetProblem() const { return problem_; }

  /**
   * @brief Retrieves the size of the solution which is the number of elements stored.
   * @returns The size of the solution.
   */
  unsigned GetSolutionSize() const { return solution_.size(); }

  /**
   * @brief Display the solution of the maximum diversity problem.
   * @param tag String that will preceed the total time console output
   * @param show_elements Flag indicating whether to display the elements.
   */
  void Show(const string& tag, bool show_elements = false);
};
#endif // MAX_DIV_SOLUTION_H_