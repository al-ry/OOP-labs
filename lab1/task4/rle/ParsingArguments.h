#pragma once

enum class Mode
{
	PACKING_MODE,
	UNPACKING_MODE,
};

struct Args
{
	Mode mode;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Mode> DefineMode(const std::string& firstArg);
std::optional<Args> ParseArguments(int argc, char* argv[]);