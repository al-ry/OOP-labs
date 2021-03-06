#include "stdafx.h"
#include "ParsingArguments.h"

using namespace std;
const int ARGUMENTS_COUNT = 4;

optional<Mode> DefineMode(const string& firstArg)
{
	if (firstArg == "pack")
	{
		return Mode::PACKING_MODE;
	}
	if (firstArg == "unpack")
	{
		return Mode::UNPACKING_MODE;
	}
	return nullopt;
}
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
	auto mode = DefineMode(argv[1]);
	if (!mode)
	{
		cout << "Incorrect mode. Argument <mode>. Should be either <pack> or <unpack>.";
		return nullopt;
	}
	args.mode = mode.value();
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	return args;
}