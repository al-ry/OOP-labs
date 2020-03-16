
#include "stdafx.h"
#include "htmldecode.h"

using namespace std;

const map<string, string> htmlEntities = {
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

string ReplaceHtmlEntity(string& htmlStr, const string& replacableEssence, const string& appropiateSymbol)
{
	size_t indexPos = 0;
	string resultStr;
	while (indexPos < htmlStr.length())
	{
		size_t foundPos = htmlStr.find(replacableEssence, indexPos);
		if (foundPos != string::npos)
		{
			resultStr.append(htmlStr, indexPos, foundPos - indexPos);
			resultStr.append(appropiateSymbol);
			indexPos = foundPos + replacableEssence.length();
		}
		else
		{
			resultStr.append(htmlStr, indexPos, htmlStr.length() - indexPos);
			break;
		}
	}
	return resultStr;
}

string HtmlDecode(const string & htmlString)
{
	string tmpString = htmlString;
	for (auto i = htmlEntities.begin(); i != htmlEntities.end(); ++i)
	{
		tmpString = ReplaceHtmlEntity(tmpString, i->first, i->second);
	}
	string result;
	return result = tmpString;
}


