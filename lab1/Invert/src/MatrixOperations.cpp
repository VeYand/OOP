#include "../include/MatrixOperations.h"
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using SquareMatrix2 = std::array<std::array<float, 2>, 2>;

SquareMatrix3 ReadMatrix(const std::string& inputFileName)
{
	const int matrixRows = 3;
	const int matrixCols = 3;

	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Cannot open input file");
	}

	SquareMatrix3 matrix{};

	int row = 0;
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (row == matrixRows)
		{
			break;
		}
		std::istringstream iss(line);
		for (int col = 0; col < matrixCols; ++col)
		{
			float value;
			if (!(iss >> value))
			{
				throw std::runtime_error(std::format("Error reading matrix element at row {}, column {}", std::to_string(row), std::to_string(col)));
			}
			matrix[row][col] = value;
		}
		++row;
	}

	if (row < matrixRows)
	{
		throw std::runtime_error("Matrix file does not contain 3 rows");
	}

	if (inputFile.bad())
	{
		throw std::runtime_error("Error reading input file");
	}

	return matrix;
}

void PrintMatrix(const SquareMatrix3& matrix)
{
	for (const auto& row : matrix)
	{
		for (auto column = 0; column < row.size(); ++column)
		{
			std::cout << std::fixed << std::setprecision(3) << row[column];
			if (column < (row.size() - 1))
			{
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}

float CalculateDeterminant(const SquareMatrix2& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

float CalculateDeterminant(const SquareMatrix3& matrix)
{
	return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
		- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
		+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

SquareMatrix2 GetSubMatrix(const SquareMatrix3& matrix, int rowToRemove, int colToRemove)
{
	SquareMatrix2 subMatrix{};
	int subMatrixI = 0;
	int subMatrixJ = 0;

	for (int m = 0; m < matrix.size(); ++m)
	{
		if (m == rowToRemove)
		{
			continue;
		}

		for (int n = 0; n < matrix[m].size(); ++n)
		{
			if (n == colToRemove)
			{
				continue;
			}

			subMatrix[subMatrixI][subMatrixJ] = matrix[m][n];
			++subMatrixJ;
		}

		++subMatrixI;
		subMatrixJ = 0;
	}

	return subMatrix;
}

SquareMatrix3 GetCofactorMatrix(const SquareMatrix3& matrix)
{
	SquareMatrix3 algebraicAdditionsMatrix{};

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			SquareMatrix2 subMatrix = GetSubMatrix(matrix, i, j);
			int sign = (i + j) % 2 == 0
				? 1
				: -1;
			algebraicAdditionsMatrix[i][j] = static_cast<float>(sign) * CalculateDeterminant(subMatrix);
		}
	}

	return algebraicAdditionsMatrix;
}

SquareMatrix3 TransposeMatrix(const SquareMatrix3& matrix)
{
	SquareMatrix3 transposedMatrix{};

	for (int row = 0; row < matrix.size(); ++row)
	{
		for (int col = 0; col < matrix[row].size(); ++col)
		{
			transposedMatrix[row][col] = matrix[col][row];
		}
	}

	return transposedMatrix;
}

std::optional<SquareMatrix3> InvertMatrix(const SquareMatrix3& matrix)
{
	auto determinant = CalculateDeterminant(matrix);

	if (determinant == 0)
	{
		return std::nullopt;
	}

	auto invertedDet = 1 / static_cast<float>(determinant);
	auto algebraicAdditionsMatrix = GetCofactorMatrix(matrix);
	auto transposedMatrix = TransposeMatrix(algebraicAdditionsMatrix);
	SquareMatrix3 invertedMatrix{};

	for (int row = 0; row < matrix.size(); ++row)
	{
		for (int col = 0; col < matrix[row].size(); ++col)
		{
			invertedMatrix[row][col] = invertedDet * static_cast<float>(transposedMatrix[row][col]);
		}
	}

	return invertedMatrix;
}