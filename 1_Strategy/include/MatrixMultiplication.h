#include <iostream>
#include <vector>
using namespace std;

#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

class MatrixMultiplication {
public:
  virtual vector<vector<int>> Solve(const vector<vector<int>>& left_matrix, const vector<vector<int>>& right_matrix) = 0;
  virtual ~MatrixMultiplication() {}
};

#endif // MATRIX_MULTIPLICATION_H