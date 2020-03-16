#include "stdafx.h"
#include "UnpackMachine.h"

using namespace std;

bool IsEvenFileSize(istream& inputFile)
{
	streamoff fileSize = 0;
	streamoff prevPosition;

	prevPosition = inputFile.tellg();
	inputFile.seekg(0, inputFile.end);
	fileSize = inputFile.tellg();

	if (fileSize % 2 != 0)
	{
		return false;
	}

	inputFile.seekg(prevPosition);
	return true;
}

void UnpackData(istream& inputFile, ostream& outputFile)
{
	char data = 0;
	uint8_t byteAmount = 0;
	size_t repeatAmount = 0;
	while (inputFile.read(&data, sizeof(char)))
	{
		byteAmount = data;
		repeatAmount = byteAmount;
		inputFile.read(&data, sizeof(char));
		for (size_t i = 0; i < repeatAmount; i++)
		{
			outputFile.put(data);
		}
	}
}

bool UnpackFile(const string& inputFileName, const string& outputFileName)
{
	ifstream inputFile;
	ofstream outputFile;
	inputFile.open(inputFileName, ios::binary);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading" << endl;
		return false;
	}
	outputFile.open(outputFileName, ios::binary);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing" << endl;
		return false;
	}
	if (!IsEvenFileSize(inputFile))
	{
		cout << "File size is not even. Cannot unpack input file.";
		return false;
	}

	UnpackData(inputFile, outputFile);

	if (inputFile.bad())
	{
		cout << "Failed to reading data from input stream" << endl;
		return false;
	}

	if (!outputFile.flush())
	{
		cout << "Failed to writing data in output stream" << endl;
		return false;
	}
	return true;
}