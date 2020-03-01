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
	string inputFile;
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
	arg.inputFile = argv[1];
	return arg;
}

bool GetMatrixFromFile(istream& inputStream, Matrix matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(inputStream >> matrix[i][j]))
			{
				cout << "Cannot get matrix from file" << endl;
				return false;
			}
		}
	}
	return true;
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

double CalculateDeterminant(const Matrix &matrix)
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

void TransposeAndCalculateUnionMatrix(const Matrix& sourceMatrix, Matrix& transposedMatrix)
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
void CalculateFinalMatrixAndPrintResult(Matrix intermidiateMatrix, const double determinant)
{
	cout.setf(ios::fixed);
	double result;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			result = intermidiateMatrix[i][j] / determinant;
			if (result == -0.0f)
			{
				result = 0.0f;
			}
			cout << setprecision(3) << result << "\t";
		}
		cout << endl;
	}
}

bool InvertMatrix(Matrix& sourceMatrix)
{
	double determinant;
	determinant = CalculateDeterminant(sourceMatrix);
	if (determinant == 0)
	{
		cout << "Determinant equals to 0. Cannot calculate invetred matrix." << endl;
		return false;
	}

	Matrix intermidiateMatrix;
	TransposeAndCalculateUnionMatrix(sourceMatrix, intermidiateMatrix);
	CalculateFinalMatrixAndPrintResult(intermidiateMatrix, determinant);
	return true;
}

int main(int argc, char* argv[])
{
	auto arg = GetArgument(argc, argv);
	if (!arg)
	{
		return 1;
	}
	ifstream inputFile;
	if (!OpenFile(inputFile, arg->inputFile))
	{
		return 1;
	}
	Matrix matrix3x3;
	if (!GetMatrixFromFile(inputFile, matrix3x3))
	{
		return 1;
	}
	if (!InvertMatrix(matrix3x3))
	{
		return 1;
	}
}
