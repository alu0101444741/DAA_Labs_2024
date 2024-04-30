/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief Tabu search Maximum Diversity solver class definition.
 * 
 */
#ifndef TABU_MAX_DIV_H_
#define TABU_MAX_DIV_H_

#include "max_div.h"
#include "./utilities/swap_movement.h"

/** @brief Tabu Search Maximum Diversity Problem solver. */
class TabuMaxDiversity: public MaximumDiversity {
public:  
  /** 
   * @brief Constructor for the TabuMaxDiversity solver.
   * @param maximum_iterations - Number of iterations for the grasp algorithm
   * @param tabu_tenure - Size of the list of the tabu list (Tabu tenure)
   */
  TabuMaxDiversity(
    unsigned maximum_iterations,
    unsigned tabu_tenure
  )
  {
    algorithm_name_ = "TabuSearch";
    maximum_iterations_ = maximum_iterations;
    candidate_list_size_ = tabu_tenure;
    problem_ = new Problem();
  }

  /**
   * @brief Solve the Maximum Diversity using a Tabu Search algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();

private:
  /**
   * @brief Get the best (highest increase on Z-value) non-tabu movement from a list of movements.
   * @param movements Movements to consider.
   * @param tabu_list Tabu list.
   * @return The best non-tabu movement.
   */
  SwapMovement GetBestNotTabuMovement(const vector<SwapMovement>& movements, const vector<SwapMovement>& tabu_list) const;
  
  /**
   * @brief Generate movements based on the current solution and remaining elements.
   * @param solution The current solution.
   * @param remaining_elements Remaining elements.
   * @return generated movements.
   */
  vector<SwapMovement> GenerateMovements(const Solution& solution, const vector<unsigned>& remaining_elements) const;

  void UpdateTabuListValues(const Solution& solution, vector<SwapMovement>& movements) const;
  
  void ApplyBestTabuMovement(Solution& solution, vector<SwapMovement>& tabu_list, vector<unsigned>& remaining_elements) const;
};

#endif /* TABU_MAX_DIV_H_ */