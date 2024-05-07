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

#include "local_search.h"

using namespace std;

/** @brief Base class for any other Maximum Diversity solver. */
class MaximumDiversity {
protected:
  Problem* problem_;
  Solution* solution_;
  string algorithm_name_;
  unsigned m_value_;
  unsigned maximum_iterations_, candidate_list_size_, generated_nodes_;
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
   * @brief Setter for the maximum iterations.
   * @param m_value - The new maximum iterations value.
   */
  void SetMaximumIterations(unsigned iterations) { maximum_iterations_ = iterations; }  

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

  unsigned GetNodesGenerated() const { return generated_nodes_; }

protected:
/**
 * @brief Build the initial solution for the Maximum Diversity algorithms.
 * @param candidate_list_size - Maximum candidate list size
 */
Solution ConstructInitialSolution(unsigned candidate_list_size);

/**
 * @brief Calculate the gravity center of a set of elements.
 * @param elements A vector of Element objects representing the elements.
 * @return An Element object representing the gravity center.
 */
Element CalculateGravityCenter(const vector<unsigned>& elements) const;

/**
 * @brief Get the indexes of every Element in a vector. 
 * @param elements A vector of Element objects.
 * @return A vector containing the indexes of elements in the same order as the input vector.
 */
vector<unsigned> GetElementIndexes(const vector<Element>& elements) const;

/**
 * @brief Get the elements indexes that are not included in a given Solution 
 * @param solution 
 * @return array of indexes
 */
vector<unsigned> GetRemainingElements(const Solution& solution) const;

/**
 * @brief Get the index of furthest element from another Element.
 * @param elements Indexes of Element objects representing the elements.
 * @param center An Element object representing the centroid element.
 * @return Index of the furthest Element object from the given Element.
 */
unsigned GetFurthestElement(const vector<unsigned>& elements, const Element& center) const;

/**
 * @brief Get the N furthest elements from a given center element.
 * @param number_of_elements Amount of elements to get
 * @param elements A vector of Element indexes representing the elements.
 * @param center An Element object representing the center element.
 * @return Indexes of the furthests Element objects from the center.
 */
vector<unsigned> GetTheNFurthestElements(unsigned number_of_elements, const vector<unsigned>& elements, const Element& center) const;

/**
 * @brief Erase a specific element from a vector of elements.
 * @param elements A reference to a vector of Element indexes.
 * @param element_to_erase The Element object to be erased from the vector.
 */
void EraseElement(vector<unsigned>& elements, unsigned element_to_erase) const;

};
#endif // MAXIMUM_DIVERSITY_H_