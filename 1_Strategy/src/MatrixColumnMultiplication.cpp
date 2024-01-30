#include "MatrixColumnMultiplication.h"

/**
 * @brief Constructor for MatrixColumnMultiplication class.
 * Initializes an instance of the MatrixColumnMultiplication class.
 */
MatrixColumnMultiplication::MatrixColumnMultiplication() {}

/**
 * @brief Performs matrix multiplication by columns. Multiplies two matrices by column-wise traversal.
 * @param left_matrix The left matrix operand.
 * @param right_matrix The right matrix operand.
 * @return The result of the matrix multiplication.
 */
vector<vector<int>> MatrixColumnMultiplication::Solve(const vector<vector<int>>& left_matrix, const vector<vector<int>>& right_matrix) {
  unsigned resultRows = left_matrix.size();
  unsigned resultColumns = right_matrix[0].size();

  vector<vector<int>> result(resultRows, vector<int>(resultColumns));

  for (unsigned col = 0; col < resultColumns; ++col) {
    for (unsigned row = 0; row < resultRows; ++row) {
      int sum = 0;
      for (unsigned i = 0; i < left_matrix[0].size(); ++i) {
        sum += left_matrix[row][i] * right_matrix[i][col];
      }
      result[row][col] = sum;
    }
  }
  return result;
}