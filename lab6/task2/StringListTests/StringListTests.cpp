#include "stdafx.h"
#include "../SringList/StringList.h"


struct EmptyStringList
{
	CStringList list;
};


BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
	BOOST_AUTO_TEST_SUITE(when_created)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(can_recieve_end_iterator)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(*it, std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(after_appending_a_string)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_2_via_AppendBack)
		{
			auto oldSize = list.GetSize();
			list.AppendBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.AppendBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(increases_its_size_by_2_via_AppendFront)
		{
			auto oldSize = list.GetSize();
			list.AppendFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.AppendFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
			list.AppendFront("good evening");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 3);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.AppendBack("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.AppendBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_const_method)
		{
			list.AppendBack("hello");
			std::string constEl = list.GetBackElement();
			BOOST_CHECK_EQUAL(constEl, "hello");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.AppendBack("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.AppendBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_const_method)
		{
			list.AppendBack("hello");
			const std::string constEl = list.GetFrontElement();
			BOOST_CHECK_EQUAL(constEl, "hello");
		}
		BOOST_AUTO_TEST_CASE(cant_get_back_element_from_empty_list)
		{
			BOOST_REQUIRE_THROW(list.GetBackElement(), std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(cant_get_front_element_from_empty_list)
		{

			BOOST_REQUIRE_THROW(list.GetFrontElement(), std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(cannot_get_const_end_and_front_element)
		{
			const CStringList list2;
			BOOST_CHECK_THROW(list2.GetBackElement(), std::runtime_error);
			BOOST_CHECK_THROW(list2.GetFrontElement(), std::runtime_error);
		}


		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.AppendBack("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
		struct when_there_are_elements : EmptyStringList
		{
			when_there_are_elements()
			{
				list.AppendBack("1");
				list.AppendBack("2");
				list.AppendBack("3");
				list.AppendBack("4");
				list.AppendBack("5");
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_there_are_elements_, when_there_are_elements)
			BOOST_AUTO_TEST_CASE(can_be_cleared)
			{
				list.Clear();
				BOOST_CHECK(list.GetSize() == 0);
			}
			BOOST_AUTO_TEST_CASE(makes_it_accessible_via_const_iterator_to_last_element)
			{
				const auto begin = list.cbegin();
				BOOST_CHECK_EQUAL(*begin, "1");;
			}
			BOOST_AUTO_TEST_CASE(can_get_const_end_iterator)
			{
				const auto end = list.cend();	
				BOOST_CHECK_THROW(*end, std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(can_increase_iterator_to_1)
			{
				auto it = list.begin();
				++it;BOOST_CHECK_EQUAL(*it, "2");
				++it;BOOST_CHECK_EQUAL(*it, "3");	
			}
			BOOST_AUTO_TEST_CASE(cannot_get_iterator_when_its_increased_to_out_of_range)
			{
				auto end = list.end();
				BOOST_CHECK_THROW(++end, std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(can_deacrease_end_iterator)
			{
				auto end = list.end();
				--end;
				BOOST_CHECK(*end == "5");
			}
			BOOST_AUTO_TEST_CASE(cant_deacrease_rbegin_iterator)
			{
				auto end = list.rbegin();
				BOOST_CHECK_THROW(--end, std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(cant_decrease_begin)
			{
				auto begin = list.begin();
				BOOST_CHECK_THROW(--begin, std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(can_be_compared)
			{
				auto it = list.begin();
				BOOST_CHECK(it == list.begin());
				++it;
				BOOST_CHECK(it != list.begin());
			}
			BOOST_AUTO_TEST_CASE(can_be_inserted_in_the_begining)
			{
				auto it = list.begin();
				list.Insert("new item", it);
				BOOST_CHECK_EQUAL(*list.begin(), "new item");
				BOOST_CHECK(it == ++list.begin());
				BOOST_CHECK(list.GetSize() == 6u);
			}
			BOOST_AUTO_TEST_CASE(can_be_inserted_at_the_end_via_rbegin)
			{
				auto it = list.rbegin();
				list.Insert("new item", it);
				BOOST_CHECK_EQUAL(list.GetBackElement(), "new item");
				BOOST_CHECK(list.GetSize() == 6u);
			}
			BOOST_AUTO_TEST_CASE(can_be_inserted_to_given_postition)
			{
				auto it = ++(++list.begin());
				BOOST_CHECK(*it == "3");
				list.Insert("new item", it);
				BOOST_CHECK(*(--it) == "new item");
				BOOST_CHECK(list.GetSize() == 6u);
			}
			BOOST_AUTO_TEST_CASE(can_be_inserted_to_empty_list)
			{
				CStringList list2;
				auto it = list2.begin();
				list2.Insert("new", it);
				BOOST_CHECK("new" == list2.GetFrontElement());
			}
			BOOST_AUTO_TEST_CASE(cannot_be_erased_from_empty_list)
			{
				CStringList list2;
				auto it = list2.begin();
				BOOST_REQUIRE_THROW(list2.Erase(it), std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(cannot_be_erased_from_rbegin_and_end)
			{
				auto it = list.end();
				BOOST_REQUIRE_THROW(list.Erase(it), std::out_of_range);
				it = list.rend();
				BOOST_REQUIRE_THROW(list.Erase(it), std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(can_be_erased_from_start_position)
			{
				auto it = list.begin();
				list.Erase(it);
				it = list.begin();
				BOOST_REQUIRE(*it == "2");
			}
			BOOST_AUTO_TEST_CASE(can_be_erased_from_end_position_via_rbegin)
			{
				auto it = list.rbegin();
				list.Erase(it);
				BOOST_REQUIRE(list.GetBackElement() == "4");
			}
			BOOST_AUTO_TEST_CASE(can_be_erased_from_any_pos)
			{
				auto it = list.begin();
				++it;
				list.Erase(it);
				it = ++list.begin();
				BOOST_REQUIRE(*it == "3");
			}
			BOOST_AUTO_TEST_CASE(can_get_elements_via_for_loop)
			{
				std::ostringstream expectedRes;
				for (auto it = list.begin(); it != list.end(); ++it)
				{
					expectedRes << *it;
				}
				BOOST_CHECK(expectedRes.str() == "12345");
			}
			BOOST_AUTO_TEST_CASE(can_get_elements_through_range_based_for)
			{
				std::ostringstream expectedRes;
				for (auto it : list)
				{
					expectedRes << it;
				}
				BOOST_CHECK(expectedRes.str() == "12345");
			}
			BOOST_AUTO_TEST_CASE(should_clear_list_with_1_size)
			{
				CStringList list2;
				list2.AppendBack("first");
				auto it = list2.begin();
				list2.Erase(it);
				BOOST_CHECK(list2.IsEmpty());
				BOOST_CHECK_THROW(list2.GetBackElement(), std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(can_get_last_elem_via_rbegin)///
			{
				auto it = list.rbegin();
				BOOST_CHECK(*it == "5");
				it = list.crbegin();
				BOOST_CHECK(*it == "5");
			}
			BOOST_AUTO_TEST_CASE(can_decrease_rend)
			{
				auto it = list.rend();
				BOOST_CHECK(*--it == "1");
			}
			BOOST_AUTO_TEST_CASE(cannot_increase_rend)
			{
				auto it = list.rend();
				BOOST_CHECK_THROW(++it, std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(cannot_get_null_data)
			{
				auto it = list.rend();
				BOOST_CHECK_THROW(*it, std::out_of_range);
				it = list.crend();
				BOOST_CHECK_THROW(*it, std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(cannot_be_inserted_to_end_and_rend)
			{	
				list.Insert("new last", list.end());
				list.Insert("new first", list.rend());
				BOOST_CHECK(list.GetFrontElement() == "new first");
				BOOST_CHECK(list.GetBackElement() == "new last");
			}
			BOOST_AUTO_TEST_CASE(can_be_erased_from_end_and_rend_position)
			{
				BOOST_CHECK_THROW(list.Erase(list.end()), std::out_of_range);
				BOOST_CHECK_THROW(list.Erase(list.rend()), std::out_of_range);
			}
			BOOST_AUTO_TEST_CASE(reverse_iterator_can_be_increased)
			{
				auto it = list.rbegin();
				++it;
				BOOST_CHECK_EQUAL(*it, "4");
			}
			BOOST_AUTO_TEST_CASE(reverse_iterator_can_be_decreased)
			{
				auto it = ++(++list.rbegin());
				--it;
				BOOST_CHECK(*it == "4");
			}
			BOOST_AUTO_TEST_CASE(can_be_got_via_for_loop_with_rbegin)
			{
				std::ostringstream expectedRes;
				for (auto it = list.rbegin(); it != list.rend(); ++it)
				{
					expectedRes << *it;
				}
				BOOST_CHECK(expectedRes.str() == "54321");
			}
			BOOST_AUTO_TEST_CASE(can_make_copy_of_list)
			{
				CStringList copyOfList(list);
				auto it = copyOfList.begin();
				BOOST_CHECK(addressof(*it) != addressof(list.GetBackElement()));
				BOOST_CHECK(*it == "1");
				BOOST_CHECK(list.GetBackElement() == "5");
			}
			BOOST_AUTO_TEST_CASE(can_make_copy_of_list_via_overoloaded_operator)
			{
				CStringList copyOfList = list;
				BOOST_CHECK(copyOfList.GetSize() == 5u);
				BOOST_CHECK(copyOfList.GetFrontElement() == "1");
				BOOST_CHECK(copyOfList.GetBackElement() == "5");
			}
			BOOST_AUTO_TEST_CASE(can_be_moved)
			{

				CStringList newList = std::move(list);
				BOOST_CHECK(newList.GetFrontElement() == "1");
				BOOST_CHECK(newList.GetBackElement() == "5");
				BOOST_CHECK(newList.GetSize() == 5u);
				CStringList newList2(std::move(newList));
				BOOST_CHECK(newList2.GetFrontElement() == "1");
				BOOST_CHECK(newList2.GetBackElement() == "5");
				BOOST_CHECK(newList2.GetSize() == 5u);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()