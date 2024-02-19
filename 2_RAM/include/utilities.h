/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 09 2024
 *
 * @brief Definition of auxiliary functions used in the program.
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum OperandType { INMEDIATO, DIRECTO, INDIRECTO, ETIQUETA };

/**
 * @brief Get the index of a label in a vector of label-index pairs.
 * If the label is found, the function returns its index, otherwise it returns -1.
 * @param labels A vector of pairs representing labels and their corresponding indices.
 * @param label The label to search for.
 * @return The index of the label if found; otherwise, -1.
 */
int get_label_index(const vector<pair<string, unsigned>>& labels, const string& label);

/**
 * @brief Determines the type of operand based on its prefix.
 * @param operand_prefix The prefix of the operand.
 * @return The OperandType of the operand.
 */
OperandType get_operand_type (const string& operand_prefix);

/**
 * @brief Converts an OperandType enum value to its string representation.
 * @param operand_prefix The OperandType enum value.
 * @return The string representation of the OperandType.
 */
string operand_type_to_string (const OperandType& operand_prefix);

/**
 * @brief Removes leading whitespace characters from a string.
 * @param line The string to be trimmed.
 */
void trim_leading_whitespace(string& line);

/**
 * @brief Displays the elements of a vector along with a title.
 * @param array The vector to be displayed.
 * @param title The title to be printed before the vector elements.
 */
void show_vector(const vector<int>& array, const string& title);

#endif // UTILITIES_H