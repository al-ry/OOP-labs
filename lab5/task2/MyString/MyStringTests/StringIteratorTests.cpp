#include "stdafx.h"
#include "../MyString/CMyString.h"

struct someString
{
	CMyString str = "iterator test";
};

BOOST_FIXTURE_TEST_SUITE(Test_iterators, someString)
	BOOST_AUTO_TEST_CASE(can_get_begin_iterator)
	{
		auto it = str.begin();
		BOOST_CHECK(*it == 'i');
	}
	BOOST_AUTO_TEST_CASE(can_increase_begin_iterator)
	{
		auto it = str.begin();
		BOOST_CHECK(*++it == 't');
	}
	BOOST_AUTO_TEST_CASE(can_get_end_iterator)
	{
		auto it = str.end();
		BOOST_CHECK(*it == '\0');
	}
	BOOST_AUTO_TEST_CASE(can_decrease_end_iterator)
	{
		auto it = str.end();
		BOOST_CHECK(*--it == 't');
	}
	BOOST_AUTO_TEST_CASE(can_decrease_to_given_position)
	{
		auto it = str.end();
		it -= 3;
		BOOST_CHECK(*it == 'e');
	}
	BOOST_AUTO_TEST_CASE(can_increase_to_given_position)
	{
		auto it = str.begin();
		it += 5;
		BOOST_CHECK(*it == 't');
	}
	BOOST_AUTO_TEST_CASE(can_calculate_difference_between_iterators)
	{
		auto it1 = str.begin();
		auto it2 = str.end();
		auto res = it2 - it1;
		BOOST_CHECK(res == str.GetLength());
		++it1;
		res = it2 - it1;
		BOOST_CHECK(res == str.GetLength() - 1);
	}
	BOOST_AUTO_TEST_CASE(can_check_equal)
	{
		auto it1 = str.begin();
		auto it2 = str.begin();
		auto it3 = str.end();
		BOOST_CHECK(it2 == it1);
		BOOST_CHECK(!(it2 == it3));

		BOOST_CHECK(it2 != it3);
		BOOST_CHECK(!(it2 != it1));
	}
	BOOST_AUTO_TEST_CASE(can_get_const_iterator)
	{
		auto it = str.cbegin();
		auto itEnd = str.cend();
		BOOST_CHECK(*it == 'i');
		BOOST_CHECK(*--itEnd == 't');
	}
	BOOST_AUTO_TEST_CASE(can_get_const_iterator_from_const_string)
	{
		const CMyString constStr = "some const str";
		auto it = constStr.begin();
		auto itEnd = constStr.end();
		BOOST_CHECK(*it == 's');
		BOOST_CHECK(*--itEnd == 'r');
	}
BOOST_AUTO_TEST_SUITE_END()