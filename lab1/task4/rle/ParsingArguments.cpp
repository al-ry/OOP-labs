#include "stdafx.h"
#include "ParsingArguments.h"

bool defineMode(const string& firstArg, Mode& modeType)
{
	if (firstArg == "pack")
	{
		modeType = PACKING_MODE;
		return true;
	}
	if (firstArg == "unpack")
	{
		modeType = UNPACKING_MODE;
		return true;
	}
	return false;
}
optional<Args> ParseArguments(int argc, char* argv[], Mode& modeType)
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
	if (!defineMode(args.mode, modeType))
	{
		cout << "Incorrect mode. Argument <mode>. Should be either <pack> or <unpack>.";
		return nullopt;
	}
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	return args;
}