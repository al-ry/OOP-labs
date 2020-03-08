#include "stdafx.h"
#include "PackMachine.h"


void PackData(ifstream& inputFile, ofstream& outputFile)
{
	uint8_t byte = 0, prevByte = 0, byteCounter = 1;
	char ch;
	inputFile.read(&ch, sizeof(char));
	if (inputFile.eof())
	{
		return;
	}
	byte = ch;
	prevByte = byte;
	while (inputFile.read(&ch, sizeof(char)))
	{
		byte = ch;
		if (prevByte == byte && byteCounter < MAX_PACK)
		{
			byteCounter++;
		}
		else
		{
			WritePacket(outputFile, byteCounter, prevByte);
			byteCounter = 1;
			prevByte = byte;
		}
	}
	WritePacket(outputFile, byteCounter, prevByte);
}
void WritePacket(ofstream& outputFile, uint8_t byteAmount, uint8_t byte)
{
	outputFile.put(byteAmount);
	outputFile.put(byte);
}


bool PackFile(const string& inputFileName, const string& outputFileName)
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

	PackData(inputFile, outputFile);

	if (inputFile.bad())
	{
		cout << "Failed for reading data from input stream" << endl;
		return false;
	}

	if (!outputFile.flush())
	{
		cout << "Failed for writing data in output stream" << endl;
		return false;
	}
	return true;
}


