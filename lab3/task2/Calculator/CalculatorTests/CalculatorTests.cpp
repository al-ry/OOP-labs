#include "stdafx.h"
#include "../Calculator/Calculator.h"

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)

	BOOST_AUTO_TEST_SUITE(Test_DeclareVriable_method)	

		BOOST_AUTO_TEST_CASE(can_declare_var)
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

BOOST_AUTO_TEST_SUITE_END()
