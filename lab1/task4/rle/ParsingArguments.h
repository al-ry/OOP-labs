#pragma once

#include "stdafx.h"
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
};

const int ARGUMENTS_COUNT = 4;

bool defineMode(const string& firstArg, Mode& modeType);
optional<Args> ParseArguments(int argc, char* argv[], Mode& modeType);