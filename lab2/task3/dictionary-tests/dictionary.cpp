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
	while (getline(inputFile, line))
	{
		string word, translation;
		int findPos, indexPos = 0;

		findPos = line.find(SPACE, indexPos);
		word.append(line, indexPos, findPos);
		translation.append(line, findPos + 1, line.length() - findPos);
		dictionary.emplace(word, translation);
		dictionary.emplace(translation, word);
	}
	if (inputFile.bad())
	{
		cout << "Failed for reading data from input dictionary" << endl;
		return false;
	}
	return true;
}

bool SearchInDictionary(const Dictionary& dict, string& inputWord)
{
	transform(inputWord.begin(), inputWord.end(), inputWord.begin(), tolower);
	auto translation = dict.find(inputWord);
	if (translation == dict.end())
	{
		cout << "Unknown word"
			 << "  " << inputWord << ". Enter a translation or empty string for refusing." << endl;
		return false;
	}
	for (auto i = dict.begin(); i != dict.end(); i++)
	{
		if (i->first == inputWord)
		{
			cout << i->second << " ";
		}
	}
	cout << endl;
	return true;
}

void ProccesNewWord(Dictionary& newWordsMap, string& inputWord)
{
	string translation;
	getline(cin, translation);
	if (!translation.empty())
	{
		newWordsMap.emplace(inputWord, translation);
		cout << "Word"
			 << " "
			 << "\"" << inputWord << "\""
			 << " was saved as"
			 << " \"" << translation << "\"" << endl;
	}
	else
	{
		cout << "Word"
			 << " " << inputWord << " was ignored" << endl;
	}
}

void ProcessInputWords(const Dictionary& dict, Dictionary& newWordsMap)
{
	string inputWord;
	while (getline(cin, inputWord) && inputWord != EXIT_VALUE)
	{
		if (dict.empty())
		{
			ProccesNewWord(newWordsMap, inputWord);
		}
		else
		{
			if (!SearchInDictionary(dict, inputWord))
			{
				ProccesNewWord(newWordsMap, inputWord);
			}
		}
	}
}

bool IsNeedToSave()
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
	if (IsNeedToSave())
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
		for (const auto& pair : newWordsMap)
		{
			outputFile << pair.first << " " << pair.second << endl;
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
