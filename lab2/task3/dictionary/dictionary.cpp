#include "stdafx.h"
#include "dictionary.h"

using namespace std;

const char SPACE = ' ';
const string EXIT_VALUE = "...";

bool ReadDictionary(const std::string& dictionatyFileName, Dictionary& sourceDict)
{
	ifstream inputFile;
	inputFile.open(dictionatyFileName);
	if (!inputFile.is_open())
	{
		return true;
	}
	string line;
	while (!inputFile.eof())
	{
		string word, translation;

		getline(inputFile, word);
		getline(inputFile, translation);
		sourceDict.emplace(word, translation);
		sourceDict.emplace(translation, word);
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
	if (auto translation = dict.find(inputWord); translation == dict.end())
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

Dictionary SaveNewWord(Vocabluary& dict, const string& inputWord)
{
	string translation;
	getline(cin, translation);
	if (translation.empty())
	{
		cout << "Word"
			 << " "
			 << "\"" << inputWord << "\""
			 << " was ignored" << endl;
		return dict.newWordsMap;
	}
	else
	{
		dict.dictionaryMap.emplace(inputWord, translation);
		dict.dictionaryMap.emplace(translation, inputWord);
		dict.newWordsMap.emplace(inputWord, translation);
		cout << "Word"
			 << " "
			 << "\"" << inputWord << "\""
			 << " was saved as"
			 << " \"" << translation << "\"" << endl;
		return dict.newWordsMap;
	}
}

void ProcessInputWords(Vocabluary &dict)
{
	string inputWord;
	while (getline(cin, inputWord) && inputWord != EXIT_VALUE)
	{
		if (!SearchInDictionary(dict.dictionaryMap, inputWord))
		{
			dict.newWordsMap = SaveNewWord(dict, inputWord);
		}
	}
}

bool IsNeedsSaving()
{
	cout << "The dictionary was changed. Enter \"Y\" or \"y\" to save changes before leaving." << endl;
	string decision;
	getline(cin, decision);
	return decision == "Y" || decision == "y";
}

bool WriteNewWordsInFile(const string fileName, const Dictionary& newWordsMap)
{
	ofstream outputDictionary;
	outputDictionary.open(fileName, ios::app);

	if (!outputDictionary.is_open())
	{
		cout << "Failed to open " << fileName << " for writing data."
			 << endl;
		return false;
	}
	for (const auto& [word, translation] : newWordsMap)
	{
		outputDictionary << word << endl
						 << translation << endl;
	}
	if (!outputDictionary.flush())
	{
		cout << "Failed for writing data in output stream" << endl;
		return false;
	}
	return true;
}

bool UpdateDictionary(string &fileName, const Dictionary& newWordsDict)
{
	if (IsNeedsSaving())
	{
		ofstream outputFile;
		if (!WriteNewWordsInFile(fileName, newWordsDict))
		{
			return false;
		}
		else
		{
			cout << "The changes were successfully saved. Check file out."
				 << " Goodbye" << endl;
			return true;	
		}
	}
	else
	{
		cout << "The changes weren't saved."
			 << " Goodbye" << endl;
	}
	return true;
}
