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
	auto arg = GetArgument(argc, argv);
	Dictionary DictionaryMap;
	Dictionary NewWordsMap;
	if (arg)
	{
		if (!ReadDictionary(arg.value(), DictionaryMap))
		{
			return 1;
		}
	}
	ProcessInputWords(DictionaryMap, NewWordsMap);
	if (!NewWordsMap.empty())
	{
		if (!SaveNewDictionary(IsArgument, arg, NewWordsMap))
		{
			return 1;
		}
	}

	return 0;
}
