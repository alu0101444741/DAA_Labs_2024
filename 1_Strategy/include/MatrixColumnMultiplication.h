#ifndef MATRIX_COLUMN_MULT_H
#define MATRIX_COLUMN_MULT_H

#include "MatrixMultiplication.h"

class MatrixColumnMultiplication : public MatrixMultiplication {
public:

  /**
   * @brief Constructor for MatrixColumnMultiplication class.
   * Initializes an instance of the MatrixColumnMultiplication class.
   */
  MatrixColumnMultiplication();

  /**
   * @brief Performs matrix multiplication by columns. Multiplies two matrices by column-wise traversal.
   * @param left_matrix The left matrix operand.
   * @param right_matrix The right matrix operand.
   * @return The result of the matrix multiplication.
   */
  vector<vector<int>> Solve(const vector<vector<int>>& leftMatrix, const vector<vector<int>>& rightMatrix) override;
};

#endif // MATRIX_COLUMN_MULT_H