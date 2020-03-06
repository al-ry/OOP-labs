
#include "stdafx.h"

using namespace std;

const int MAX_PACK = 0xFF;
const int ARGUMENTS_COUNT = 4;

struct Args
{
	string mode;
	string inputFileName;
	string outputFileName;
};
enum Mode
{
	PACKING_MODE,
	UNPACKING_MODE,
	INCORRECT_MODE
};
optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments" << endl;
		cout << "Arguments should be: <mode><input file> <output file> " << endl;
		cout << "Where <mode> is either <pack> or <unpack>" << endl;
		return nullopt;
	}
	Args args;
	args.mode = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	return args;
}

void WritePacket(ofstream& outputFile, uint8_t byteAmount, uint8_t byte)
{
	outputFile.put(byteAmount);
	outputFile.put(byte);
}

Mode defineMode(const string& firstArg)
{
	if (firstArg == "pack")
	{
		return PACKING_MODE;
	}
	if (firstArg == "unpack")
	{
		return UNPACKING_MODE;
	}
	cout << "Incorrect mode. Argument <mode>. Should be either <pack> or <unpack>.";
	return INCORRECT_MODE;
}
bool IsEvenFileSize(ifstream& inputFile)
{
	streamoff fileSize = 0;
	streamoff prevPosition;

	prevPosition = inputFile.tellg();
	inputFile.seekg(0, inputFile.end);
	fileSize = inputFile.tellg();

	if (fileSize % 2 != 0)
	{
		cout << "File size is not even. Cannot unpack input file.";
		return false;
	}

	inputFile.seekg(prevPosition);
	return true;
}

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

void UnpackData(ifstream& inputFile, ofstream& outputFile)
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
		return false;
	}
	UnpackData(inputFile, outputFile);

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

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);
	if (!args)
	{
		return 1;
	}
	Mode modeType = defineMode(args->mode);
	if (modeType == PACKING_MODE)
	{
		if (!PackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	else if (modeType == UNPACKING_MODE)
	{
		if (!UnpackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	else if (modeType == INCORRECT_MODE)
	{
		return 1;
	}
	return 0;
}
