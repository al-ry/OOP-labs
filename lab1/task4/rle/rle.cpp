
#include "stdafx.h"
#include "PackMachine.h"
#include "UnpackMachine.h"
#include "ParsingArguments.h"


int main(int argc, char* argv[])
{
	Mode modeType;
	auto args = ParseArguments(argc, argv, modeType);
	if (!args)
	{
		return 1;
	}
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
	return 0;
}
