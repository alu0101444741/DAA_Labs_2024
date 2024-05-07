/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: May 1 2024
 *
 * @brief Branch and Bound Maximum Diversity solver class implementation.
 * 
 */

#include "bnb_maxdiv.h"

/**
 * @brief Solve the Maximum Diversity using a branch and bound algorithm.
 * @return Solution representing a set of k-dimensional elements.
 */
Solution BranchBoundMaxDiversity::Solve() { //return Solve_2();

  Solution best_solution = GetInitialSolution(new GraspMaxDiversity(20, 3));//GetInitialSolution(new GreedyMaxDiversity());
  generated_nodes_ = 1;

  vector<unsigned> all_elements_indexes = GetElementIndexes(problem_->GetElements());
  vector<bool> selected_elements(problem_->GetElements().size(), false);  

  float lower_bound = CalculateUpperBound(best_solution.GetElements(), all_elements_indexes, selected_elements);
  
  ChangeSelected(best_solution.GetElements(), selected_elements);

  for (unsigned i = 0; i < selected_elements.size(); ++i) {
    if (best_solution.HasElement(i)) selected_elements[i] = true;
  }

  vector<Node> tree = {Node()}; // Root node
  unsigned initial_level = 1, next_level = initial_level, level_counter;

  // Generate initial nodes for the tree
  CreateInitialNodes(tree, selected_elements, all_elements_indexes, lower_bound);

  next_level += (all_elements_indexes.size() - m_value_ + 1);

  // Generate remaining nodes
  for (unsigned i = 1; i < m_value_; i++) {
    level_counter = 0;
    for (unsigned j = initial_level; j < next_level; j++) {
      // Skip node if pruned. Add an empty node
      if (tree[j].isPruned()) {
        cout << "(!) ";
        for (unsigned k = tree[j].label_; k <= all_elements_indexes.size() - (m_value_ - tree[j].depth_); k++) {
          tree.push_back(Node());
          level_counter++;
        }
        continue;
      }
      for (unsigned k = tree[j].label_; k <= all_elements_indexes.size() - (m_value_ - tree[j].depth_); k++) {
        vector<unsigned> current_solution = tree[j].solution_;
        current_solution.push_back(k);
        tree.push_back(Node(current_solution, k));
        //ChangeSelected(current_solution, selected_elements);
        // Prune if CurrentNode.LB < LB
        if (CalculateUpperBound(current_solution, all_elements_indexes, selected_elements) < lower_bound) {
          tree[tree.size() - 1].Prune();
        }
        generated_nodes_ ++;
        //ChangeSelected(current_solution, selected_elements);
        level_counter++;
      }
    }
    initial_level = next_level;
    next_level += level_counter;
  }

  UpdateSolution(best_solution, tree, initial_level, next_level);
   
  return best_solution;
}

/**
 * @brief Generate a solution for the current problem using a MaximumDiversity solver as Greedy, GRASP or TabuSearch
 * @param solver Pointer to a MaximumDiversity solver 
 * @return Solution 
 */
Solution BranchBoundMaxDiversity::GetInitialSolution(MaximumDiversity* solver) const {
  solver->SetProblem(problem_);
  solver->SetSubsetSize(m_value_);
  return solver->Solve();
}

/**
 * @brief Create initial nodes in the Branch and Bound algorithm tree. 
 * @param tree The tree vector containing the nodes.
 * @param selected_elements The vector indicating which elements are selected.
 * @param all_elements_indexes The vector containing all element indexes.
 * @param lower_bound The lower bound value.
 */
void BranchBoundMaxDiversity::CreateInitialNodes(vector<Node>& tree, vector<bool>& selected_elements, const vector<unsigned>& all_elements_indexes, unsigned lower_bound) {
  for (unsigned i = 0; i < all_elements_indexes.size() - m_value_ + 1; i++) {
    vector<unsigned> current_solution = tree[0].solution_;
    current_solution.push_back(i);
    tree.push_back(Node(current_solution, i));    
    ChangeSelected(current_solution, selected_elements);
    // Prune if CurrentNode.LB < LB
    if (CalculateUpperBound(current_solution, all_elements_indexes, selected_elements) < lower_bound) {
      tree[tree.size() - 1].Prune();
    }
    ChangeSelected(current_solution, selected_elements);
    generated_nodes_ ++;
  }
}

/**
 * @brief Update the best solution found in the Branch and Bound algorithm.
 * @param best_solution The best solution found so far.
 * @param tree The tree vector containing the nodes.
 * @param initial_level The initial level in the tree.
 * @param next_level The next level in the tree.
 */
void BranchBoundMaxDiversity::UpdateSolution(Solution& best_solution, const vector<Node>& tree, unsigned initial_level, unsigned next_level) const {
  float best_z = 0;
  vector<unsigned> solution;
  for (unsigned i = initial_level; i < next_level; i++) { // Look for the best solution
    if (tree[i].isPruned()) continue;
    float newZ = CalculateZ(tree[i].solution_);
    if (newZ > best_z) {
      best_z = newZ;
      solution = tree[i].solution_;
    }
  }

  if (best_z > best_solution.GetDiversity()) { // Update solution
    best_solution.Clear();
    for (const unsigned& e : solution) {
      best_solution.AddElement(e);
    }
  } 
}

/**
 * @brief Calculate the upper bound for the Branch and Bound algorithm.
 * @param partial_solution The partial solution vector.
 * @param elements The set of elements.
 * @param selected_elements The vector indicating which elements are currently selected.
 * @return The upper bound value.
 */
