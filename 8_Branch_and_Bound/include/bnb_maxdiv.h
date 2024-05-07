/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: May 1 2024
 *
 * @brief Branch and Bound Maximum Diversity solver class definition.
 * 
 */
#ifndef BRANCH_BOUND_MAX_DIV_H_
#define BRANCH_BOUND_MAX_DIV_H_

#include "max_div.h"
//#include "./utilities/branch_bound_utilities.h"
#include "greedy_maxdiv.h"
#include "grasp_maxdiv.h"

/*
vector<unsigned> get_unselected(const vector<unsigned>& all_elements_indexes, const vector<unsigned>& current_selection);

vector<pair<unsigned, float>> sorted_distances(Problem* problem, unsigned v);

float calculate_dmin(Problem* problem, const vector<unsigned>& current_selection,
  const vector<pair<unsigned, float>>& distances,
  unsigned m_value_
);

float calculate_dmax( Problem* problem, const vector<unsigned>& current_selection,
  const vector<pair<unsigned, float>>& distances,
  unsigned m_value_
);
*/
/** @brief Greedy Parallel Machine Scheduling Problem solver. */
class BranchBoundMaxDiversity: public MaximumDiversity {
private:  
  bool perform_local_search_;
public:

  /** @brief Represents a node in the Branch and Bound algorithm tree. */
  class Node {
  public:
    vector<unsigned> solution_;
    unsigned depth_, label_;
    bool pruned_;

    /** @brief Default constructor. */
    Node() :  depth_(0), label_(0), pruned_(false) {}

    /**
     * @brief Parameterized constructor.
     * 
     * @param solution The solution vector.
     * @param label The label or index associated with the node.
     */
    Node(vector<unsigned> solution, unsigned label)
    : solution_(solution), depth_(solution.size()), label_(label), pruned_(false) {}

    /** @brief Mark the node as pruned. */
    void Prune() { pruned_ = true; }

    /**
     * @brief Check if the node is pruned.
     * @return True if the node is pruned, false otherwise.
     */
    bool isPruned() const { return pruned_; }
  };

  /** @brief Constructor for the BranchBoundMaxDiversity solver. */
  BranchBoundMaxDiversity(bool perform_local_search = false)
  : perform_local_search_(perform_local_search)
  {
    algorithm_name_ = "Branch and Bound";
    problem_ = new Problem();
    generated_nodes_ = 1;
  }  

  /**
   * @brief Solve the Maximum Diversity using a branch and bound algorithm.
   * @return Solution representing the subset of elements that has the maximum diversity.
   */
  Solution Solve();
  
  // **************** Intento de solución usando el Paper ****************
  Solution Solve_2();
  float CalculateElementZ(const vector<unsigned>& elements, const vector<bool>& selected_elements, unsigned element_v, unsigned k);
  vector<unsigned> GetBestElements(
    const vector<unsigned>& unselected,
    const vector<unsigned>& all_elements_indexes,
    const vector<bool>& selected_elements,
    unsigned number_of_elements
  );
  // *********************************************************************
  
private:

  Solution GetInitialSolution(MaximumDiversity* solver) const;

  void CreateInitialNodes(vector<Node>& tree, vector<bool>& selected_elements, const vector<unsigned>& all_elements_indexes, unsigned lower_bound);

  void UpdateSolution(Solution& best_solution, const vector<Node>& tree, unsigned initial_level, unsigned next_level) const;

  /**
   * @brief Toggle the selected status of elements based on the provided elements vector.
   * @param elements The vector containing the indices of elements whose selected status needs to be toggled.
   * @param selected The vector indicating the selected status of elements.
   */
  void ChangeSelected(const vector<unsigned>& elements, vector<bool>& selected) const;

  /**
   * @brief Calculate the upper bound for the Branch and Bound algorithm.
   * @param partial_solution The partial solution vector.
   * @param elements The set of elements.
   * @param selected_elements The vector indicating which elements are currently selected.
   * @return The upper bound value.
   */
  float CalculateUpperBound(const vector<unsigned>& partialSolution, const vector<unsigned>& elementSet, const vector<bool>& selected_elements) const;

  /**
   * @brief Calculate the diversity value of a given solution.
   * @param solution The solution vector.
   * @return The diversity value.
   */
  float CalculateZ(const vector<unsigned>& solution) const;

  /**
   * @brief Calculate the upper bound (part 2).
   * @param elements The set of elements.
   * @param selected_elements The vector indicating which elements are selected.
   * @param k The current size of the partial solution.
   * @return The upper bound value for part 2.
   */
  float CalculateUB2(const vector<unsigned>& elementSet, const vector<bool>& selected_elements, unsigned k) const;

  /**
   * @brief Calculate the upper bound (part 3).
   * @param elements The set of elements.
   * @param selected_elements The vector indicating which elements are selected.
   * @param k The current size of the partial solution.
   * @return The upper bound value for part 3.
   */
  float CalculateUB3(const vector<unsigned>& elementSet, const vector<bool>& selected_elements, unsigned k) const;

  /**
   * @brief Calculate the diversity of selected elements with respect to a given element.
   * @param elements The set of elements.
   * @param selected_elements The vector indicating which elements are selected.
   * @param element_v The element to calculate the diversity from.
   * @return The diversity value.
   */
  float CalculateZSel(const vector<unsigned>& elementSet, const vector<bool>& selected_elements, unsigned element_v) const;

  /**
   * @brief Calculate the diversity of unselected elements with respect to a given element.
   * @param elements The set of elements.
   * @param selected_elements The vector indicating which elements are selected.
   * @param element_v The element to calculate the diversity from.
   * @param k The current size of the partial solution.
   * @return The diversity value.
   */
  float CalculateZUnsel(const vector<unsigned>& elementSet, const vector<bool>& selected_elements, unsigned element_v, unsigned k) const;
};

#endif /* BRANCH_BOUND_MAX_DIV_H_ */