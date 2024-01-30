#include "MatrixRowMultiplication.h"

/**
 * @brief Constructor for MatrixRowMultiplication class.
 * Initializes an instance of the MatrixRowMultiplication class.
 */
MatrixRowMultiplication::MatrixRowMultiplication() {}

/**
  * @brief Performs matrix multiplication by rows. Multiplies two matrices by row-wise traversal.
  * @param left_matrix The left matrix operand.
  * @param right_matrix The right matrix operand.
  * @return The result of the matrix multiplication.
  */
vector<vector<int>> MatrixRowMultiplication::Solve(const vector<vector<int>>& left_matrix, const vector<vector<int>>& right_matrix) {
  unsigned resultRows = left_matrix.size();
  unsigned resultColumns = right_matrix[0].size();

  vector<vector<int>> result(resultRows, vector<int>(resultColumns));

  for (unsigned row = 0; row < resultRows; ++row) {
    for (unsigned col = 0; col < resultColumns; ++col) {
      int sum = 0;
      for (unsigned i = 0; i < left_matrix[0].size(); ++i) {
        sum += left_matrix[row][i] * right_matrix[i][col];
      }
      result[row][col] = sum;
    }
  }
  return result;
}

