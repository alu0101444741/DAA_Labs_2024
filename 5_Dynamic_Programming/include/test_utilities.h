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
 * 
 */
#ifndef TEST_UTILITIES_H_
#define TEST_UTILITIES_H_

#include <iomanip> // Table creation

#include "bruteforce_tsp.h"
#include "greedy_tsp.h"
#include "dynamic_programming_tsp.h"

using namespace std;

const string kMicro = "\u00B5";

/** @brief Class representing measurements of an algorithm's performance. */
class AlgorithmMeasurement {
public:
  int value_;
  int time_;
  string path_;
  /**
   * @brief Constructor for AlgorithmMeasurement.
   * @param value Value measured.
   * @param time Time taken for execution.
   * @param path Path associated with the measurement.
   */
  AlgorithmMeasurement(int value, int time, string path) : 
          value_(value), time_(time), path_(path) {}
};

/** @brief Class representing a row in the table. */
class TableRow {
public:
    string instance_;
    vector<AlgorithmMeasurement> algorithm_measures_;
    /**
     * @brief Constructor for TableRow.
     * @param instance Instance information.
     * @param algorithm_measures Measurements for each algorithm.
     */
    TableRow(string instance, vector<AlgorithmMeasurement> algorithm_measures) :
            instance_(instance), algorithm_measures_(algorithm_measures) {}
};

/** @brief Class representing a table. */
class Table {
private:
  vector<string> algorithm_names_;
  vector<TableRow> table_rows_;
  unsigned instance_width = 12, column_width = 15;
  unsigned total_width;

public:
  /**
   * @brief Constructor for Table.
   * @param algorithm_names Names of algorithms.
   */
  Table(const vector<string>& algorithm_names) : algorithm_names_(algorithm_names) { total_width = column_width * 10 + algorithm_names.size() * 3; }

  /**
   * @brief Add a new row to the table.
   * @param new_row The row to add.
   */
  void AddRow(const TableRow& new_row) { table_rows_.push_back(new_row); }

  /** @brief Display the table. */
  void Show();
};

/**
 * @brief Test the performance of a TSP algorithm using the given instance file and starting node.
 * @param tsp_algorithm Pointer to the TSP algorithm instance.
 * @param filename Name of the instance file.
 * @param start_node Name of the starting node.
 * @return AlgorithmMeasurement Performance measurement containing the solution value, execution time, and minimum path.
 */
AlgorithmMeasurement test_algorithm(TSP* tsp_algorithm, const string& filename, const string& start_node);

/**
* @brief Execute TSP algorithms and measure the time taken by each of them.
* @param files - graphs on 'txt' files
* @param start_node - node identifier
* @param symmetric_matrix
*/
void test_tsp_algorithms(const string& start_node, const vector<string>& algorithm_names, bool symmetric_matrix);


/**
* @brief Create multiple 'txt' files with 4-sized and random weighted graphs
* @param graph_amount - number of files to create
* @param distances - minimum weight and maximum weight
* @param nodes - minimum amount of nodes and maximum amount
* @return list with the names of all files created
*/
vector<string> create_graphs_files(const unsigned& graphs_amount, const pair<unsigned, unsigned>& distances, const pair<unsigned, unsigned>& nodes);

/**
* @brief Create a 'txt' file with a 4-sized and random weighted graph
* @param filename - name of the file to create
* @param minimum_distance - minimum weight
* @param maximum_distance - maximum weight
* @return name of the file created
*/
string create_random_graph(const string& filename, unsigned nodes, const pair<unsigned, unsigned>& distances);


#endif // TEST_UTILITIES_H_