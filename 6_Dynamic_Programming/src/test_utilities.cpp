/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Mar 19 2023
 *
 * @brief Utility functions.
 */

#include "test_utilities.h"

/**
* @brief Execute TSP algorithms and measure the time taken by each of them.
* @param files - graphs on 'txt' files
* @param start_node - node identifier
*/
void test_tsp_algorithms(const string& start_node, const vector<string>& algorithm_names, bool symmetric_matrix) {  
  vector<pair<string, unsigned>> files = create_graphs_files( 3,
                                              pair<unsigned, unsigned>(5, 50),
                                              pair<unsigned, unsigned>(3, 6));
  //files.insert(files.begin(), "./input/example1.txt");
  Table table(algorithm_names);
  vector<AlgorithmMeasurement> measures;
  for (unsigned i = 0; i < files.size(); ++i) {
    measures.clear();
    measures.push_back(test_algorithm(new GreedyTSP(symmetric_matrix), files[i].first, start_node, files[i].second));
    measures.push_back(test_algorithm(new BruteForceTSP(symmetric_matrix), files[i].first, start_node, files[i].second));    
    measures.push_back(test_algorithm(new DynamicProgrammingTSP(symmetric_matrix), files[i].first, start_node, files[i].second));
    table.AddRow(TableRow(files[i].first, measures, files[i].second));
  }
  table.Show();
  cout << " MODIFICACION: " << endl;
  table.Show_MOD();
}

/**
 * @brief Test the performance of a TSP algorithm using the given instance file and starting node.
 * @param tsp_algorithm Pointer to the TSP algorithm instance.
 * @param filename Name of the instance file.
 * @param start_node Name of the starting node.
 * @return AlgorithmMeasurement Performance measurement containing the solution value, execution time, and minimum path.
 */
AlgorithmMeasurement test_algorithm(TSP* tsp_algorithm, const string& filename, const string& start_node, unsigned node_amount) {
  auto start = Clock::now();
  tsp_algorithm->CreateFromFile(filename);
  int value = tsp_algorithm->Solve(start_node);
  //cout << tsp_algorithm->Solve(start_node) << "\t  ";  //cout << endl; tsp_solver->ShowAdjacencyMatrix(); cout << endl;

  auto stop = Clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);  
  double time = duration.count(); //cout << duration.count() << "\t";
  string path = concatenate_strings(tsp_algorithm->GetMinimumPath()); //tsp_algorithm->ShowMinimumPath(); cout << "\t";  
  return AlgorithmMeasurement(value, time, path, node_amount);
}

/**
* @brief Create multiple 'txt' files with 4-sized and random weighted graphs
* @param graphs_per_node_amount - number of files to create per node amount
* @param distances - minimum weight and maximum weight
* @param nodes - minimum amount of nodes and maximum amount
* @return list with the names of all files created
*/
vector<pair<string, unsigned>> create_graphs_files(const unsigned& graphs_per_node_amount, const pair<unsigned, unsigned>& distances, const pair<unsigned, unsigned>& nodes) {
  vector<pair<string, unsigned>> files_created;
  for (unsigned i = nodes.first; i <= nodes.second; ++i) {
    for (unsigned j = 1; j <= graphs_per_node_amount; ++j) { // Para cada cantidad se hacen 3 tests
      files_created.push_back(
        pair<string, unsigned> (
          create_random_graph("example" + to_string(j) + "_" + to_string(i), i, distances),
          i
        ));
    }    
  }
  return(files_created);
}

