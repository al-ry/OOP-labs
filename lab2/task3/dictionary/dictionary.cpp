#include "stdafx.h"
#include "dictionary.h"

using namespace std;

const char SPACE = ' ';
const string EXIT_VALUE = "...";

bool ReadDictionary(const string& dictionatyFileName, Dictionary& dictionary)
{
	ifstream inputFile;
	inputFile.open(dictionatyFileName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << dictionatyFileName << " for reading" << endl;
		return false;
	}
	string line;
	while (!inputFile.eof())
	{
		string word, translation;

		getline(inputFile, word);
		getline(inputFile, translation);
		dictionary.emplace(word, translation);
		dictionary.emplace(translation, word);
	}
	if (inputFile.bad())
	{
		cout << "Failed to reading data from input dictionary" << endl;
		return false;
	}
	return true;
}

bool SearchInDictionary(const Dictionary& dict, const string& inputWord)
{
	auto translation = dict.find(inputWord);
	if (translation == dict.end())
	{
		cout << "Unknown word"
			 << " " << inputWord << ". Enter a translation or empty string for refusing." << endl;
		return false;
	}
	else
	{
		auto eqr = dict.equal_range(inputWord);
		for (auto it = eqr.first; it != eqr.second; ++it)
		{
			cout << it->second << " ";
		}
	}
	cout << endl;
	return true;
}

bool SaveNewWord(Dictionary& dict, Dictionary& newWordsMap, string& inputWord)
{
	string translation;
	getline(cin, translation);
	if (translation.empty())
	{
		cout << "Word"
			 << " "
			 << "\"" << inputWord << "\""
			 << " was ignored" << endl;
		return false;
	}
	else
	{
		dict.emplace(inputWord, translation);
		dict.emplace(translation, inputWord);
		newWordsMap.emplace(inputWord, translation);
		cout << "Word"
			 << " "
			 << "\"" << inputWord << "\""
			 << " was saved as"
			 << " \"" << translation << "\"" << endl;
		return true;
	}
}

void ProcessInputWords(Dictionary& dict, Dictionary& newWordsMap)
{
	string inputWord;
	while (getline(cin, inputWord) && inputWord != EXIT_VALUE)
	{
		if (!SearchInDictionary(dict, inputWord))
		{
			if (!SaveNewWord(dict, newWordsMap, inputWord))
			{
				continue;
			}
		}
	}
}

bool IsNeedsSaving()
{
	string decision;
	getline(cin, decision);
	return decision == "Y" || decision == "y";
}

bool IsArgument(const optional<string>& arg)
{
	if (arg == nullopt)
	{
		return false;
	}
	return true;
}

bool SaveNewDictionary(IsSourceSDictionary fn, const optional<string>& arg,
	const Dictionary& newWordsMap)
{
	cout << "The dictionary was changed. Enter \"Y\" or \"y\" to save changes before leaving." << endl;
	if (IsNeedsSaving())
	{
		ofstream outputFile;
		if (!fn(arg)) // создаем новый словарь
		{
			string dictionaryName;
			cout << "Enter a new dictionary name" << endl;
			cin >> dictionaryName;
			outputFile.open(dictionaryName);
		}
		else //если словарь уже есть, то дописываем в него новые слова
		{
			outputFile.open(arg.value(), ios::app);
		}
		if (!outputFile.is_open())
		{
			cout << "Failed to open " << arg.value() << " for writing" << endl;
			return false;
		}
		for (auto i = newWordsMap.begin(); i != newWordsMap.end(); i++)
		{
			outputFile << i->first << endl;
			outputFile << i->second << endl;
		}
		if (!outputFile.flush())
		{
			cout << "Failed for writing data in output stream" << endl;
			return false;
		}
		cout << "The changes were successfully saved. Check file out."
			 << " Goodbye" << endl;
	}
	else
	{
		cout << "The changes weren't saved."
			 << " Goodbye" << endl;
	}
	return true;
}
