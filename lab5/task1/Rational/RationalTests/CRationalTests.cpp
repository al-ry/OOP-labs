#include "stdafx.h"
#include "../Rational/CRational.h"


void VerifyNumeratorAndDenumerator(const CRational& verifiableFraction, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK(verifiableFraction.GetNumerator() == expectedNumerator);
	BOOST_CHECK(verifiableFraction.GetDenominator() == expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Test_Construcor)
	BOOST_AUTO_TEST_CASE(costructor_without_parameters_should_construct_fraction_with_0_numerator_and_1_denominator)
	{
		CRational rationalNumber;
		VerifyNumeratorAndDenumerator(rationalNumber, 0, 1);
	}
	BOOST_AUTO_TEST_CASE(costructor_with_one_parameter_should_construct_fraction_with_transfer_numerator)
	{
		CRational rationalNumber(5);
		VerifyNumeratorAndDenumerator(rationalNumber, 5, 1);
	}
	BOOST_AUTO_TEST_CASE(costructor_tow_parameter_should_construct_fraction_with_transfer_numerator_and_denomirator)
	{
		CRational rationalNumber(5, 2);
		VerifyNumeratorAndDenumerator(rationalNumber, 5, 2);
	}
	BOOST_AUTO_TEST_CASE(when_denominator_is_zero_should_construct_fraction_with_0_numerator_and_1_denominator)
	{
		CRational rationalNumber(5, 0);
		VerifyNumeratorAndDenumerator(rationalNumber, 0, 1);
	}
	BOOST_AUTO_TEST_CASE(when_denominator_lesser_than_0_should_construct_fraction_with_non_negative_denominator)
	{
		CRational rationalNumber(6, -5);
		VerifyNumeratorAndDenumerator(rationalNumber, -6, 5);
	}
	BOOST_AUTO_TEST_CASE(costructor_should_normalize_fraction)
	{
		CRational rationalNumber(840, 3600);
		VerifyNumeratorAndDenumerator(rationalNumber, 7, 30);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_ToDouble_)
	BOOST_AUTO_TEST_CASE(should_convert_fraction_to_double)
	{
		CRational rationalNumber(1, 4);
		BOOST_CHECK_EQUAL(rationalNumber.ToDouble(), 0.25);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_overloaded_unary_operators)
	BOOST_AUTO_TEST_CASE(when_overloaded_plus_should_change_numerator_value_to_plus)
	{
		CRational rationalNumber(-5, 10);
		rationalNumber = +rationalNumber;
		VerifyNumeratorAndDenumerator(rationalNumber, -1, 2);
	}
	BOOST_AUTO_TEST_CASE(when_overloaded_minus_should_change_numerator_value_to_minus)
	{
		CRational rationalNumber(-5, 10);
		rationalNumber = -rationalNumber;
		VerifyNumeratorAndDenumerator(rationalNumber, 1, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

struct some_rational_numbers
{
	CRational num1;
	CRational num2;
	some_rational_numbers()
		: num1(5, 2)
		, num2(3, 5){};
};



BOOST_FIXTURE_TEST_SUITE(Test_overloaded_binary_minus_operator, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(overloaded_minus_should_add_two_rational_numbers)
	{
		CRational res = num1 - num2;
		VerifyNumeratorAndDenumerator(res, 19, 10);
	}
	BOOST_AUTO_TEST_CASE(when_one_operand_is_integer_should_substract_nums)
	{
		CRational res = num1 - 1;
		VerifyNumeratorAndDenumerator(res, 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(Test_overloaded_binary_star_operator, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(overloaded_star_should_multiply_two_rational_numbers)
	{
		CRational res = num1 * num2;
		VerifyNumeratorAndDenumerator(res, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(when_one_operand_is_integer_should_multiply_two_numbers)
	{
		CRational res = num1 * 10;
		VerifyNumeratorAndDenumerator(res, 25, 1);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_binary_slash_operator, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(overloaded_slash_should_divide_two_rational_numbers)
	{
		CRational res = num1 / num2;
		VerifyNumeratorAndDenumerator(res, 25, 6);
	}
	BOOST_AUTO_TEST_CASE(when_one_operand_is_integer_should_divide_two_numbers)
	{
		CRational res = num1 / 2;
		VerifyNumeratorAndDenumerator(res, 5, 4);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_binary_plus, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(overloaded_plus_should_add_two_rational_numbers)
	{
		CRational res = num1 + num2;
		VerifyNumeratorAndDenumerator(res, 31, 10);
	}
	BOOST_AUTO_TEST_CASE(when_one_operand_is_integer_should_add_nums)
	{
		CRational res = num1 + 1;
		VerifyNumeratorAndDenumerator(res, 7, 2);
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(Test_overloaded_operator_plus_equal, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_assign_two_rational_nums_should_assign_value_to_num)
	{
		num1 += num2;
		VerifyNumeratorAndDenumerator(num1, 31, 10);
	}
	BOOST_AUTO_TEST_CASE(when_right_num_is_int_should_assign_value_to_num)
	{
		num1 += 5;
		VerifyNumeratorAndDenumerator(num1, 15, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_operator_minus_equal, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_assign_two_rational_nums_should_assign_value_to_num)
	{
		num1 -= num2;
		VerifyNumeratorAndDenumerator(num1, 19, 10);
	}
	BOOST_AUTO_TEST_CASE(when_right_num_is_int_should_assign_value_to_num)
	{
		num1 -= 1;
		VerifyNumeratorAndDenumerator(num1, 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_operator_slash_equal, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_assign_two_rational_nums_should_assign_value_to_num)
	{
		num1 /= num2;
		VerifyNumeratorAndDenumerator(num1, 25, 6);
	}
	BOOST_AUTO_TEST_CASE(when_right_num_is_int_should_assign_value_to_num)
	{
		num1 /= 10;
		VerifyNumeratorAndDenumerator(num1, 1, 4);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_operator_star_equal, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_assign_two_rational_nums_should_assign_value_to_num)
	{
		num1 *= num2;
		VerifyNumeratorAndDenumerator(num1, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(when_right_num_is_int_should_assign_value_to_num)
	{
		num1 *= 2;
		VerifyNumeratorAndDenumerator(num1, 5, 1);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_equal_operator, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(should_compare_equals_values)
	{
		CRational comparedNum(5, 2);
		BOOST_CHECK(num1 == comparedNum);
	}
	BOOST_AUTO_TEST_CASE(when_rvalue_is_integer_should_compare_equals_values)
	{
		CRational comparedNum(5);
		BOOST_CHECK(comparedNum == 5);
	}
	BOOST_AUTO_TEST_CASE(should_compare_not_equals_values)
	{
		BOOST_CHECK(!(num1 == num2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_not_equal_operator, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(should_compare_not_equals_values)
	{
		BOOST_CHECK(num1 != num2);
	}
	BOOST_AUTO_TEST_CASE(when_rvalue_is_integer_should_compare_equals_values)
	{
		BOOST_CHECK(num1 != 5);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_comparasion_operator_less_than, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_both_op_are_rational_nums_should_compare_values)
	{
		BOOST_CHECK(num2 < num1);
	}
	BOOST_AUTO_TEST_CASE(when_lvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(1 < num1);
	}
	BOOST_AUTO_TEST_CASE(when_rvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(num2 < 1);
	}
	BOOST_AUTO_TEST_CASE(when_values_equal_should_compare_values)
	{
		CRational num(3, 5);
		BOOST_CHECK(!(num <num2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_comparasion_operator_less_than_or_equal_to, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_both_op_are_rational_nums_should_compare_values)
	{
		BOOST_CHECK(num2 <= num1);
	}
	BOOST_AUTO_TEST_CASE(when_lvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(1 <= num1);
	}
	BOOST_AUTO_TEST_CASE(when_rvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(num2 <= 1);
	}
	BOOST_AUTO_TEST_CASE(when_values_equal_should_compare_values)
	{
		CRational num(5, 2);
		BOOST_CHECK(num1 <= num);
		BOOST_CHECK(num <= num1);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_comparasion_operator_greater_than, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_both_op_are_rational_nums_should_compare_values)
	{
		BOOST_CHECK(num1 > num2);
	}
	BOOST_AUTO_TEST_CASE(when_lvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(num1 > 1);
	}
	BOOST_AUTO_TEST_CASE(when_rvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(1 > num2);
	}
	BOOST_AUTO_TEST_CASE(when_values_equal_should_compare_values)
	{
		CRational num(3, 5);
		BOOST_CHECK(!(num > num2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_comparasion_operator_greater_than_or_equal_to, some_rational_numbers)
	BOOST_AUTO_TEST_CASE(when_both_op_are_rational_nums_should_compare_values)
	{
		BOOST_CHECK(num1 >= num2);
	}
	BOOST_AUTO_TEST_CASE(when_lvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(num1 >= 1);
	}
	BOOST_AUTO_TEST_CASE(when_rvalue_is_int_should_compare_values)
	{
		BOOST_CHECK(1 >= num2);
	}
	BOOST_AUTO_TEST_CASE(when_values_equal_should_compare_values)
	{
		CRational num(5, 2);
		BOOST_CHECK(num1 >= num);
		BOOST_CHECK(num >= num1);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_overloaded_stream_operators, some_rational_numbers)
	BOOST_AUTO_TEST_SUITE(left_arrows_operator)
		BOOST_AUTO_TEST_CASE(can_put_rational_num_in_output)
		{
			std::stringstream strs;
			strs << num1;
			std::string expecteStr = "5/2";
			BOOST_CHECK(expecteStr == strs.str());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(right_arrows_operator)
		BOOST_AUTO_TEST_CASE(can_get_rational_num_in_output)
		{
			std::stringstream strs;
			strs << "50/2";
			strs >> num1;
			VerifyNumeratorAndDenumerator(num1, 25, 1);
		}
		BOOST_AUTO_TEST_CASE(can_set_fail_bit_when_data_incorrect)
		{
			std::stringstream strs;
			strs << "50//2";
			strs >> num1;
			BOOST_CHECK(strs.fail());
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_ToCompoundFraction)
	BOOST_AUTO_TEST_CASE(can_convert_rational_to_compound_fraction)
	{
		CRational rational(24, 3);
		auto res = rational.ToCompoundFraction();
		BOOST_CHECK(res.first == 8);
		VerifyNumeratorAndDenumerator(res.second, 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_convert_negative_rational_to_compound_fraction)
	{
		CRational rational(-7, 3);
		auto res = rational.ToCompoundFraction();
		BOOST_CHECK(res.first == -2);
		VerifyNumeratorAndDenumerator(res.second, -1, 3);
	}
BOOST_AUTO_TEST_SUITE_END()