/**
* @brief Create a 'txt' file with a 4-sized and random weighted graph
* @param filename - name of the file to create
* @param minimum_distance - minimum weight
* @param maximum_distance - maximum weight
* @return name of the file created
*/
string create_random_graph(const string& filename, unsigned nodes, const pair<unsigned, unsigned>& distances) {  
  string text_line;
  string file_created = kInputFolderPath + filename + kInputFileExtension;
  ofstream graph_file(file_created);
  unsigned distance_range = distances.second - distances.first + 1;
  vector<string> nodes_names;
  for (unsigned i = 0; i < nodes; ++i) nodes_names.push_back(string(1, (char)('A' + i)));
  if (graph_file.is_open()) {    
		graph_file << nodes << endl;
    for (unsigned i = 0; i < nodes; ++i) {
      for (unsigned j = i + 1; j < nodes; ++j) {
        graph_file << nodes_names[i] +  " " + nodes_names[j] + " " << distances.first + (rand() % distance_range) << endl;
      }
    }
	}
	graph_file.close();
  return(file_created);
}
// *************************************************************************************************************************************************
// ************************************************************ MODIFICACION 19/03/2024 ************************************************************
// *************************************************************************************************************************************************
/** @brief Display the table. */
void Table::Show_MOD() {
  std::sort(node_amounts_.begin(), node_amounts_.end()); // Elimina los elementos duplicados    
  node_amounts_.erase(std::unique(node_amounts_.begin(), node_amounts_.end()), node_amounts_.end());

  Table new_table(algorithm_names_);
  vector<AlgorithmMeasurement> measures;
  vector<pair<int, int>> new_measures;

  for (unsigned i = 0; i < this->node_amounts_.size(); ++i) { // Para cada cantidad de nodos...
    measures.clear(); 
    new_measures.clear();
    new_measures.resize(algorithm_names_.size());   
    // Para cada fila con ESA cantidad de nodos...  
    for (const TableRow& t : table_rows_) {
      if (t.node_amount_ == node_amounts_[i]) {
        for (unsigned j = 0; j < t.algorithm_measures_.size(); ++j) {
          new_measures[j].first += t.algorithm_measures_[j].value_;
          new_measures[j].second += t.algorithm_measures_[j].time_;
        }
      }
    }

    for ( auto& a : new_measures) {
      a.first /= algorithm_names_.size();
      a.second /= algorithm_names_.size();
      measures.push_back(AlgorithmMeasurement(a.first, a.second, to_string(node_amounts_[i]), node_amounts_[i]));
    }
    new_table.AddRow(TableRow(to_string(node_amounts_[i]), measures ,node_amounts_[i]));
  }
  new_table.Show();
}
// *************************************************************************************************************************************************
// *************************************************************************************************************************************************
// *************************************************************************************************************************************************

/** @brief Display the table. */
void Table::Show() {
  const string RESET = "\033[0m";
  const string BOLD = "\033[1m";
  const string UNDERLINE = "\033[4m";

  cout << UNDERLINE << setfill(' ') << setw(total_width) << "" << setfill(' ') << RESET << endl;
  
  // Header. Table columns name
  cout << BOLD  << left << "|" << setw(instance_width) << "Instancia" << "|";
  for (const string& name : algorithm_names_) {
    cout << setw(column_width) << name + " (valor)" << "|"
         << setw(column_width) << name + " (" + kMicro + "s)"    << "|";
         //<< setw(column_width) << name + " (path)"  << "|";
  }
  cout << endl << UNDERLINE << setfill(' ') << setw(total_width) << "" << setfill(' ') << RESET << endl;

  // Content. Table rows
  for (const TableRow& row : table_rows_) {
    cout << "|" << left << setw(instance_width)
         << remove_subsequences(row.instance_, vector<string> { kInputFolderPath, kInputFileExtension })
         << "|";
    for (const AlgorithmMeasurement& measure : row.algorithm_measures_) {
      string value, time, path;
      if (measure.time_ == kExecutionTimeCode) {
        value = "-";
        time  = "EXCESIVO";
        //path  = "-";
      } else {
        value = to_string(measure.value_);
        time = to_string(measure.time_);
        //path  = measure.path_;
      }
      
      cout << left  << setw(column_width) << value << "|"
                    << setw(column_width) << time  << "|";
                    //<< setw(column_width) << path  << "|";
    }
    cout << endl;
  }
  cout << UNDERLINE << setfill(' ') << setw(total_width) << "" << setfill(' ') << endl << RESET << endl;
}

