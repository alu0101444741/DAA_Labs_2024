#ifndef MATRIX_ROW_MULT_H
#define MATRIX_ROW_MULT_H

#include "MatrixMultiplication.h"

class MatrixRowMultiplication : public MatrixMultiplication {
public:

	/**
	 * @brief Constructor for MatrixRowMultiplication class.
	 * Initializes an instance of the MatrixRowMultiplication class.
	 */
	MatrixRowMultiplication();

	/**
	 * @brief Performs matrix multiplication by rows. Multiplies two matrices by row-wise traversal.
	 * @param left_matrix The left matrix operand.
	 * @param right_matrix The right matrix operand.
	 * @return The result of the matrix multiplication.
	 */
	vector<vector<int>> Solve(const vector<vector<int>>& left_matrix, const vector<vector<int>>& right_matrix) override;
};

#endif // MATRIX_ROW_MULT_H
