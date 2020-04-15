#include "stdafx.h"
#include "../Calculator/Calculator.h"

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)

	BOOST_AUTO_TEST_SUITE(Test_DeclareVriable_method)	

		BOOST_AUTO_TEST_CASE(can_declare_var_with_empty_val)
		{
			bool res = calculator.DeclareVariable("x");

			BOOST_CHECK_EQUAL(res, true);
		}

		BOOST_AUTO_TEST_CASE(cannot_declare_similar_vars)
		{
			calculator.DeclareVariable("x");
			bool res = calculator.DeclareVariable("x");

			BOOST_CHECK_EQUAL(res, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_declare_with_empty_name)
		{
			bool res = calculator.DeclareVariable("");
		
			BOOST_CHECK_EQUAL(res, false);
		}

		BOOST_AUTO_TEST_CASE(cannot_declare_var_starts_with_digit)
		{
			bool res = calculator.DeclareVariable("123variable");

			BOOST_CHECK_EQUAL(res, false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_GetVariables_method)	

		BOOST_AUTO_TEST_CASE(can_get_empty_variable_list)
		{
			BOOST_CHECK(calculator.GetVariables().empty());
		};

		BOOST_AUTO_TEST_CASE(can_get_variable_list_with_3_vars)
		{
			calculator.DeclareVariable("x");
			calculator.DeclareVariable("var_1");
			calculator.DeclareVariable("_var");

			auto res = calculator.GetVariables();
			BOOST_CHECK_EQUAL(res.size(), 3);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_AssignValueToVariable_method)	
		BOOST_AUTO_TEST_CASE(can_declare_var_through_this_method)
		{
			BOOST_CHECK(calculator.AssignValueToVariable("x", "5"));
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("x") != varList.end());
		};
		BOOST_AUTO_TEST_CASE(check_that_right_identifier_cannot_be_empty)
		{
			BOOST_CHECK(!calculator.AssignValueToVariable("x", ""));
		}
		BOOST_AUTO_TEST_CASE(can_assign_value_to_var)
		{
			calculator.AssignValueToVariable("x", "55.55");
			auto varList = calculator.GetVariables();
			BOOST_CHECK_EQUAL(varList.at("x"), 55.55);
		};
		BOOST_AUTO_TEST_CASE(cant_assign_value_to_var_when_right_id_arent_either_number_or_another_var)
		{
			calculator.AssignValueToVariable("x", "hg5hello");
			calculator.DeclareVariable("f");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(std::isnan(varList.at("f")));
		};
		BOOST_AUTO_TEST_CASE(can_assign_value_to_var_via_other_var)
		{
			calculator.AssignValueToVariable("x", "55.55");
			calculator.DeclareVariable("y");
			calculator.AssignValueToVariable("y", "x");
			auto varList = calculator.GetVariables();
			BOOST_CHECK_EQUAL(varList.at("y"), 55.55);
		};

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_GetVariableValue_method)
		BOOST_AUTO_TEST_CASE(can_get_empty_value_from_declared_var)
		{
			calculator.DeclareVariable("var_1");
			calculator.GetVariableValue("var_1");
			BOOST_CHECK(std::isnan(calculator.GetVariableValue("var_1")));
		};
		BOOST_AUTO_TEST_CASE(can_get_var_value)
		{
			calculator.AssignValueToVariable("var", "550");
			BOOST_CHECK_EQUAL(calculator.GetVariableValue("var"), 550);
		};

	BOOST_AUTO_TEST_SUITE_END()

		
BOOST_AUTO_TEST_SUITE_END()
