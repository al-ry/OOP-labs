#include "stdafx.h"
#include "../dictionary/dictionary.h"

using namespace std;



BOOST_AUTO_TEST_SUITE(SearchInDictionary_function)


	BOOST_AUTO_TEST_SUITE(when_find_existent_word_in_dictionary)
		BOOST_AUTO_TEST_CASE(should_find_word_in_dictionary)
		{
			Vocabluary dictionary;
			dictionary.dictionaryMap.emplace("mother", "мама");
			dictionary.dictionaryMap.emplace("street", "улица");
			string inputWord = "street"; 
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary.dictionaryMap, inputWord), true);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_find_nonexistent_word_in_dictionary)
		BOOST_AUTO_TEST_CASE(cannot_find_word_in_dictionary)
		{
			Vocabluary dictionary;
			dictionary.dictionaryMap.emplace("mother", "мама");
			dictionary.dictionaryMap.emplace("house", "дом");
			string inputWord = "libary";
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary.dictionaryMap, inputWord), false);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(when_find_expression_in_dictionary)
		BOOST_AUTO_TEST_CASE(should_find_expression_in_dictionary)
		{
			Vocabluary dictionary;
			dictionary.dictionaryMap.emplace("object oriented programming", "объектно орентирование программирование");
			string inputExpression = "object oriented programming";
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary.dictionaryMap, inputExpression), true);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(when_find_two_similar_words_in_dictionary)
		BOOST_AUTO_TEST_CASE(should_find_words_in_dictionary)
		{
			Vocabluary dictionary;
			dictionary.dictionaryMap.emplace("cat", "кот");
			dictionary.dictionaryMap.emplace("cat", "кошка");
			string inputWord = "cat";
			BOOST_CHECK_EQUAL(SearchInDictionary(dictionary.dictionaryMap, inputWord), true);
		}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
