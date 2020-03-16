#include "stdafx.h"
#include "../dictionary-tests/dictionary.h"


BOOST_AUTO_TEST_SUITE(SearchInDictionary_function)


	BOOST_AUTO_TEST_CASE(find_word_in_dictionary)
	{
		multimap<string, string> dictionary;
		dictionary.emplace("car", "машина");
		BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, "car"), true);
	}


BOOST_AUTO_TEST_SUITE_END()