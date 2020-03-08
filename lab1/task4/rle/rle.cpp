
#include "stdafx.h"
#include "PackMachine.h"
#include "UnpackMachine.h"

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
