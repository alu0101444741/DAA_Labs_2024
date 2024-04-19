/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief TSP solver class implementation.
 * 
 */

#include "tsp.h"

/**
 * @brief Create the tree from a 'txt' file. 
 * @param filename - name/path of the file
 */
void TSP::CreateFromFile(const string& filename) {
  string text_line, line_part, string_control;
  ifstream text_file (filename);
  if (text_file.is_open()) {
    // Nodes amount
		getline (text_file, text_line);
    unsigned nodes_amount = stoi(text_line);
		this->node_names_ = vector<string>(nodes_amount);
    for (unsigned i = 0; i < nodes_amount; ++i) {
      this->node_names_[i] = string(1, 'A' + i);
    }
    // Distances
    while (text_file >> string_control) {
      getline (text_file, text_line);
      istringstream current_line(text_line);
      getline(current_line, line_part, ' ');
      string node_start = string_control;
      getline(current_line, line_part, ' ');
      string node_end = line_part;
      getline(current_line, line_part, ' ');
      unsigned distance = stoi(line_part);
      pair<string, string> nodes(node_start, node_end);
      pair<pair<string, string>, unsigned> connection(nodes, distance);
      this->distances_.push_back(connection);
		}
	}	
  this->CreateAdjacencyMatrix();
}

/** @brief Create the adjacency matrix from the stored node data. */
void TSP::CreateAdjacencyMatrix() {  
  unsigned matrix_size = this->node_names_.size();
  for (unsigned i = 0; i < matrix_size; ++i) {
    this->adjacency_matrix_.push_back(vector<int>(matrix_size));
  }

  for (unsigned i = 0; i < matrix_size; ++i) {
    for (unsigned j = 0; j < matrix_size; ++j) {
      this->adjacency_matrix_[i][j] = DistanceBetweenNodes(node_names_[i], node_names_[j]);    
    }
  }
}

/**
 * @brief Find the distance between two given nodes
 * @param start_node
 * @param end_node
 * @return distance between the nodes
 */
unsigned TSP::DistanceBetweenNodes(const string& start_node, const string& end_node) {
  unsigned size = this->distances_.size();
  if (symetric_adjacency_list_) {
    for (unsigned i = 0; i < size; ++i) {
      if ((this->distances_[i].first.first == start_node) && (this->distances_[i].first.second == end_node)) {
        return(this->distances_[i].second);
      }
      if ((this->distances_[i].first.first == end_node) && (this->distances_[i].first.second == start_node)) {
        return(this->distances_[i].second);
      }
    }
  }
  else {
    for (unsigned i = 0; i < size; ++i) {
      if ((this->distances_[i].first.first == start_node) && (this->distances_[i].first.second == end_node)) {
        return(this->distances_[i].second);
      }
    }
  }  
  return(0);
}

/**
 * @brief Get the index of a node by it identifier 
 * @param node - node identifier
 * @return index
 */
unsigned TSP::GetIndexOfNode(const string& node) {
  unsigned size = this->distances_.size();
  for (unsigned i = 0; i < size; ++ i) {
    if (node_names_[i] == node) return(i);    
  }
  return(size + 10);
}

/** @brief Print the stored graph. */
void TSP::ShowGraph() {
  unsigned size = node_names_.size();
  cout << "Nodes: ";
  for (unsigned i = 0; i < size; ++i){
    cout << node_names_[i];
    if (i < (size - 1)) cout << ", ";
  }
  cout << endl;  
  size = distances_.size();
  cout << "Connections:\n";
  for (unsigned i = 0; i < size; ++i){
    cout << distances_[i].first.first << " " << distances_[i].first.second << " " << distances_[i].second << endl;
  }
}

/** @brief Print the adjacency matrix. */
void TSP::ShowAdjacencyMatrix() {
  unsigned size = node_names_.size();
  cout << "\t";
  for (unsigned i = 0; i < size; ++i)
    cout << node_names_[i] << "\t";
  cout << endl;
  for (unsigned i = 0; i < size; ++i) {
    cout << node_names_[i] << "\t";
    for (unsigned j = 0; j < size; ++j) {
      cout << adjacency_matrix_[i][j] << "\t";
    }
    cout << endl;
  }
}

/**
 * @brief Check if the execution time has exceeded the maximum allowed time.
 * @param start The start time of the execution.
 * @return True if the execution time has exceeded the maximum allowed time, false otherwise.
 */
bool TSP::ExecutionTimeExceeded(const TimePoint& start) {
  auto stop = Clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  return (duration.count() >= kMaximumExecutionTime);
}