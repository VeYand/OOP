#include <array>
#include <string>

#ifndef INVERT_INCLUDE_MATRIXOPERATIONS_H
#define INVERT_INCLUDE_MATRIXOPERATIONS_H

const int MATRIX_SIZE = 3;

std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> ReadMatrix(const std::string& inputFileName);
void PrintMatrix(const std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE>& matrix);
std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> GetAlgebraicAdditionsMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix);
std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> TransposeMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix);
std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE> InvertMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix);

#endif // INVERT_INCLUDE_MATRIXOPERATIONS_H
