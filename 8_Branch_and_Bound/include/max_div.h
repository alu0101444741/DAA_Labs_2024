/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief MaximumDiversity interface definition.
 */

#ifndef MAXIMUM_DIVERSITY_H_
#define MAXIMUM_DIVERSITY_H_

#include "max_div_utilities.h"
#include "local_search.h"

using namespace std;

/** @brief Base class for any other Maximum Diversity solver. */
class MaximumDiversity {
protected:
  Problem* problem_;
  Solution* solution_;
  string algorithm_name_;
  unsigned m_value_;
public:
  /** @brief Constructor for the Maximum Diversity solver. */
  MaximumDiversity() : algorithm_name_("Maximum Diversity"),  m_value_(0) { }

  /**
   * @brief Solve the problem and return a subset of elements.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  virtual Solution Solve() = 0;

  /**
   * @brief Initializes the problem by creating it from a file. 
   * @param filename - The name of the file containing the problem data.
   */
  void InitializeProblem(const string& filename) { problem_->CreateFromFile(filename); } 

  /**
   * @brief Setter for the solution size (m).
   * @param m_value - The new solution size.
   */
  void SetSubsetSize(unsigned m_value) { m_value_ = m_value; }

  /**
   * @brief Setter for the problem.
   * @param problem - The name of the algorithm.
   */
  void SetProblem(Problem* problem) { problem_ = problem; }

  /**
   * @brief Getter method for the problem.
   * @return the stored problem.
   */
  Problem* GetProblem() const { return problem_; }

  /**
   * @brief Get the name of the algorithm as a string.
   * @return The name of the algorithm.
   */
  string GetAlgorithmName() { return algorithm_name_; }

protected:
/**
 * @brief Build the initial solution for the Maximum Diversity algorithms.
 * 
 * @param problem - Problem information
 * @param candidate_list_size - Maximum candidate list size
 */
Solution ConstructInitialSolution(Problem* problem, unsigned candidate_list_size);

/**
 * @brief Calculate the gravity center of a set of elements.
 * @param elements A vector of Element objects representing the elements.
 * @return An Element object representing the gravity center.
 */
Element CalculateGravityCenter(const vector<Element>& elements) const;

/**
 * @brief Get the furthest element from a given center element.
 * @param elements A vector of Element objects representing the elements.
 * @param center An Element object representing the center element.
 * @return The furthest Element object from the center.
 */
Element GetFurthestElement(const vector<Element>& elements, const Element& center) const;

/**
 * @brief Get the N furthest elements from a given center element.
 * @param number_of_elements Amount of elements to get
 * @param elements A vector of Element objects representing the elements.
 * @param center An Element object representing the center element.
 * @return The furthest Element object from the center.
 */
vector<Element> GetTheNFurthestElements(unsigned number_of_elements, const vector<Element>& elements, const Element& center) const;

/**
 * @brief Erase a specific element from a vector of elements.
 * @param elements A reference to a vector of Element objects.
 * @param element_to_erase The Element object to be erased from the vector.
 */
void EraseElement(vector<Element>& elements, const Element& element_to_erase) const;

};
#endif // MAXIMUM_DIVERSITY_H_