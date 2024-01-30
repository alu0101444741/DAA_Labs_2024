#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <memory>
#include "MatrixMultiplication.h"
#include "MatrixRowMultiplication.h"
#include "MatrixColumnMultiplication.h"
using namespace std;

/**
 * @brief Generates a random matrix of a specified size with values within a given range.
 * @param size The size of the square matrix.
 * @param minimum_value The minimum value for matrix elements.
 * @param maximum_value The maximum value for matrix elements.
 * @return The generated random matrix.
 */
vector<vector<int>> GenerateRandomMatrix(int size, int minValue, int maxValue);

/**
 * @brief Measures the execution time of matrix multiplication using a given multiplication strategy.
 * @param label A label used to customize the console output message.
 * @param multiplication A unique pointer to the matrix multiplication strategy.
 * @param first_matrix The left matrix operand.
 * @param second_matrix The right matrix operand.
 */
void MeasureExecutionTime(const string& label, unique_ptr<MatrixMultiplication>& multiplication, const vector<vector<int>>& firstMatrix, const vector<vector<int>>& secondMatrix);

/**
 * @brief Tests matrix multiplication with matrices of different sizes.
 * @param initial_size The initial size of the matrices.
 * @param maximum_size The maximum size of the matrices to be tested.
 * @param size_increase The step size for increasing matrix sizes.
 */
void TestMatrixMultiplication(unsigned initial_size, unsigned maximum_size, unsigned size_increase);

/**
 * @brief Prints a matrix along with a label for identification.
 * @param label A label to identify the printed matrix.
 * @param matrix The matrix to be printed.
 */
void PrintMatrix(const string& label, const vector<vector<int>>& matrix);

#endif // UTILITIES_H
