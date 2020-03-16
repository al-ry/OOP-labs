#pragma once


bool ReadDictionary(const std::string& dictionatyFileName, std::multimap<std::string, std::string>& dictMap);
void ProcessInputWords(const std::multimap<std::string, std::string>& dict, std::multimap<std::string, std::string>& newWordsMap, bool& newWord);
void ProccesNewWord(std::multimap<std::string, std::string>& newWordsMap, std::string& inputWord, bool& newWord);
bool SearchInDictionary(std::multimap<std::string, std::string>& dict, const std::string& inputWord);
void SaveNewDictionary(const std::multimap<std::string, std::string>& newWordsMap, const std::string& fileName);
bool IsNeedToSave();