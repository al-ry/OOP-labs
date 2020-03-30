#include "stdafx.h"
#include "../dictionary/dictionary.h"

using namespace std;



BOOST_AUTO_TEST_SUITE(SearchInDictionary_function)


	BOOST_AUTO_TEST_SUITE(when_find_existent_word_in_dictionary)
		BOOST_AUTO_TEST_CASE(should_find_word_in_dictionary)
		{
			Dictionary dictionary;
			dictionary.emplace("mother", "мама");
			dictionary.emplace("street", "улица");
			string inputWord = "street"; 
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputWord), true);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_find_nonexistent_word_in_dictionary)
		BOOST_AUTO_TEST_CASE(cannot_find_word_in_dictionary)
		{
			Dictionary dictionary;
			dictionary.emplace("mother", "мама");
			dictionary.emplace("house", "дом");
			string inputWord = "libary";
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputWord), false);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(when_find_expression_in_dictionary)
		BOOST_AUTO_TEST_CASE(should_find_expression_in_dictionary)
		{
			Dictionary dictionary;
			dictionary.emplace("object oriented programming", "объектно орентирование программирование");
			string inputExpression = "object oriented programming";
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputExpression), true);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(when_find_two_similar_words_in_dictionary)
		BOOST_AUTO_TEST_CASE(should_find_words_in_dictionary)
		{
			Dictionary dictionary;
			dictionary.emplace("cat", "кот");
			dictionary.emplace("cat", "кошка");
			string inputWord = "cat";
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputWord), true);
		}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
