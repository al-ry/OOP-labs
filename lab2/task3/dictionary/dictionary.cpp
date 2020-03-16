#include "stdafx.h"
#include "dictionary.h"

using namespace std;

const char SPACE = ' ';
const string EXIT_VALUE = "...";

bool ReadDictionary(const string& dictionatyFileName, multimap<string, string>& dictionary)
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
	if (dictionary.empty())
	{
		cout << "Empty dictionary.";
		return false;
	}
	return true;
}

bool SearchInDictionary(const multimap<string, string>& dict, const string& inputWord)
{
	auto translation = dict.find(inputWord);
	if (translation == dict.end())
	{
		cout << "Неизвестное слово" << "  " << inputWord << ". Введите перевод или пустую строку для отказа." << endl;
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

void ProccesNewWord(multimap<string, string>& newWordsMap, string& inputWord, bool& newWord)
{
	string translation;
	getline(cin, translation);
	transform(inputWord.begin(), inputWord.end(), inputWord.begin(), tolower);
	if (!translation.empty())
	{
		newWordsMap.emplace(inputWord, translation);
		cout << "Слово" << " " << inputWord << " сохранено как" << " \"" << translation << "\"" << endl;
		newWord = true;
	}
	else
	{
		cout << "Слово" << " " << inputWord << " проигнорировано" << endl;
	}
}

void ProcessInputWords(const multimap<string, string>& dict, multimap<string, string>& newWordsMap, bool& newWord)
{
	string inputWord;
	while (getline(cin, inputWord) && inputWord != EXIT_VALUE)
	{
		transform(inputWord.begin(), inputWord.end(), inputWord.begin(), tolower);
		if (!SearchInDictionary(dict, inputWord))
		{
			ProccesNewWord(newWordsMap, inputWord, newWord);
		}
	}
}

bool IsNeedToSave()
{
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом." << endl;
	string decision;
	getline(cin, decision);
	return decision == "Y" || decision == "y";
}

void SaveNewDictionary(const multimap<string, string>& newWordsMap, const string& fileName)
{
	if (IsNeedToSave())
	{
		ofstream outputFile;
		outputFile.open(fileName, ios::app);
		if (!outputFile.is_open())
		{
			cout << "Failed to open " << fileName << " for writing" << endl;
		}
		for (const auto& pair : newWordsMap)
		{
			outputFile << pair.first << " " << pair.second << endl;
		}
		if (!outputFile.flush())
		{
			cout << "Failed for writing data in output stream" << endl;
		}
		cout << "Изменения успешно сохранены. Проверьте файл"
			 << " " << fileName << " До свидания";
	}
	else
	{
		cout << "Изменения не сохранены."
			 << " До свидания";
	}
}
