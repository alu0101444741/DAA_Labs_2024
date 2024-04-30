/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Problem class for the Maximum Diversity algorithm.
 */

#ifndef MAX_DIV_PROBLEM_H_
#define MAX_DIV_PROBLEM_H_

#include <algorithm>
#include <sstream>
#include <regex>

#include "./utilities/max_div_utilities.h"

using namespace std;

/** @brief Problem class for the Maximum Diversity solver. */
class Problem {
private:
  vector<Element> elements_;
  unsigned dimension_;
  vector<vector<float>> distances_;
public:
  /** @brief Constructor for the Problem class. */
  Problem() {}  

  /**
   * @brief Create the Maximum Diversity instance from a 'txt' file. 
   * @param filename - name/path of the file
   */
  void CreateFromFile(const string& filename);  

  /**
   * @brief Retrieves the stored elements.
   * @returns Elements stored.
   */
  vector<Element> GetElements() const { return elements_; }

  /**
   * @brief Retrieves the stored element at a given index.
   * @returns Elements stored.
   */
  Element GetElementOnIndex(unsigned index) const {
    index_validation(index, elements_.size(), "Problem");
    return elements_[index];
  }

  /**
   * @brief Retrieves the dimension of the elements (K).
   * @returns The dimension of the elements.
   */
  unsigned GetDimension() const { return dimension_; }

  /**
   * @brief Retrieves the distance between two elements from the distances matrix.
   * @param first_index First element index
   * @param second_index Second element index
   * @returns Distance between lements.
   */
  float GetDistance(unsigned first_index, unsigned second_index) const {
    index_validation(first_index, elements_.size(), "Problem");
    index_validation(second_index, elements_.size(), "Problem");
    return distances_[first_index][second_index];
  }

  /** @brief Prints the problem information: elements and their dimension */
  void ShowInfo();
private:
  /**
   * @brief Calculates the distances between all pairs of elements and fills
   * the distances matrix symmetrically.
   */
  void CalculateDistances();
};
#endif // MAX_DIV_PROBLEM_H_