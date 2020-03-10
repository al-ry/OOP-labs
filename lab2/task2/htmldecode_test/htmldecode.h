#pragma once
#include "stdafx.h"

const map<string, string> htmlEntities = {
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

string HtmlDecode(string& htmlString);
