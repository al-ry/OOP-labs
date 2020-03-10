#pragma once
#include "stdafx.h"

const map<string, string> htmlEntities = {
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

string HtmlDecode(const string& htmlString);
string ReplaceHtmlEntity(string& htmlStr, const string& replacableEssence, const string& appropiateSymbol);
