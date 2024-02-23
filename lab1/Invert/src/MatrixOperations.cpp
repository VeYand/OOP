#include "../include/MatrixOperations.h"
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> ReadMatrix(const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Cannot open input file");
	}

	std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> matrix{};

	int row = 0;
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (row == MATRIX_SIZE)
		{
			break;
		}
		std::istringstream iss(line);
		for (int col = 0; col < MATRIX_SIZE; ++col)
		{
			int value;
			if (!(iss >> value))
			{
				throw std::runtime_error(std::format("Error reading matrix element at row {}, column {}", std::to_string(row), std::to_string(col)));
			}
			matrix[row][col] = value;
		}
		++row;
	}

	if (row < MATRIX_SIZE)
	{
		throw std::runtime_error("Matrix file does not contain 3 rows");
	}

	if (inputFile.bad())
	{
		throw std::runtime_error("Error reading input file");
	}

	return matrix;
}

void PrintMatrix(const std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE>& matrix)
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

int CalculateDeterminant(const std::array<std::array<int, 2>, 2>& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

int CalculateDeterminant(const std::array<std::array<int, 3>, 3>& matrix)
{
	return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
		- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
		+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

std::array<std::array<int, 2>, 2> GetSubMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix, int rowToRemove, int colToRemove)
{
	std::array<std::array<int, 2>, 2> subMatrix{};
	int subMatrixI = 0;
	int subMatrixJ = 0;

	for (int m = 0; m < MATRIX_SIZE; ++m)
	{
		if (m == rowToRemove)
		{
			continue;
		}

		for (int n = 0; n < MATRIX_SIZE; ++n)
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

std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> GetAlgebraicAdditionsMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix)
{
	std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> algebraicAdditionsMatrix{};

	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			std::array<std::array<int, 2>, 2> subMatrix = GetSubMatrix(matrix, i, j);
			int sign = (i + j) % 2 == 0
				? 1
				: -1;
			algebraicAdditionsMatrix[i][j] = sign * CalculateDeterminant(subMatrix);
		}
	}

	return algebraicAdditionsMatrix;
}

std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> TransposeMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix)
{
	std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> transposedMatrix{};

	for (int col = 0; col < MATRIX_SIZE; ++col)
	{
		for (int row = 0; row < MATRIX_SIZE; ++row)
		{
			transposedMatrix[row][col] = matrix[col][row];
		}
	}

	return transposedMatrix;
}

std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE> InvertMatrix(const std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE>& matrix)
{
	auto determinant = CalculateDeterminant(matrix);
	auto invertedDet = 1 / static_cast<float>(determinant);
	auto algebraicAdditionsMatrix = GetAlgebraicAdditionsMatrix(matrix);
	auto transposedMatrix = TransposeMatrix(algebraicAdditionsMatrix);
	std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE> invertedMatrix{};

	for (int col = 0; col < MATRIX_SIZE; ++col)
	{
		for (int row = 0; row < MATRIX_SIZE; ++row)
		{
			invertedMatrix[row][col] = invertedDet * (float)transposedMatrix[col][row];
		}
	}

	return invertedMatrix;
}