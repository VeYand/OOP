#include <array>
#include <optional>
#include <string>

#ifndef INVERT_INCLUDE_MATRIXOPERATIONS_H
#define INVERT_INCLUDE_MATRIXOPERATIONS_H

using SquareMatrix3 = std::array<std::array<float, 3>, 3>;

SquareMatrix3 ReadMatrix(const std::string& inputFileName);
void PrintMatrix(const SquareMatrix3& matrix);
std::optional<SquareMatrix3> InvertMatrix(const SquareMatrix3& matrix);

#endif // INVERT_INCLUDE_MATRIXOPERATIONS_H
