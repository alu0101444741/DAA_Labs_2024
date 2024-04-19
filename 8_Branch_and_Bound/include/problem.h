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

#include "max_div_utilities.h"

using namespace std;

/** @brief Problem class for the Maximum Diversity solver. */
class Problem {
private:
  vector<Element> elements_;
  unsigned dimension_;
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
   * @brief Retrieves the dimension of the elements (K).
   * @returns The dimension of the elements.
   */
  unsigned GetDimension() const { return dimension_; }

  /** @brief Prints the problem information: elements and their dimension */
  void ShowInfo();
};
#endif // MAX_DIV_PROBLEM_H_