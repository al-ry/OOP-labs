
typedef std::multimap<std::string, std::string> Dictionary;

typedef bool (*IsSourceSDictionary)(const std::optional<std::string> &arg);
bool SearchInDictionary(const Dictionary& dict, const std::string& inputWord);
bool IsArgument(const std::optional<std::string> &arg);
bool ReadDictionary(const std::string& dictionatyFileName, Dictionary& dictMap);
void ProcessInputWords(Dictionary& dict, Dictionary& newWordsMap);
bool SaveNewWord(Dictionary& dict, Dictionary& newWordsMap, const std::string& inputWord);
bool SaveNewDictionary(IsSourceSDictionary fn, const std::optional<std::string>& arg, const Dictionary& newWordsMap);
bool IsNeedsSaving();