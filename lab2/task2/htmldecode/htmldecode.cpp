
#include "stdafx.h"
#include "htmldecode.h"

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
string HtmlDecode(string & htmlString)
{
	for (auto i = htmlEntities.begin(); i != htmlEntities.end(); ++i)
	{
		htmlString = ReplaceHtmlEntity(htmlString, i->first, i->second);
	}
	return htmlString;
}
