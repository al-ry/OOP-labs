
#include "stdafx.h"
#include "PackMachine.h"
#include "UnpackMachine.h"
#include "ParsingArguments.h"


int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);
	if (!args)
	{
		return 1;
	}
	if (args->mode == Mode::PACKING_MODE)
	{
		if (!PackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	else if (args->mode == Mode::UNPACKING_MODE)
	{
		if (!UnpackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	return 0;
}
