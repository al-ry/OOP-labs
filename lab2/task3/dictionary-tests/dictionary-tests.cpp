#include "stdafx.h"
#include "../dictionary/dictionary.h"

using namespace std;



BOOST_AUTO_TEST_SUITE(SearchInDictionary_function)

	BOOST_AUTO_TEST_CASE(find_existent_word_in_dictionary)
	{
		Dictionary dictionary;
		dictionary.emplace("mother", "мама");
		dictionary.emplace("street", "улица");
		string inputWord = "street"; 
		BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputWord), true);
	}

	BOOST_AUTO_TEST_CASE(find_nonexistent_word_in_dictionary)
	{
		Dictionary dictionary;
		dictionary.emplace("mother", "мама");
		dictionary.emplace("house", "дом");
		string inputWord = "libary";
		BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputWord), false);
	}


	BOOST_AUTO_TEST_CASE(find_expression_in_dictionary)
	{
		Dictionary dictionary;
		dictionary.emplace("object oriented programming", "объектно орентирование программирование");
		string inputExpression = "object oriented programming";
		BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputExpression), true);
	}

	BOOST_AUTO_TEST_CASE(find_two_similar_words_in_dictionary)
	{
		Dictionary dictionary;
		dictionary.emplace("cat", "кот");
		dictionary.emplace("cat", "кошка");
		string inputWord = "cat";
		BOOST_CHECK_EQUAL(SearchInDictionary(dictionary, inputWord), true);
	}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SaveNewWord_function)
	BOOST_AUTO_TEST_CASE(ignores_a_new_word_if_the_user_has_not_entered_a_translation)
	{
		Dictionary dictionary;
		Dictionary newWords;
		dictionary.emplace("мама", "mother");
		string word = "слово";
		BOOST_CHECK(SaveNewWord(dictionary, newWords, word), false);
	}
BOOST_AUTO_TEST_SUITE_END()