float BranchBoundMaxDiversity::CalculateUpperBound(const vector<unsigned>& partial_solution, const vector<unsigned>& elements, const vector<bool>& selected_elements) const {
  return CalculateZ(partial_solution)
       + CalculateUB2(elements, selected_elements, partial_solution.size())
       + CalculateUB3(elements, selected_elements, partial_solution.size());
}

/**
 * @brief Calculate the Z value of a given solution.
 * @param solution The solution vector.
 * @return The diversity value.
 */
float BranchBoundMaxDiversity::CalculateZ(const vector<unsigned>& solution) const {
  float z = 0.0;
  for (unsigned i = 0; i < solution.size(); i++) {
    for (unsigned j = i + 1; j < solution.size(); j++) {
      z += problem_->GetDistance(solution[i], solution[j]);
    }
  }
  return z;
}

/**
 * @brief Calculate the upper bound (part 2).
 * Get the the sum of the (m_value_ - k) highest ZSel values
 * @param elements The set of elements.
 * @param selected_elements The vector indicating which elements are selected.
 * @param k The current size of the partial solution.
 * @return The upper bound value for part 2.
 */
float BranchBoundMaxDiversity::CalculateUB2(const vector<unsigned>& elements, const vector<bool>& selected_elements, unsigned k) const {
  vector<float> ZSel;
  for (unsigned i = 0; i < elements.size(); i++) {
    if (selected_elements[elements[i]]) continue;
    ZSel.push_back(CalculateZSel(elements, selected_elements, elements[i]));
  }
  // Get the m_value_ - k best ZSel values
  float UB2 = 0;
  for (unsigned i = 0; i < m_value_ - k; i++) {
    unsigned bestIndex = 0;
    for (unsigned j = 0; j < ZSel.size(); j++) {
      if (ZSel[j] > ZSel[bestIndex]) {
        bestIndex = j;
      }
    }
    UB2 += ZSel[bestIndex];
    ZSel.erase(ZSel.begin() + bestIndex);
  }
  return UB2;
}

/**
 * @brief Calculate the upper bound (part 3).
 * Get the the sum of the (m_value_ - k) highest ZUnsel values
 * @param elements The set of elements.
 * @param selected_elements The vector indicating which elements are selected.
 * @param k The current size of the partial solution.
 * @return The upper bound value for part 3.
 */
float BranchBoundMaxDiversity::CalculateUB3(const vector<unsigned>& elements, const vector<bool>& selected_elements, unsigned k) const {
  vector<float> ZUnsel;
  for (unsigned i = 0; i < elements.size(); i++) {
    if (selected_elements[elements[i]]) continue;
    ZUnsel.push_back(CalculateZUnsel(elements, selected_elements, elements[i], k));
  }
  // Get the (m_value_ - k) best ZUnsel values
  float UB3 = 0;
  for (unsigned i = 0; i < m_value_ - k; i++) {
    unsigned bestIndex = 0;
    for (unsigned j = 0; j < ZUnsel.size(); j++) {
      if (ZUnsel[j] > ZUnsel[bestIndex]) {
        bestIndex = j;
      }
    }
    UB3 += ZUnsel[bestIndex];
    ZUnsel.erase(ZUnsel.begin() + bestIndex);
  }
  return UB3;
}

/**
 * @brief Calculate the diversity of a given element with respect to the selected elements.
 * @param elements The set of elements.
 * @param selected_elements The vector indicating which elements are selected.
 * @param element_v The element to calculate the diversity from.
 * @return The diversity value.
 */
float BranchBoundMaxDiversity::CalculateZSel(const vector<unsigned>& elements, const vector<bool>& selected_elements, unsigned element_v) const {
  float ZSel = 0;
  for (unsigned i = 0; i < elements.size(); i++) {
    if (!selected_elements[elements[i]]) continue;
    ZSel += problem_->GetDistance(elements[i], element_v);
  }
  return ZSel;
}

/**
 * @brief Calculate the diversity of a given element with respect to the not selected elements.
 * @param elements The set of elements.
 * @param selected_elements The vector indicating which elements are selected.
 * @param element_v The element to calculate the diversity from.
 * @param k The current size of the partial solution.
 * @return The diversity value.
 */
float BranchBoundMaxDiversity::CalculateZUnsel(const vector<unsigned>& elements, const vector<bool>& selected_elements, unsigned element_v, unsigned k) const {  
  vector<float> dUnsel;
  float ZUnsel = 0;

  for (unsigned i = 0; i < elements.size(); i++) {
    if (selected_elements[elements[i]]) continue;
    dUnsel.push_back(problem_->GetDistance(elements[i], element_v));
  }
  unsigned end_value = (m_value_ == k) ? 0 : m_value_ - k - 1;

  for (unsigned i = 0; i < end_value; i++) {
    unsigned bestIndex = 0;
    for (unsigned j = 0; j < dUnsel.size(); j++) {
      if (dUnsel[j] > dUnsel[bestIndex]) {
        bestIndex = j;
      }
    }
    ZUnsel += dUnsel[bestIndex];
    if (bestIndex > 0) dUnsel.erase(dUnsel.begin() + bestIndex);
  }
  return ZUnsel / 2;
}

/**
 * @brief Toggle the selected status of elements based on the provided elements vector.
 * @param elements The vector containing the indices of elements whose selected status needs to be toggled.
 * @param selected The vector indicating the selected status of elements.
 */
void BranchBoundMaxDiversity::ChangeSelected(const vector<unsigned>& elements, vector<bool>& selected) const {
  for (unsigned i = 0; i < elements.size(); ++i) {
    selected[elements[i]] = !selected[elements[i]];
  }
}