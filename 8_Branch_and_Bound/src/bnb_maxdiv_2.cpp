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

vector<unsigned> get_unselected(
  const vector<unsigned>& all_elements_indexes,
  const vector<unsigned>& current_selection
) {
  vector<unsigned> unselected;
  for (unsigned i = 0; i < all_elements_indexes.size(); ++i) { // Getting V\Sel as "unselected"
    bool element_added = false;
    for (unsigned j = 0; j < current_selection.size(); ++j) {
      if (i == current_selection[j]) {
        element_added = true;
        break;
      }
    }
    if (!element_added) unselected.push_back(i);
  }
  return unselected;
}

vector<pair<unsigned, float>> sorted_distances(Problem* problem, unsigned v) {
  vector<pair<unsigned, float>> sorted_distances;
  for (const Element& e : problem->GetElements()) {
    sorted_distances.push_back(pair<unsigned, float>(e.GetIndex(), problem->GetDistance(v, e.GetIndex())));
  }
  sort(sorted_distances.begin(), sorted_distances.end(),
    [](const pair<unsigned, float>& a, const pair<unsigned, float>& b) {
      return a.second > b.second;
  });
  return sorted_distances;
}

float calculate_dmin(
  Problem* problem,
  const vector<unsigned>& current_selection,
  const vector<pair<unsigned, float>>& distances,
  unsigned m_value_
) {

  if (distances.size() < 1) return 0;

  float result = 0.0;
  
  for (unsigned i = 0; i < m_value_; ++i) {
    //cout << "Accessing " << distances.size() - i - 1 << " of " << distances.size() << endl;
    result += distances[distances.size() - i - 1].second;
  }
  return result / 2;
}

float calculate_dmax(
  Problem* problem,
  const vector<unsigned>& current_selection,
  const vector<pair<unsigned, float>>& distances,
  unsigned m_value_
) {
  float result = 0.0;
  for (unsigned i = 0; i < m_value_; ++i) {
    result += distances[i].second;
  }
  return result / 2;
}

float BranchBoundMaxDiversity::CalculateElementZ(
  const vector<unsigned>& elements,
  const vector<bool>& selected_elements,
  unsigned element_v,
  unsigned k
  ) {
  // cout << "[CalculateElementZ] Calculando Z\n"; // DEBUG
  // cout << "[CalculateElementZ] Calculate z of Unsel with k = " << k << endl; // DEBUG
  return  CalculateZSel(elements, selected_elements, element_v)
        + CalculateZUnsel(elements, selected_elements, element_v, k);
}

vector<unsigned> BranchBoundMaxDiversity::GetBestElements( // Get elements from V\Sel with maximum z
  const vector<unsigned>& unselected,
  const vector<unsigned>& all_elements_indexes,
  const vector<bool>& selected_elements,
  unsigned number_of_elements
) {
  vector<unsigned> best_elements;
  vector<pair<unsigned, float>> z_values(unselected.size());

  unsigned contador = 0;
  for (bool elemento : selected_elements) { if (elemento) { contador++; } }


  //cout << "Seleccionados: " << contador << endl;
  //cout << "No seleccionados: " << unselected.size() << endl;

  //cout << "\t\t Calculando z(v)...\n";
  
  for (unsigned i = 0; i < unselected.size(); ++i) {
    //cout << "[GetBestElements] Calculate z of Unsel with k = " << number_of_elements << endl; // DEBUG
    z_values[i] = pair<unsigned, float>(
      unselected[i],
      CalculateElementZ(unselected, selected_elements, unselected[i], number_of_elements)
    );
  }

  //cout << "\t\t Ordenando z(v)...\n";

  sort(z_values.begin(), z_values.end(),
    [](const pair<unsigned, float>& a, const pair<unsigned, float>& b) {
      return a.second > b.second;
  });

  //cout << "\t\t Obteniendo los " << number_of_elements << " mejores...\n";

  //vector<unsigned> best_elements(number_of_elements, 0);
  for (unsigned i = 0; i < number_of_elements; ++i) {
    best_elements.push_back(z_values[i].first);
  }
  return best_elements;
}

