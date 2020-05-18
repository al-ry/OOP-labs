#include "stdafx.h"
#include "../MyString/CMyString.h"


void VerifyString(const CMyString& str, const char* expectedData, size_t expectedLenght)
{
	BOOST_CHECK_EQUAL(str.GetLength(), expectedLenght);
	BOOST_CHECK_EQUAL(str.GetStringData(), expectedData);
	BOOST_CHECK_EQUAL(strcmp(str.GetStringData(), expectedData), 0);
}

BOOST_AUTO_TEST_SUITE(Test_Constructors)
	BOOST_AUTO_TEST_CASE(can_create_string)
	{
		CMyString str("str", 3);
		VerifyString(str, "str", 3);
	}
	BOOST_AUTO_TEST_CASE(can_create_string_by_default)
	{
		CMyString str;
		VerifyString(str, "", 0);
	}
	BOOST_AUTO_TEST_CASE(should_cut_string_after_teminated_zero)
	{
		CMyString myStr("str\0 ff");
		VerifyString(myStr, "str", 3); 
	}
	BOOST_AUTO_TEST_CASE(can_create_string_with_temrinated_zero_in_the_middle_of_str)
	{
		CMyString myStr("str\0ignored_data", 5);
		VerifyString(myStr, "str\0i", 5);
	}
	BOOST_AUTO_TEST_CASE(can_create_string_from_stl_string)
	{
		std::string str = "hello";
		CMyString myStr(str);
		VerifyString(myStr, "hello", 5);
	}
	BOOST_AUTO_TEST_CASE(can_copy_data_in_new_str)
	{
		CMyString myStr("that string will be copied to other");
		CMyString copyOf(myStr);
		BOOST_CHECK(myStr.GetStringData() != copyOf.GetStringData());
		VerifyString(copyOf, "that string will be copied to other", myStr.GetLength());
	}
BOOST_AUTO_TEST_SUITE_END()

struct someDefaultString
{
	CMyString emptyStr;
};
BOOST_FIXTURE_TEST_SUITE(test_default_str, someDefaultString)
	BOOST_AUTO_TEST_CASE(has_zero_lenght)
	{
		VerifyString(emptyStr, "", 0);
	}
	BOOST_AUTO_TEST_CASE(has_terminated_zero)
	{
		BOOST_CHECK_EQUAL(emptyStr.GetStringData()[emptyStr.GetLength()], '\0');
	}
BOOST_AUTO_TEST_SUITE_END()

