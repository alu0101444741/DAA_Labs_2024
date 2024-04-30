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

#include "problem.h"

using namespace std;

/** @brief Solution class for the Maximum Diversity solver. */
class Solution {
private:
  Problem* problem_;
  vector<unsigned> solution_;
  double diversity_;
public:
  /**
   * @brief Constructor for creating a Solution object.
   * @param problem A pointer to the problem instance.
   */
  Solution(Problem* problem) : problem_(problem), solution_(vector<unsigned>(0, 0)), diversity_(0.0) {}

  /** @brief Calculate the diversity of the solution based on the distances between elements. */
  void UpdateDiversity();

  /**
   * @brief Get the Element at the specified index.
   * @param index - element index
   * @return Element 
   */
  unsigned GetElementAtIndex(unsigned index) const;

  vector<unsigned> GetElements() const { return solution_; }

  /**
   * @brief Adds a new element to the solution 
   * @param element Element to be added
   * @param position Position at which to insert the element. It will be added at the end if position has a negative value
   */
  //void AddElement(const Element& element, int position = -1);
  void AddElement(unsigned element_index, int position = -1);

  /**
   * @brief Removes the element on a given position 
   * @param element_index Element to be removed
   */
  void RemoveElement(unsigned element_index);

  /**
   * @brief Replace one element from the solution with another one which is not included. 
   * @param first_index Element to be removed
   * @param second_index Element to be included
   */
  void ReplaceElement(unsigned first_index, unsigned second_index);

  /**
   * @brief Check if a given element is included in the solution
   * @param element - Element to find
   * @return true if included
   */
  //bool HasElement(const Element& element_to_find) const;
  bool HasElement(unsigned element_index) const;

  /**
   * @brief Get the diversity (z) value of the solution 
   * @return diversity value
   */
  float GetDiversity() const { return diversity_; }

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
   * @param cpu String with the execution time of the algorithm
   * @param iterations Iterations executed by the algorithm
   * @param candidate_list_size Size of the candidate list
   * @param show_elements Flag indicating whether to display the elements.
   */
  void Show(const string& tag, const string& cpu, unsigned iterations = 1, unsigned candidate_list_size = 1, bool show_elements = false);
  void ShowMarkdown(const string& tag, const string& cpu, unsigned iterations = 1, unsigned candidate_list_size = 1, bool show_elements = false);
};
#endif // MAX_DIV_SOLUTION_H_