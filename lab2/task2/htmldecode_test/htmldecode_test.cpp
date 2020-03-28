#include "stdafx.h"
#include "..\htmldecode\htmldecode.h"

using namespace std;

void VerifyHtmlDecode(std::string& sourceStr, const std::string& expectedTrimmedString)
{
	BOOST_CHECK_EQUAL(HtmlDecode(sourceStr), expectedTrimmedString);
}


BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

	BOOST_AUTO_TEST_CASE(must_convert_empty_string_to_empty_string)
	{
		string str = "";
		VerifyHtmlDecode(str, "");
	}
	BOOST_AUTO_TEST_CASE(must_copy_string_without_changes)
	{
		string str = "This text hasn't html entities and will copy without changes";
		VerifyHtmlDecode(str, str);
	}
	BOOST_AUTO_TEST_CASE(must_change_all_avaiable_html_entities)
	{
		string str = "&quot; &lt; &gt; &apos; &amp;";
		VerifyHtmlDecode(str, "\" < > \' &");
	}
	BOOST_AUTO_TEST_CASE(must_replace_quot_entity)
	{
		string str = "&quot;some&quot;text&quot; in quotes&quot;";
		VerifyHtmlDecode(str, "\"some\"text\" in quotes\"");
	}
	BOOST_AUTO_TEST_CASE(must_replace_lt_entity)
	{
		string str = "5 &lt; 6";
		VerifyHtmlDecode(str, "5 < 6");
	}
	BOOST_AUTO_TEST_CASE(must_replace_gt_entity)
	{
		string str = "6 &gt; 5";
		VerifyHtmlDecode(str, "6 > 5");
	}
	BOOST_AUTO_TEST_CASE(must_replace_amp_and_apos_entity)
	{
		string str = "M&amp;M&apos;s";
		VerifyHtmlDecode(str, "M&M's");
	}

BOOST_AUTO_TEST_SUITE_END()