struct someStrings : someDefaultString
{
	CMyString str;
	someStrings()
		: str("string")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_string_with_some_data, someStrings)
	BOOST_AUTO_TEST_CASE(has_terminated_zero)
	{
		BOOST_CHECK_EQUAL(str.GetStringData()[str.GetLength()], '\0');
	}
	BOOST_AUTO_TEST_SUITE(Test_SubStr)
		BOOST_AUTO_TEST_CASE(can_extract_substr_from_zero_pos)
		{
			auto res = str.SubString(0, 3);
			VerifyString(res, "str", 3);
		}
		BOOST_AUTO_TEST_CASE(can_extract_substr_from_any_pos)
		{
			auto res = str.SubString(2, 3);
			VerifyString(res, "rin", 3);
		}
		BOOST_AUTO_TEST_CASE(can_extract_str_from_start_to_end)
		{
			auto res = str.SubString(1);
			VerifyString(res, "tring", 5);
		}
		BOOST_AUTO_TEST_CASE(can_extract_all_str_from_zero_pos)
		{
			auto res = str.SubString(0, 8);
			VerifyString(res, "string", 6);
		}
		BOOST_AUTO_TEST_CASE(can_extract_substr_from_empty_str)
		{
			auto res = emptyStr.SubString(0, 8);
			VerifyString(res, "", 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_clear)
		BOOST_AUTO_TEST_CASE(can_clear_str)
		{
			str.Clear();
			VerifyString(str, "", 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_assignment_operator_)
		BOOST_AUTO_TEST_CASE(can_assign_to_itself)
		{
			str = str;
			VerifyString(str, "string", 6);
		}
		//memory leak
		BOOST_AUTO_TEST_CASE(can_assign_rvalue)
		{
			emptyStr = "rvalue";
			VerifyString(emptyStr, "rvalue", 6);
		}
		//memory leak
		BOOST_AUTO_TEST_CASE(can_assign_stl_str)
		{
			std::string stlStr = "stlStr";
			str = stlStr;
			VerifyString(str, "stlStr", 6);
		}
		BOOST_AUTO_TEST_CASE(can_assign_other_str_to_source_str)
		{
			emptyStr = str;
			VerifyString(emptyStr, "string", 6);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


struct some_strings_for_test_overloaded_operators
{
	CMyString str1;
	CMyString str2;
	some_strings_for_test_overloaded_operators()
		: str1("str1")
		, str2("str2")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_operators, some_strings_for_test_overloaded_operators)
	BOOST_AUTO_TEST_SUITE(Test_assignment_operator_plus)
		BOOST_AUTO_TEST_CASE(can_concatenate_with_CMyString_type)
		{
			CMyString result = str1 + str2;
			VerifyString(result, "str1str2", 8);
		}
		BOOST_AUTO_TEST_CASE(can_concatenate_few_str_with_CMyString_type)
		{
			CMyString result = str1 + str2 + str1;
			VerifyString(result, "str1str2str1", 12);
		}
		BOOST_AUTO_TEST_CASE(can_concatenate_with_pointer_to_const_data)
		{
			CMyString result = str1 + "pChars";
			VerifyString(result, "str1pChars", 10);
		}
		BOOST_AUTO_TEST_CASE(can_concatenate_few_pointers_to_const_data)
		{
			CMyString result = str1 + "other" + "other";
			VerifyString(result, "str1otherother", 14);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_assignment_operator_plus_equal)
		BOOST_AUTO_TEST_CASE(can_concatenate_to_source_str)
		{
			CMyString conc = "+newStr";
			str1 += conc;
			VerifyString(str1, "str1+newStr", conc.GetLength() + 4);
		}
		BOOST_AUTO_TEST_CASE(can_concatenate_with_empty_str)
		{
			CMyString conc = "";
			str1 += conc;
			VerifyString(str1, "str1", 4);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_compare_bool_operator_equal_equal)
		BOOST_AUTO_TEST_CASE(can_be_equal_with_CMyString)
		{
			BOOST_CHECK(!(str1 == str2));
			CMyString equalStr = "str1";
			BOOST_CHECK(str1 == equalStr);
		}
		BOOST_AUTO_TEST_CASE(can_be_equal_with_pointer_to_const_char)
		{
			BOOST_CHECK(str1 == "str1");
		}
		BOOST_AUTO_TEST_CASE(can_be_equal_with_stl_string)
		{
			std::string equalStr = "str2";
			BOOST_CHECK(str2 == equalStr);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_compare_bool_operator_not_equal)
		BOOST_AUTO_TEST_CASE(can_not_be_equal_with_CMyString)
		{
			BOOST_CHECK(str1 != str2);
		}
		BOOST_AUTO_TEST_CASE(cant_be_equal_with_pointer_to_const_char)
		{
			BOOST_CHECK(str1 != "not_equal_str");
		}
		BOOST_AUTO_TEST_CASE(can_not_be_equal_with_stl_string)
		{
			std::string equalStr = "not equal str";
			BOOST_CHECK(str2 != equalStr);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_compare_bool_operator_lesser_than)
		BOOST_AUTO_TEST_CASE(can_compare_with_CMyString)
		{
			BOOST_CHECK(str1 < str2);
		}
		BOOST_AUTO_TEST_CASE(when_first_greater_than_another_should_return_false)
		{
			BOOST_CHECK(!(str2 < str1));
		}
		BOOST_AUTO_TEST_CASE(when_both_str_are_equal_should_return_false)
		{
			BOOST_CHECK(!(str1 < str1));
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_pointer_to_const_char)
		{
			BOOST_CHECK(str1 < "str2");
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_stl_string)
		{
			std::string greaterStr = "str3";
			BOOST_CHECK(str2 < greaterStr);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_compare_bool_operator_greater_than_or_equal_to)
		BOOST_AUTO_TEST_CASE(can_compare_with_CMyString)
		{
			BOOST_CHECK(str2 >= str1);
		}
		BOOST_AUTO_TEST_CASE(when_both_str_are_equal_should_return_true)
		{
			BOOST_CHECK(str1 >= str1);
		}
		BOOST_AUTO_TEST_CASE(when_first_lesser_than_another_should_return_false)
		{
			BOOST_CHECK(!(str1 >= str2));
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_pointer_to_const_char)
		{
			BOOST_CHECK(str1 >= "str0");
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_stl_string)
		{
			std::string lesserStr = "str0";
			BOOST_CHECK(str2 >= lesserStr);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_compare_bool_operator_greater_than)
		BOOST_AUTO_TEST_CASE(can_compare_with_CMyString)
		{
			BOOST_CHECK(str2 > str1);
		}
		BOOST_AUTO_TEST_CASE(when_both_str_are_equal_should_return_false)
		{
			BOOST_CHECK(!(str1 > str1));
		}
		BOOST_AUTO_TEST_CASE(when_first_str_lesser_then_another_should_return_false)
		{
			BOOST_CHECK(!(str1 > str2));
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_pointer_to_const_char)
		{
			BOOST_CHECK(str1 > "str0");
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_stl_string)
		{
			std::string lesserStr = "str0";
			BOOST_CHECK(str2 > lesserStr);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_compare_bool_operator_lesser_than_or_equal)
		BOOST_AUTO_TEST_CASE(can_compare_with_CMyString)
		{
			BOOST_CHECK(str1 <= str2);
		}
		BOOST_AUTO_TEST_CASE(when_both_str_are_equal_should_return_true)
		{
			BOOST_CHECK(str1 <= str1);
		}
		BOOST_AUTO_TEST_CASE(when_first_str_lesser_then_another_should_return_true)
		{
			BOOST_CHECK(str1 <= str2);
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_pointer_to_const_char)
		{
			BOOST_CHECK(str1 <= "str2");
		}
		BOOST_AUTO_TEST_CASE(can_be_compared_with_stl_string)
		{
			std::string greaterStr = "str3";
			BOOST_CHECK(str2 <= greaterStr);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Test_index_operator)
		BOOST_AUTO_TEST_CASE(can_get_certain_char_from_string)
		{
			BOOST_CHECK(str1[2] == 'r');

			BOOST_CHECK(str1[0] == 's');
		}
		BOOST_AUTO_TEST_CASE(can_change_certain_char_from_string)
		{
			str1[3] = '0';
			VerifyString(str1, "str0", 4);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_stream_operator_right_arrows)
		//memory leak
		BOOST_AUTO_TEST_CASE(can_be_read_from_stream)
		{
			std::stringstream strS("someString");
			CMyString str;
			strS >> str;
			VerifyString(str, "someString", 10);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_stream_operator_left_arrows)
		BOOST_AUTO_TEST_CASE(can_be_written_to_CMyString_from_strean)
		{
			std::stringstream strS;
			CMyString str = "string";
			strS << str;
			BOOST_CHECK(strS.str() == str);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
