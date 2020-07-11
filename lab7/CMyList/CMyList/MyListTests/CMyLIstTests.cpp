#include "stdafx.h"
#include "../CMyList/CMyList.h"



struct EmptyIntList
{
	CMyList<int> list;
};

BOOST_FIXTURE_TEST_SUITE(Int_list, EmptyIntList)
	BOOST_AUTO_TEST_SUITE(when_created)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(is_empty_via_method)
		{
			BOOST_CHECK(list.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(can_get_begin_and_end_iterators_but_cant_get_data_from_themselves)
		{
			auto begin = list.begin();
			auto end = list.end();
			BOOST_CHECK_THROW(*begin, std::runtime_error);
			BOOST_CHECK_THROW(*end, std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(can_get_cbegin_and_cend_iterators_but_cant_get_data_from_themselves)
		{
			auto begin = list.cbegin();
			auto end = list.cend();
			BOOST_CHECK_THROW(*begin, std::runtime_error);
			BOOST_CHECK_THROW(*end, std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(can_get_rbegin_and_rend_iterators_but_cant_get_data_from_themselves)
		{
			auto rbegin = list.rbegin();
			auto rend = list.rend();
			BOOST_CHECK_THROW(*rbegin, std::out_of_range);
			BOOST_CHECK_THROW(*rend, std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(cannot_be_erased_from_empty_list)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(list.Erase(it), std::runtime_error);
			it = list.begin();
			BOOST_CHECK_THROW(list.Erase(it), std::runtime_error);		
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_appending_element)
		BOOST_AUTO_TEST_CASE(should_increase_size)
		{
			list.AppendBack(1);
			BOOST_CHECK_EQUAL(list.GetSize(), 1u);
			list.AppendBack(2);
			BOOST_CHECK_EQUAL(list.GetSize(), 2u);
			list.AppendFront(0);
			BOOST_CHECK_EQUAL(list.GetSize(), 3u);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_there_are_elements : EmptyIntList
	{
		when_there_are_elements()
		{
			list.AppendBack(1);
			list.AppendBack(2);
			list.AppendBack(3);
			list.AppendBack(4);
			list.AppendBack(5);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_there_are_elements_, when_there_are_elements)
		BOOST_AUTO_TEST_CASE(is_not_empty)
		{
			BOOST_CHECK(!list.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(has_appropriate_size)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 5u);
		}
		BOOST_AUTO_TEST_CASE(can_recieve_back_element)
		{
			BOOST_CHECK_EQUAL(list.GetBackElement(), 5u);
		}
		BOOST_AUTO_TEST_CASE(can_recieve_front_element)
		{
			BOOST_CHECK_EQUAL(list.GetFrontElement(), 1u);
		}
		BOOST_AUTO_TEST_CASE(can_get_begin_and_cbegin_iterator)
		{
			auto it = list.begin();
			auto cIt = list.cbegin();
			BOOST_CHECK_EQUAL(*it, 1);
			BOOST_CHECK_EQUAL(*cIt, 1);
		}
		BOOST_AUTO_TEST_CASE(cannit_get_data_from_end_and_cend_iterators)
		{
			auto it = list.end();
			auto cIt = list.cend();
			BOOST_CHECK_THROW(*it, std::runtime_error);
			BOOST_CHECK_THROW(*cIt, std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(can_increment_begin_iterator)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*++it, 2);
			BOOST_CHECK_EQUAL(*++(++it), 4);
			BOOST_CHECK_EQUAL(*it++, 5);
		}
		BOOST_AUTO_TEST_CASE(cannot_increment_end_iterator_to_out_of_range)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(++it, std::out_of_range);
			BOOST_CHECK_THROW(it++, std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_decrement_end_iterator)
		{
			auto it = list.end();
			BOOST_CHECK_EQUAL(*--it, 5);
			BOOST_CHECK_EQUAL(*--(--it), 3);
			BOOST_CHECK_EQUAL(*it--, 2);
		}
		BOOST_AUTO_TEST_CASE(cannot_decrement_begin_iterator_to_out_of_range)
		{
			auto it = list.begin();
			BOOST_CHECK_THROW(--it, std::out_of_range);
			BOOST_CHECK_THROW(it--, std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_increase_iteratro_and_then_decrease_it_back)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*++it, 2);
			BOOST_CHECK_EQUAL(*--it, 1);
		}
		BOOST_AUTO_TEST_CASE(can_be_checked_to_equality)
		{
			auto it1 = list.begin();
			auto it2 = list.begin();

			BOOST_CHECK(it1 == it2);
			BOOST_CHECK(!(it1 != it2));
			++it1;
			BOOST_CHECK(it1 != it2);
			BOOST_CHECK(!(it1 == it2));
		}
		BOOST_AUTO_TEST_CASE(can_insert_into_specified_position)
		{
			auto it = list.begin();
			++it;
			list.Insert(20, it);
			BOOST_CHECK(*++list.begin() == 20);
			auto cIt = list.cbegin();
			list.Insert(20, cIt);
			list.Insert(100, cIt);
			BOOST_CHECK(*list.begin() == 20);
			BOOST_CHECK(*++list.begin() == 100);
		}
		BOOST_AUTO_TEST_CASE(can_get_elements_via_for_loop)
		{
			std::ostringstream res;
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				res << *it;
			}
			BOOST_CHECK(res.str() == "12345");
			res.str("");
			for (auto it = list.cbegin(); it != list.cend(); ++it)
			{
				res << *it;
			}
			BOOST_CHECK(res.str() == "12345");
		}
		BOOST_AUTO_TEST_CASE(can_get_elements_through_range_based_for)
		{
			std::ostringstream res;
			for (auto it : list)
			{
				res << it;
			}
			BOOST_CHECK(res.str() == "12345");
			res.str("");
			for (const auto it : list)
			{
				res << it;
			}
			BOOST_CHECK(res.str() == "12345");
		}
		BOOST_AUTO_TEST_CASE(can_get_rbegin_iterator)
		{
			auto it = list.rbegin();
			BOOST_CHECK(*it == 5);
		}
		BOOST_AUTO_TEST_CASE(can_get_rend_iterator)
		{
			auto it = list.rend();
			BOOST_CHECK_THROW(*it, std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_get_backward_elements_via_for_loop)
		{
			std::ostringstream res;
			for (auto it = list.rbegin(); it != list.rend(); ++it)
			{
				res << *it;
			}
			BOOST_CHECK(res.str() == "54321");
			res.str("");
			for (auto it = list.crbegin(); it != list.crend(); ++it)
			{
				res << *it;
			}
			BOOST_CHECK(res.str() == "54321");
		}
		BOOST_AUTO_TEST_CASE(cant_be_erased_from_end_position)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(list.Erase(it), std::runtime_error);

		}
		BOOST_AUTO_TEST_CASE(can_be_erased_from_begin_and_cbegin)
		{
			auto it = list.begin();
			list.Erase(it);
			it = list.begin();
			BOOST_CHECK(*it == 2);
			auto cIt = list.cbegin();
			list.Erase(cIt);
			it = list.begin();
			BOOST_CHECK_EQUAL(*it, 3);
		}
		BOOST_AUTO_TEST_CASE(can_be_erased_from_any_pos)
		{
			auto it = list.end();
			list.Erase(--(--it));
			auto itRes = list.end();
			BOOST_CHECK_EQUAL(*----itRes, 3);
		}
		BOOST_AUTO_TEST_CASE(can_make_copy_of_list)
		{
			CMyList<int> copy(list);
			BOOST_CHECK_NE(std::addressof(copy), std::addressof(list));
			BOOST_CHECK(*copy.begin() == 1);
			CMyList<int> copy2 = list;
			BOOST_CHECK_NE(std::addressof(copy2), std::addressof(list));
			BOOST_CHECK(*copy2.begin() == 1);
		}
		BOOST_AUTO_TEST_CASE(can_be_moved)
		{
			CMyList<int> newList(std::move(list));
			BOOST_CHECK_EQUAL(*newList.begin(), 1);
			CMyList<int> newList2 = std::move(newList);
			BOOST_CHECK_EQUAL(*newList2.begin(), 1);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

struct EmptyStringList
{
	CMyList<std::string> list;
	EmptyStringList()
	{
		list.AppendBack("1");
		list.AppendBack("2");
		list.AppendBack("3");
		list.AppendBack("4");
		list.AppendBack("5");
	}
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
	BOOST_AUTO_TEST_SUITE(when_created_with_elements)
		BOOST_AUTO_TEST_CASE(has_size)
		{
			BOOST_CHECK(list.GetSize() == 5u);
		}
		BOOST_AUTO_TEST_CASE(can_get_elements_via_itarators)
		{
			BOOST_CHECK(*list.begin() == "1");
			BOOST_CHECK(*++list.begin() == "2");
			BOOST_CHECK(*list.rbegin() == "5");
			BOOST_CHECK(*--list.rend() == "1");
		}
		BOOST_AUTO_TEST_CASE(can_append_elements)
		{
			list.AppendBack("new last item");
			BOOST_CHECK(*--list.end() == "new last item");
			list.AppendFront("new first item");
			BOOST_CHECK(*list.begin() == "new first item");
			list.Insert("new middle item", ++++++list.begin());
			BOOST_CHECK(*++++++list.begin() == "new middle item");
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()