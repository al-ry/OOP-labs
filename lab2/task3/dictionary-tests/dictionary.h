#pragma once


typedef std::multimap<std::string, std::string> Dictionary;

bool SearchInDictionary(const Dictionary& dict, std::string& inputWord);
typedef bool (*IsSourceSDictionary)(const std::optional<std::string>& arg);
bool IsArgument(const std::optional<std::string>& arg);
bool ReadDictionary(const std::string& dictionatyFileName, Dictionary& dictMap);
void ProcessInputWords(const Dictionary& dict, Dictionary& newWordsMap);
void ProccesNewWord(Dictionary& newWordsMap, std::string& inputWord);
bool SaveNewDictionary(IsSourceSDictionary fn, const std::optional<std::string>& arg, const Dictionary& newWordsMap);
bool IsNeedToSave();