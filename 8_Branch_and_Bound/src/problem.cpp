/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 19 2024
 *
 * @brief Problem class implementation.
 */

#include "problem.h"

/**
 * @brief Create the Maximum Diversity instance from a 'txt' file. 
 * @param filename - name/path of the file
 */
void Problem::CreateFromFile(const string& filename) {
  elements_.resize(0);
  ifstream file(filename);
  unsigned number_of_elements;

  if (!file) {
    cerr << "No se pudo abrir el archivo " << filename << endl;
    exit(1);
  }
  file >> number_of_elements >> dimension_;  
  string line;
  getline(file, line); // Consumir la línea vacía después de leer K
  for (unsigned i = 0; i < number_of_elements; ++i) {
    getline(file, line);
    stringstream ss(line);
    vector<float> element;
    float value;
    while (ss >> value) {
      element.push_back(value);
    }
    elements_.push_back(Element(element));
  }
  file.close();
}

/** @brief Prints the problem information: elements and their dimension */
void Problem::ShowInfo() {
  cout << "Elements: " << elements_.size() << endl; 
  cout << "Dimension: " << dimension_ << endl; 
  for (unsigned i = 0; i < elements_.size(); ++i) {
    for (unsigned j = 0; j < dimension_; ++j) {
      cout << elements_[i].GetDimensionValue(j);
      if (j < (dimension_ - 1)) cout << ", ";
    } cout << endl;
  } cout << endl;
}