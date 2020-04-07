#include "stdafx.h"
#include "dictionary.h"

using namespace std;

optional<string> GetArgument(int argc, char* argv[])
{
	string arg;
	if (argc != 2)
	{
		return nullopt;
	}
	arg = argv[1];
	return arg;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	auto sourceDictionaryFile = GetArgument(argc, argv);
	Vocabluary dictionary;
	if (!sourceDictionaryFile)
	{
		return 1;
	}
	if (!ReadDictionary(sourceDictionaryFile.value(), dictionary.dictionaryMap))
	{
		return 1;
	}
	ProcessInputWords(dictionary);
	if (!dictionary.newWordsMap.empty())
	{
		if (!UpdateDictionary(sourceDictionaryFile.value(), dictionary.newWordsMap))
		{
			return 1;
		}
	}

	return 0;
}
