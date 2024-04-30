/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 20 2024
 *
 * @brief Greedy Maximum Diversity solver class implementation.
 * 
 */

#include "tabu_maxdiv.h"



/**
 * @brief Solve the Maximum Diversity using a Tabu Search algorithm.
 * @return Solution representing a set of k-dimensional elements.
 */
Solution TabuMaxDiversity::Solve() {  
  Solution current_solution = ConstructInitialSolution(problem_, candidate_list_size_);
  Solution best_solution = current_solution;
  vector<SwapMovement> tabu_list;
  
  vector<unsigned> remaining_elements = GetRemainingElements(current_solution);  

  for (unsigned iteration = 0; iteration < maximum_iterations_; ++ iteration) {
    // Get all possible SwapMovement for the current solution
    vector<SwapMovement> available_movements = GenerateMovements(current_solution, remaining_elements);
    //cout << kFourSpaces + "Solution size: " << best_solution.GetSolutionSize() << endl;
    //cout << kFourSpaces + "Remaining elements: " << remaining_elements.size() << endl;
    //for (const auto& e : remaining_elements) cout << e << ", ";
    //cout << endl;
    //cout << kFourSpaces + "Av. movements: " << available_movements.size() << endl << endl;    
    //UpdateTabuListValues(current_solution, tabu_list);

    // Search for the movement which provides the highest Z and is NOT in the tabu list
    SwapMovement best_move = GetBestNotTabuMovement(available_movements, tabu_list);

    if (!(best_move == SwapMovement::kNullSwapMovement)) { // Update Solution if found a movement
      current_solution.ReplaceElement(best_move.GetIndexes().first, best_move.GetIndexes().second);
      replace_index(remaining_elements, best_move.GetIndexes().first, best_move.GetIndexes().second);      
      if (best_solution.GetDiversity() < current_solution.GetDiversity()) {
        best_solution = current_solution;
      }      
      tabu_list.push_back(best_move);
    } else { // Apply the best tabu movement and move it to the back of the list
      ApplyBestTabuMovement(current_solution, tabu_list, remaining_elements);
    }    
    // Remove oldest movement
    if (tabu_list.size() > candidate_list_size_) {
      tabu_list.erase(tabu_list.begin());
    }
  }
  return best_solution;
}

/**
 * @brief Get the best (highest increase on Z-value) non-tabu movement from a list of movements.
 * @param movements Movements to consider.
 * @param tabu_list Tabu list.
 * @return The best non-tabu movement.
 */
SwapMovement TabuMaxDiversity::GetBestNotTabuMovement(const vector<SwapMovement>& movements, const vector<SwapMovement>& tabu_list) const {  
  float best_value = -numeric_limits<float>::infinity();
  SwapMovement best_movement(SwapMovement::kNullSwapMovement);

  for (const SwapMovement& movement : movements) {    
    if (find(tabu_list.begin(), tabu_list.end(), movement) == tabu_list.end()) { // Check if the movement is not tabu
      if (movement.GetValue() > best_value) {
        best_movement = movement;
        best_value = movement.GetValue();
      }
    }
  }
  return best_movement;
}

/**
 * @brief Generate movements based on the current solution and remaining elements.
 * @param solution The current solution.
 * @param remaining_elements Remaining elements.
 * @return generated movements.
 */
vector<SwapMovement> TabuMaxDiversity::GenerateMovements(const Solution& solution, const vector<unsigned>& remaining_elements) const {
  vector<unsigned> solution_elements = solution.GetElements();
  vector<SwapMovement> movements;
/*
  cout << "Solution elements: ";
  for (const unsigned& s : solution_elements) cout << s << ", ";
  cout << endl;
  cout << "Remaining elements: ";
  for (const unsigned& e : remaining_elements) cout << e << ", ";
  cout << endl;
*/
  for (const unsigned& s : solution_elements) {
    for (const unsigned& e : remaining_elements) {
      if (solution.HasElement(e)) continue;
      //cout << "\tChecking " << s << " and " << e << endl;
      Solution current_solution(solution);
      current_solution.ReplaceElement(s, e);
      float movement_value = current_solution.GetDiversity() - solution.GetDiversity();
      movements.push_back(SwapMovement(s, e, movement_value));
    }
  }  
  return movements;
}

void TabuMaxDiversity::ApplyBestTabuMovement(Solution& solution, vector<SwapMovement>& tabu_list, vector<unsigned>& remaining_elements) const {
  SwapMovement best_tabu_movement(SwapMovement::kNullSwapMovement);
  for (unsigned i = 0; i < tabu_list.size(); ++i) {
    if (tabu_list[i].GetValue() > best_tabu_movement.GetValue()) {
      best_tabu_movement = tabu_list[i];
    }
  }
  solution.ReplaceElement(best_tabu_movement.GetIndexes().first, best_tabu_movement.GetIndexes().second);
  replace_index(remaining_elements, best_tabu_movement.GetIndexes().first, best_tabu_movement.GetIndexes().second);
  tabu_list.erase(find(tabu_list.begin(), tabu_list.end(), best_tabu_movement));
  tabu_list.push_back(best_tabu_movement);
}

void TabuMaxDiversity::UpdateTabuListValues(const Solution& solution, vector<SwapMovement>& movements) const {
  for (SwapMovement& e : movements) {
    Solution current_solution(solution);
    current_solution.ReplaceElement(e.GetIndexes().first, e.GetIndexes().second);
    float movement_value = current_solution.GetDiversity() - solution.GetDiversity();
    e.SetValue(movement_value);
  }
}


