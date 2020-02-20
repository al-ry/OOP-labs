
#include <iostream>
#include <fstream>
#include <string>
#include <optional>

using namespace std;

const int ARGUMNETS_COUNT = 5;

struct Args
{
	string inputFilename;
	string outputFileName;
	string searchString;
	string replaceString;
};

optional<Args> ParseArguments(int argc,char *argv[])
{
	if (argc != ARGUMNETS_COUNT)
	{
		cout << "Invalid arguments" << endl;
		cout << "Arguments should be: <input file> <output file> ";
		cout << "<search string> <replace string>" << endl;
		return nullopt;
	}
	Args args;
	args.inputFilename = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	if (args.searchString.empty())
	{
		cout << "Invalid arguments" << endl;
		cout << "Argument <search string> mustn't be empty" << endl;
		return nullopt;
	}
	args.replaceString = argv[4];
	return args;
}

string ReplaceSubstring(const string line, const string searchStr, const string replaceStr)
{
	size_t indexPosition = 0;
	string result;
	while (indexPosition < line.length())
	{
		size_t foundPos = line.find(searchStr, indexPosition);
		if (foundPos != string::npos)
		{
			result.append(line, indexPosition, foundPos - indexPosition);
			result.append(replaceStr);
			indexPosition = foundPos + searchStr.length();
		}
		else
		{
			//Если искомая строка не найдена -> Копирование без замены
			result.append(line, indexPosition, line.length() - indexPosition);
			break;
		}
	}
	return result;
}

bool CopyFileWithReplace(istream& inputStream, ostream& outputStream,
	const string& searchStr, const string& replaceStr)
{
	string line;
	while (getline(inputStream, line))
	{
		outputStream << ReplaceSubstring(line, searchStr, replaceStr) << endl;
	}
	return true;
}


bool HandleStreamAndCopyFileWithReplace(const string &inputStream, const string &outputStream,
	const string &searchStr, const string &replaceStr)
{
	ifstream inputFile;
	inputFile.open(inputStream);

	//Проверка на открытие входного потока
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputStream << " for reading" << endl;
		return false;
	}

	ofstream outputFile;
	outputFile.open(outputStream);

	//Проверка на открытие выходного потока
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputStream << " for writing" << endl;
		return false;
	}

	/// Замена в файле
	if (!CopyFileWithReplace(inputFile, outputFile, searchStr, replaceStr))
	{
		return false;
	}

	//Проверка на нарушения целостности данных входного файла
	if (inputFile.bad())
	{
		cout << "Failed for reading data from input stream" << endl;
		return false;
	}

	//Проверка на нарушения целостности данных выходного файла
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

	if (!HandleStreamAndCopyFileWithReplace(args->inputFilename, args->outputFileName,
											args->searchString, args->replaceString))
	{
		return 1;
	}

	return 0;
}

