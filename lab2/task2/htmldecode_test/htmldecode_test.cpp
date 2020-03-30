#include "stdafx.h"
#include "..\htmldecode\htmldecode.h"

using namespace std;

void VerifyHtmlDecode(std::string& sourceStr, const std::string& expectedTrimmedString)
{
	BOOST_CHECK_EQUAL(HtmlDecode(sourceStr), expectedTrimmedString);
}


BOOST_AUTO_TEST_SUITE(HtmlDecode_function)


	BOOST_AUTO_TEST_SUITE(when_processing_a_empty_string)
		BOOST_AUTO_TEST_CASE(must_convert_empty_string_to_empty_string)
		{
			string str = "";
			VerifyHtmlDecode(str, "");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_a_string_without_html_entities)
		BOOST_AUTO_TEST_CASE(must_copy_string_without_changes)
		{
			string str = "This text hasn't html entities and will copy without changes";
			VerifyHtmlDecode(str, str);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_all_available_html_entities)
		BOOST_AUTO_TEST_CASE(must_change_all_avaiable_html_entities_to_symbol_representation)
		{
			string str = "&quot; &lt; &gt; &apos; &amp;";
			VerifyHtmlDecode(str, "\" < > \' &");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_quot_html_entity)
		BOOST_AUTO_TEST_CASE(must_replace_quot_entity_to_symbol_representation)
		{
			string str = "&quot;some&quot;text&quot; in quotes&quot;";
			VerifyHtmlDecode(str, "\"some\"text\" in quotes\"");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_lt_html_entity)
		BOOST_AUTO_TEST_CASE(must_replace_lt_entity_to_symbol_representation)
		{
			string str = "5 &lt; 6";
			VerifyHtmlDecode(str, "5 < 6");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_gt_html_entity)
		BOOST_AUTO_TEST_CASE(must_replace_gt_entity_to_symbol_representation)
		{
			string str = "6 &gt; 5";
			VerifyHtmlDecode(str, "6 > 5");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_amp_and_apos_html_entities)
		BOOST_AUTO_TEST_CASE(must_replace_amp_and_apos_entity_to_symbol_representation)
		{
			string str = "M&amp;M&apos;s";
			VerifyHtmlDecode(str, "M&M's");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_apos_without_ampSymbol_after_amp_entity)
		BOOST_AUTO_TEST_CASE(must_replace_amp_entity_without_converting_apos_entity)
		{
			string str = "&amp;apos;";
			VerifyHtmlDecode(str, "&apos;");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()