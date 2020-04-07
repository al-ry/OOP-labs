
typedef std::multimap<std::string, std::string> Dictionary;

struct Vocabluary
{
	Dictionary dictionaryMap;
	Dictionary newWordsMap;
};

bool ReadDictionary(const std::string& dictionatyFileName, Dictionary& sourceDict);
void ProcessInputWords(Vocabluary& dict);
bool UpdateDictionary(std::string &fileName, const Dictionary& newWordsDict);
bool SearchInDictionary(const Dictionary& dict, const std::string& inputWord);
Dictionary SaveNewWord(Vocabluary& dict, const std::string& inputWord);