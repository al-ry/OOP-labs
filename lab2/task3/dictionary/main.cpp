#include "stdafx.h"
#include "dictionary.h"

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
	multimap<string, string> DictionaryMap;
	multimap<string, string> NewWordsMap;
	if (arg)
	{
		if (!ReadDictionary(arg.value(), DictionaryMap))
		{
			return 1;
		}
	}
	bool areNewWords = false;
	ProcessInputWords(DictionaryMap, NewWordsMap, areNewWords);
	if (areNewWords)
	{
		SaveNewDictionary(NewWordsMap, arg.value());
	}

	return 0;
}
