// rle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

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
	UNPACKING_MODE
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
		cout << "File size is not even. Cannot upack input file.";
		return false;
	}

	inputFile.seekg(prevPosition);
	return true;
}
void PackFile(istream& inputStream, ostream& outputStream)
{
	char ch, prevCh;
	inputStream.read(&ch, sizeof(ch));
	if (inputStream.eof())
	{
		return;
	}
	unsigned char byteCounter = 1;
	prevCh = ch;
	while (inputStream.read(&ch, sizeof(ch)))
	{
		if (prevCh == ch && byteCounter < MAX_PACK)
		{
			byteCounter++;
		}
		else
		{
			outputStream.put(byteCounter);
			outputStream.put(prevCh);
			byteCounter = 1;
			prevCh = ch;
		}
	}
	outputStream.put(byteCounter);
	outputStream.put(prevCh);
}
void UnpackFile(istream& inputStream, ostream& outputStream)
{
	char data = 0;
	unsigned char byteAmount = 0;
	size_t repeatAmount = 0;
	while (inputStream.read(&data, sizeof(char)))
	{
		byteAmount = data;
		repeatAmount = byteAmount;
		inputStream.read(&data, sizeof(char));
		for (size_t i = 0; i < repeatAmount; i++)
		{
			outputStream.put(data);
		}
	}
}
bool OpenFiles(const string& inputFileName, const string& outputFileName,
	ifstream& inputFile, ofstream& outputFile)
{
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
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);
	if (!args)
	{
		return 1;
	}
	ifstream inputFile;
	ofstream outputFile;
	Mode modeType = defineMode(args->mode);
	if (modeType == PACKING_MODE)
	{
		if (!OpenFiles(args->inputFileName, args->outputFileName, inputFile, outputFile))
		{
			return 1;
		}
		PackFile(inputFile, outputFile);
	}
	else if (modeType == UNPACKING_MODE)
	{
		if (!OpenFiles(args->inputFileName, args->outputFileName, inputFile, outputFile))
		{
			return 1;
		}
		if (!IsEvenFileSize(inputFile))
		{
			return 1;
		}
		UnpackFile(inputFile, outputFile);
	}
	else
	{
		cout << "Incorrect <mode>. Argument <mode> should be <pack> or <unpack>" << endl;
		return 1;
	}
	return 0;
}
