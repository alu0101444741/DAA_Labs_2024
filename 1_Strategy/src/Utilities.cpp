#include "Utilities.h"

/**
 * @brief Generates a random matrix of a specified size with values within a given range.
 * @param size The size of the square matrix.
 * @param minimum_value The minimum value for matrix elements.
 * @param maximum_value The maximum value for matrix elements.
 * @return The generated random matrix.
 */
vector<vector<int>> GenerateRandomMatrix(int size, int minimum_value, int maximum_value) {
  vector<vector<int>> matrix(size, vector<int>(size, 0));
  srand(time(0));

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix[i][j] = rand() % (maximum_value - minimum_value + 1) + minimum_value;
    }
  }
  return matrix;
}

/**
 * @brief Tests matrix multiplication with matrices of different sizes.
 * @param initial_size The initial size of the matrices.
 * @param maximum_size The maximum size of the matrices to be tested.
 * @param size_increase The step size for increasing matrix sizes.
 */
void TestMatrixMultiplication(unsigned initial_size, unsigned maximum_size, unsigned size_increase) {
  int maximum_value = 100;
  
  for (unsigned current_size = initial_size; current_size <= maximum_size; current_size += size_increase) {
    // Declarar variables    
    vector<vector<int>> first_matrix = GenerateRandomMatrix(current_size, -maximum_value, maximum_value);
    vector<vector<int>> second_matrix = GenerateRandomMatrix(current_size, -maximum_value, maximum_value);

    // Multiplicación por filas
    unique_ptr<MatrixMultiplication> multiplication = make_unique<MatrixRowMultiplication>();
    cout << "  Size " << to_string(current_size) << endl;
    MeasureExecutionTime("\tMult. by Rows", multiplication, first_matrix, second_matrix);
    // Multiplicación por columnas
    multiplication = make_unique<MatrixColumnMultiplication>();
    MeasureExecutionTime("\tMult. by Columns", multiplication, first_matrix, second_matrix);
  }
}

/**
 * @brief Measures the execution time of matrix multiplication using a given multiplication strategy.
 * @param label A label used to customize the console output message.
 * @param multiplication A unique pointer to the matrix multiplication strategy.
 * @param first_matrix The left matrix operand.
 * @param second_matrix The right matrix operand.
 */
void MeasureExecutionTime(const string& label, unique_ptr<MatrixMultiplication>& multiplication, const vector<vector<int>>& first_matrix, const vector<vector<int>>& second_matrix) {
  auto start = chrono::high_resolution_clock::now();
  vector<vector<int>> result = multiplication->Solve(first_matrix, second_matrix);
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

  cout << label << ". Time:\t" << duration.count() << " ms" << endl;
}

/**
 * @brief Prints a matrix along with a label for identification.
 * @param label A label to identify the printed matrix.
 * @param matrix The matrix to be printed.
 */
void PrintMatrix(const string& label, const vector<vector<int>>& matrix) {
  cout << label << endl;
  for (const auto& row : matrix) {
    for (int value : row) {
      cout << value << " ";
    }
    cout << endl;
  }
}