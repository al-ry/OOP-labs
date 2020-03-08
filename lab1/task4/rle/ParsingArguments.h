#pragma once

#include "stdafx.h"
enum class Mode
{
	PACKING_MODE,
	UNPACKING_MODE,
};
struct Args
{
	Mode mode;
	string inputFileName;
	string outputFileName;
};


const int ARGUMENTS_COUNT = 4;

optional<Mode> defineMode(const string& firstArg);
optional<Args> ParseArguments(int argc, char* argv[]);