Solution BranchBoundMaxDiversity::Solve_2() {
  generated_nodes_ = 1;
  Solution best_solution = GetInitialSolution(new GreedyMaxDiversity());

  //cout << "[Solve_2] Initial solution OK\n"; // DEBUG

  vector<unsigned> all_elements_indexes = GetElementIndexes(problem_->GetElements());
  vector<bool> selected_elements(problem_->GetElements().size(), false);

  //vector<Node> tree = {Node()}; // Root node
  priority_queue<Node, vector<Node>, function<bool(Node, Node)>> tree(
        [](Node a, Node b) { return a.depth_ > b.depth_; });

  float lower_bound = best_solution.GetDiversity();

  tree.push(Node());

  for (unsigned i = 0; i < selected_elements.size(); ++i) {
    if (best_solution.HasElement(i)) selected_elements[i] = true;
  }

  // (2) Make ActiveNodes = { Initial nodes }
  for (unsigned i = 0; i < all_elements_indexes.size(); i++) {
    vector<unsigned> current_solution = tree.top().solution_; //tree[0].solution_;
    current_solution.push_back(i);
    //tree.push(Node(current_solution, i));    
    ChangeSelected(current_solution, selected_elements);
    // Prune if CurrentNode.LB < LB
    //if (CalculateUpperBound(current_solution, all_elements_indexes, selected_elements) < lower_bound) {
      //tree[tree.size() - 1].Prune();
    //}
    //else {
    tree.push(Node(current_solution, i));
    //}
    ChangeSelected(current_solution, selected_elements);
    generated_nodes_ ++;
  }
  tree.pop();

  //cout << "[Solve_2] Nodos iniciales creados. Iniciando bucle principal...\n"; // DEBUG

  while (tree.size() > 0) {
    Node current_node = tree.top(); // (3) Take Node from ActiveNodes
    if (current_node.solution_.size() == m_value_) { // It is a leaf node

      //cout << "\t[Paso 4] Nodo hoja. Calculando Z...\n"; // DEBUG

      float current_z = CalculateZ(current_node.solution_); // (4) Compute z'
      if (current_z > lower_bound) {
        lower_bound = current_z; // (5) LB = z'
      }
      tree.pop(); // (6) Remove Node from ActiveNodes
    }
    else { // Not a leaf node

      //cout << "\t[Paso 7] Nodo NO hoja.\n"; // DEBUG

      vector<unsigned> current_selection = current_node.solution_; // (7) Sel as partial solution
      bool node_removed = false;

      vector<unsigned> unselected = get_unselected(all_elements_indexes, current_selection); // unselected as V\Sel
      vector<float> selection_dmax(current_selection.size(), 0.0),
                    unselected_dmin(unselected.size(), 0.0);

      //cout << "\t[Paso 7] Calculando dmax.\n"; // DEBUG

      for (unsigned i = 0; i < current_selection.size(); ++i) {
        vector<pair<unsigned, float>> distances = sorted_distances(problem_, current_selection[i]);
        selection_dmax[i] = calculate_dmax(problem_, current_selection, distances, m_value_ - current_selection.size());
      }

      //cout << "\t[Paso 7] Calculando dmin.\n"; // DEBUG

      for (unsigned i = 0; i < unselected.size(); ++i) {
        vector<pair<unsigned, float>> distances = sorted_distances(problem_, unselected[i]);
        unselected_dmin[i] = calculate_dmin(problem_, unselected, distances, m_value_ - current_selection.size());
      }

      //cout << "\t[Paso 8] Verificando que el nodo es bueno.\n"; // DEBUG

      for (unsigned j = 0; j < current_selection.size(); ++j) { // (8)
        for (unsigned i = 0; i < unselected.size(); ++i) {
          //cout << "Accessing " << i << " of " << unselected.size() << endl; // DEBUG
          //cout << "Accessing " << j << " of " << current_selection.size() << endl; // DEBUG
          if (selection_dmax[j] < unselected_dmin[i]) {
            tree.pop(); // (9)
            node_removed = true;
            break;
          }
        }
        if (node_removed) break;
      }      

      if (!node_removed) {

        //cout << "\t[Paso 10] Nodo no podado. Calculando cota...\n"; // DEBUG

        ChangeSelected(current_selection, selected_elements);
        float upper_bound = CalculateUpperBound(current_selection, all_elements_indexes, selected_elements); // (10)
        ChangeSelected(current_selection, selected_elements);

        //cout << "\t[Paso 12] Obteniendo mejores elementos a añadir...\n"; // DEBUG

        vector<unsigned> best_elements = GetBestElements(unselected, all_elements_indexes, selected_elements, m_value_ - current_selection.size()); // (12)

        for (const unsigned& e : best_elements) { current_selection.push_back(e); }

        //cout << "\t[Paso 12] Calculando Z del nodo actual...\n"; // DEBUG
        
        float current_z = CalculateZ(current_selection); // (12)

        cout << "\t[Paso 13] Verificando Z del nodo actual...\n"; // DEBUG
        
        if (current_z > lower_bound) {
          cout << "\t[Paso 13] Actualizando Z...\n"; // DEBUG
          lower_bound = current_z; // (13) LB = z'
        }
        if (upper_bound < lower_bound) {

          cout << "\t[Paso 14] Eliminando nodo...\n"; // DEBUG

          tree.pop(); // (14) Remove Node
        } else if(current_z < upper_bound) {

          cout << "\t[Paso 15] Calculando cota mejorada...\n"; // DEBUG

          float best_upper_bound = current_z;

          for (unsigned i = 0; i < best_elements.size(); ++i) {
            vector<unsigned> new_solution = current_selection;
            new_solution.push_back(best_elements[i]);
            //ChangeSelected(new_solution, selected_elements);
            //cout << "ola\n";
            float current_bound = CalculateUpperBound(new_solution, all_elements_indexes, selected_elements);
            //ChangeSelected(new_solution, selected_elements);
            if (current_bound < best_upper_bound) {
              best_upper_bound = current_bound;
            }
          }
          if (best_upper_bound < lower_bound) {
            tree.pop(); // (16)
          }
        } else { // (17) Add child nodes to ActiveNodes
          cout << "[Paso 17] Adding child nodes...\n";

          for(const unsigned& e : all_elements_indexes) {
            vector<unsigned> current_solution = current_selection; //tree[0].solution_;
            current_solution.push_back(e);
            //tree.push(Node(current_solution, i));    
            ChangeSelected(current_solution, selected_elements);
            tree.push(Node(current_solution, e));
            ChangeSelected(current_solution, selected_elements);
            generated_nodes_ ++;
          }
        }
      }
    }
  }

  return best_solution;
}