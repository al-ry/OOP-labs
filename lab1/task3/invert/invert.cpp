#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

const int MATRIX_SIZE = 3;
const int MINOR_MATRIX_SIZE = 2;

struct Argument
{
	string inputFileName;
};
typedef double Matrix[MATRIX_SIZE][MATRIX_SIZE];
typedef double MinorMatrix[MINOR_MATRIX_SIZE][MINOR_MATRIX_SIZE];
optional<Argument> GetArgument(int argc, char* argv[])
{
	Argument arg;
	if (argc != 2)
	{
		cout << "Invalid arguments" << endl;
		cout << "Arguments should be: <input matrix>";
		return nullopt;
	}
	arg.inputFileName = argv[1];
	return arg;
}

bool OpenFile(ifstream& file, const string& inputFileName)
{
	file.open(inputFileName);
	//Проверка на открытие входного потока
	if (!file.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading" << endl;
		return false;
	}
	return true;
}

bool GetMatrixFromFile(const string& inputFileName, Matrix& matrix)
{
	ifstream inputFile;
	if (!OpenFile(inputFile, inputFileName))
	{
		return false;
	}
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(inputFile >> matrix[i][j]))
			{
				cout << "Cannot get matrix from file" << endl;
				return false;
			}
		}
	}
	return true;
}

double GetMinor(const Matrix& matrix, int column, int row)
{
	MinorMatrix matrixMinor;
	for (int i = 0, m = 0; i < MATRIX_SIZE; i++)
	{
		if (column != i)
		{
			for (int j = 0, n = 0; j < MATRIX_SIZE; j++)
			{
				if ((row != j))
				{
					matrixMinor[m][n] = matrix[i][j];
					n++;
				}
			}
			m++;
		}
	}
	return matrixMinor[0][0] * matrixMinor[1][1] - matrixMinor[1][0] * matrixMinor[0][1];
}

double CalculateDeterminant(const Matrix& matrix)
{
	double resultDeterminant = 0;
	int sign = 1;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		resultDeterminant += matrix[0][i] * sign * GetMinor(matrix, 0, i);
		sign *= -1;
	}
	return resultDeterminant;
}

void CalculateTransposedAdjugateMatrix(const Matrix& sourceMatrix, Matrix& transposedMatrix)
{
	int sign = 1;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			transposedMatrix[j][i] = sign * GetMinor(sourceMatrix, i, j);
			sign *= -1;
		}
	}
}
void CalculateInvertedMatrix(Matrix& intermidiateMatrix, const double determinant)
{
	cout.setf(ios::fixed);
	double result;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			intermidiateMatrix[i][j] = intermidiateMatrix[i][j] / determinant;
			if (intermidiateMatrix[i][j] == -0.0f)
			{
				intermidiateMatrix[i][j] = 0.0f;
			}
		}
	}
}

bool InvertMatrix(const Matrix& sourceMatrix, Matrix& resultMatrix)
{
	double determinant;
	determinant = CalculateDeterminant(sourceMatrix);
	if (determinant == 0)
	{
		cout << "Determinant equals to 0. Cannot calculate invetred matrix." << endl;
		return false;
	}

	CalculateTransposedAdjugateMatrix(sourceMatrix, resultMatrix);
	CalculateInvertedMatrix(resultMatrix, determinant);
	return true;
}

void PrintMatrix(const Matrix &resultMatrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			cout << setprecision(3) << resultMatrix[i][j] << "\t";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	auto arg = GetArgument(argc, argv);
	if (!arg)
	{
		return 1;
	}
	Matrix matrix3x3;
	if (!GetMatrixFromFile(arg->inputFileName, matrix3x3))
	{
		return 1;
	}
	Matrix resultMatrix;
	if (!InvertMatrix(matrix3x3, resultMatrix))
	{
		return 1;
	}
	PrintMatrix(resultMatrix);
}
